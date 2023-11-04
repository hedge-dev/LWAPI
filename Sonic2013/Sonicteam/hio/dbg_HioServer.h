#pragma once
// Reference implementation of HioServer, This might not be accraute with LW's, nevermind the layout is accruate to PC's

#define HIO_COMMAND_SERVERLINK "sys:serverlink"
#define HIO_COMMAND_CLIENTLINK "sys:clientlink"

#define HIO_SERVICE_INVALID   -1

namespace csl::hio
{
	struct ConnectArgs
	{
		NetworkSocket Socket{};
	};
	
	struct DisconnectArgs
	{
		NetworkSocket Socket{};
	};
	
	struct PacketReadArgs
	{
		PacketHeader Header{};
		NetworkSocket Socket{};
		PacketHeader* pPacket{};
	};
	
	struct PacketWriteArgs
	{
		NetworkSocket Socket{};
	};
	
	class HioServer : public HioCore
	{
	public:
		typedef HioError ConnectFuncType(void*, const ConnectArgs&);
		typedef HioError DisconnectFuncType(void*, const DisconnectArgs&);
		typedef HioError ReadFuncType(void*, const PacketReadArgs&);
		typedef HioError WriteFuncType(void*, const PacketWriteArgs&);
	
	protected:
		struct ServiceDesc
		{
			ut::FixedString<64> Name{};
			bool CanWrite{};
			bool CanRead{};
			void* pConnectContext{};
			void* pDisconnectContext{};
			void* pReadContext{};
			void* pWriteContext{};
			ConnectFuncType* pConnectFunc{};
			DisconnectFuncType* pDisconnectFunc{};
			ReadFuncType* pReadFunc{};
			WriteFuncType* pWriteFunc{};

			void ReadCallback(const PacketReadArgs& in_rArgs)
			{
				if (pReadFunc && pReadFunc(pReadContext, in_rArgs) != HIO_ERROR_OK)
					pReadFunc = nullptr;
			}

			void WriteCallback(NetworkSocket in_sock)
			{
				if (pWriteFunc && pWriteFunc(pWriteContext, { in_sock }) != HIO_ERROR_OK)
					pWriteFunc = nullptr;
			}
			
			void ConnectCallback(NetworkSocket in_sock)
			{
				if (pConnectFunc && pConnectFunc(pConnectContext, { in_sock }) != HIO_ERROR_OK)
					pConnectFunc = nullptr;
			}
			
			void DisconnectCallback(NetworkSocket in_sock)
			{
				if (pDisconnectFunc && pDisconnectFunc(pDisconnectContext, { in_sock }) != HIO_ERROR_OK)
					pDisconnectFunc = nullptr;
			}
		};

		struct ClientSocket
		{
			NetworkSocket Socket{};
			ServiceDesc* pService{};
		};

		csl::ut::FixedArray<ServiceDesc, FD_SETSIZE> m_Services{};
		size_t m_ServiceCount{};
		csl::ut::FixedArray<ClientSocket, FD_SETSIZE> m_Clients{};
		size_t m_ClientCount{};
		fd_set m_FdSet;
	
	public:
		HioServer(fnd::IAllocator* in_pAlloc) : HioCore(in_pAlloc)
		{
			FD_ZERO(&m_FdSet);
			SetServer(true);
		}
		
		~HioServer()
		{
			Cleanup();
		}
		
		void DisconnectAll() 
		{
			for (size_t i = 0; i < m_ClientCount; i++) 
			{
				auto& client = m_Clients[i];
				if (!client.Socket || !client.pService)
					continue;

				client.pService->DisconnectCallback(client.Socket);
				client.pService->CanRead = false;
				client.pService->CanWrite = false;
			}
		}

	protected:
		HioError StartupCore(const char* in_pAddress, ushort in_port) override
		{
			Cleanup();
			HioError error = HIO_ERROR_OK;
			if ((error = SocketInit(in_pAddress, in_port)) == HIO_ERROR_OK)
			{
				m_ClientCount = 1;
				m_Clients[0].Socket = GetSocket();
				FD_SET(GetSocket(), &m_FdSet);
			}
			
			return error;
		}

		HioError PollCore() override
		{
			fd_set readFds;
			fd_set writeFds;

			memcpy(&readFds, &m_FdSet, sizeof(m_FdSet));
			memcpy(&writeFds, &m_FdSet, sizeof(m_FdSet));
			
			timeval timeout{};
			int validSocks = select(FD_SETSIZE, &readFds, &writeFds, nullptr, &timeout);
			if (validSocks == SOCKET_ERROR)
				return HIO_ERROR_SELECTFAIL;

			if (!validSocks)
				return HIO_ERROR_NOSOCKETS;

			for (size_t i = 0; i < m_ClientCount; i++)
			{
				auto& client = m_Clients[i];
				if (FD_ISSET(client.Socket, &m_FdSet))
				{
					if (client.Socket == GetSocket() && IsServer())
					{
						NetworkSocket newClient = AcceptNewClient(client.Socket);
						if (newClient != HIO_ERROR_ACCEPTFAIL)
						{
							if (m_ClientCount >= m_Clients.size())
								return HIO_ERROR_TOOMANYCLIENTS;

							FD_SET(newClient, &m_FdSet);
							m_Clients[m_ClientCount++].Socket = newClient;
						}
					}
					else
					{
						if (RecvAndSendMsg(&client, GetSocket(), &m_FdSet) != HIO_ERROR_OK)
						{
							if (client.pService)
							{
								client.pService->DisconnectCallback(client.Socket);
								client.pService->CanRead = false;
								client.pService->CanWrite = false;
							}

							FD_CLR(client.Socket, &m_FdSet);
							m_ClientCount--;
						}
					}
				}
				
				if (FD_ISSET(client.Socket, &m_FdSet))
				{
					if (client.pService)
					{
						if (client.pService->CanWrite)
							client.pService->WriteCallback(client.Socket);
						else if (client.pService->CanRead)
						{
							PacketHeader header;
							MakePacketHeader(client.pService->Name, HIO_COMMAND_CLIENTLINK, header);
							HioError sendError = HIO_ERROR_OK;
							SendAll(client.Socket, &header, sizeof(header), &sendError);

							if (sendError == HIO_ERROR_OK)
								client.pService->CanWrite = true;
						}
					}
				}
			}

			return HIO_ERROR_OK;
		}

		bool AcceptNewClientLink(const PacketHeader* in_pHeader, csl::hio::HioServer::ClientSocket* in_pSock)
		{
			for (size_t i = 0; i < m_ServiceCount; i++)
			{
				auto& service = m_Services[i];
				if (!service.CanRead && in_pHeader->ServiceName == service.Name.c_str() && in_pHeader->CommandName == HIO_COMMAND_SERVERLINK)
				{
					in_pSock->pService = &service;
					service.CanRead = true;
					service.ConnectCallback(in_pSock->Socket);
					return true;
				}
			}
			
			return false;
		}
		
		HioError RecvAndSendMsg(ClientSocket* in_pSock, NetworkSocket in_hostSock, fd_set* in_pSet)
		{
			int bytesRecieved = 0;
			HioError error = HIO_ERROR_OK;
			PacketHeader* pPacket = RecvAllAlloc(in_pSock->Socket, &bytesRecieved, &error);

			if (error == HIO_ERROR_OK && (IsServer() ? in_pSock->Socket != in_hostSock : true) && FD_ISSET(in_pSock->Socket, in_pSet))
			{
				PacketHeader header{};
				GetPacketHeader(pPacket, &header);
				if (!AcceptNewClientLink(&header, in_pSock) && in_pSock->pService)
				{
					PacketReadArgs args{};
					args.Header = header;
					args.Socket = in_pSock->Socket;
					args.pPacket = pPacket;
					in_pSock->pService->ReadCallback(args);
				}
			}

			RecvAllFree(pPacket);
			return error;
		}
		
		HioError CleanupCore() override
		{
			DisconnectAll();
			DisconnectSocket();
			return HIO_ERROR_OK;
		}

		NetworkSocket AcceptNewClient(NetworkSocket in_sock)
		{
			sockaddr_in address{};
			int addrLen = sizeof(sockaddr_in);
			
			NetworkSocket clientSock = accept(in_sock, (sockaddr*)&address, &addrLen);
			if (clientSock == SOCKET_ERROR)
			{
				closesocket(in_sock);
				return HIO_ERROR_ACCEPTFAIL;
			}

			return clientSock;
		}
	
	public:
		const char* GetIPAddress(int in_index)
		{
			char nameBuf[256]{};
			hostent* ht{};
			
			if (gethostname(nameBuf, sizeof(nameBuf)) == SOCKET_ERROR || (ht = gethostbyname(nameBuf)) == nullptr)
			{
				m_Address = "unknown";
			}
			else
			{
				in_addr* addr = (in_addr*)ht->h_addr_list[in_index];
				if (addr)
					m_Address = inet_ntoa(*addr);
				else
					m_Address = "unknown";
			}
			return m_Address;
		}

		void SetConnectFunc(int in_service, ConnectFuncType* in_pFunc, void* in_pContext)
		{
			if (in_service >= m_ServiceCount)
				return;

			m_Services[in_service].m_pConnectFunc = in_pFunc;
			m_Services[in_service].m_pConnectContext = in_pContext;
		}

		void SetDisconnectFunc(int in_service, DisconnectFuncType* in_pFunc, void* in_pContext)
		{
			if (in_service >= m_ServiceCount)
				return;

			m_Services[in_service].m_pDisconnectFunc = in_pFunc;
			m_Services[in_service].m_pDisconnectContext = in_pContext;
		}

		void SetReadFunc(int service, ReadFuncType* in_pFunc, void* in_pContext)
		{
			if (in_service >= m_ServiceCount)
				return;

			m_Services[in_service].m_pReadFunc = in_pFunc;
			m_Services[in_service].m_pReadContext = in_pContext;
		}

		void SetWriteFunc(int in_service, WriteFuncType* in_pFunc, void* in_pContext)
		{
			if (in_service >= m_ServiceCount)
				return;

			m_Services[in_service].m_pWriteFunc = in_pFunc;
			m_Services[in_service].m_pWriteContext = in_pContext;
		}
		
		int SetServiceId(const char* in_pName)
		{
			size_t i = 0;
			for(auto& service : m_Services)
			{
				if (i >= m_ServiceCount)
				{
					service.m_Name = in_pName;
					return i;
				}
				
				if (service.m_Name == in_pName)
				{
					return i;
				}

				i++;
			}

			return HIO_SERVICE_INVALID;
		}

		const char* GetServiceId(int in_id) const
		{
			if (in_id >= m_Services.size())
				return nullptr;

			return m_Services[in_id].m_Name;
		}
	};
}