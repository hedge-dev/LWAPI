#pragma once
// Reference implementation of HioServer, This might not be accraute with LW's, nevermind the layout is accruate to PC's

#define HIO_COMMAND_SERVERLINK "sys:serverlink"
#define HIO_COMMAND_CLIENTLINK "sys:clientlink"

#define HIO_SERVICE_INVALID   -1

namespace csl::hio
{
	struct ConnectArgs
	{
		NetworkSocket m_Socket{};
	};
	
	struct DisconnectArgs
	{
		NetworkSocket m_Socket{};
	};
	
	struct PacketReadArgs
	{
		PacketHeader m_Header{};
		NetworkSocket m_Socket{};
		PacketHeader* m_pPacket{};
	};
	
	struct PacketWriteArgs
	{
		NetworkSocket m_Socket{};
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
			ut::FixedString<64> m_Name{};
			bool m_CanWrite{};
			bool m_CanRead{};
			void* m_pConnectContext{};
			void* m_pDisconnectContext{};
			void* m_pReadContext{};
			void* m_pWriteContext{};
			ConnectFuncType* m_pConnectFunc{};
			DisconnectFuncType* m_pDisconnectFunc{};
			ReadFuncType* m_pReadFunc{};
			WriteFuncType* m_pWriteFunc{};

			void ReadCallback(const PacketReadArgs& args)
			{
				if (m_pReadFunc && m_pReadFunc(m_pReadContext, args) != HIO_ERROR_OK)
					m_pReadFunc = nullptr;
			}

			void WriteCallback(NetworkSocket sock)
			{
				if (m_pWriteFunc && m_pWriteFunc(m_pWriteContext, { sock }) != HIO_ERROR_OK)
					m_pWriteFunc = nullptr;
			}
			
			void ConnectCallback(NetworkSocket sock)
			{
				if (m_pConnectFunc && m_pConnectFunc(m_pConnectContext, { sock }) != HIO_ERROR_OK)
					m_pConnectFunc = nullptr;
			}
			
			void DisconnectCallback(NetworkSocket sock)
			{
				if (m_pDisconnectFunc && m_pDisconnectFunc(m_pDisconnectContext, { sock }) != HIO_ERROR_OK)
					m_pDisconnectFunc = nullptr;
			}
		};

		struct ClientSocket
		{
			NetworkSocket m_Socket{};
			ServiceDesc* m_pService{};
		};

		csl::ut::FixedArray<ServiceDesc, FD_SETSIZE> m_Services{};
		size_t m_ServiceCount{};
		csl::ut::FixedArray<ClientSocket, FD_SETSIZE> m_Clients{};
		size_t m_ClientCount{};
		fd_set m_FdSet;
	
	public:
		HioServer(fnd::IAllocator* pAlloc) : HioCore(pAlloc)
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
				if (!client.m_Socket || !client.m_pService)
					continue;

				client.m_pService->DisconnectCallback(client.m_Socket);
				client.m_pService->m_CanRead = false;
				client.m_pService->m_CanWrite = false;
			}
		}

	protected:
		HioError StartupCore(const char* pAddress, ushort port) override
		{
			Cleanup();
			HioError error = HIO_ERROR_OK;
			if ((error = SocketInit(pAddress, port)) == HIO_ERROR_OK)
			{
				m_ClientCount = 1;
				m_Clients[0].m_Socket = GetSocket();
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
				if (FD_ISSET(client.m_Socket, &m_FdSet))
				{
					if (client.m_Socket == GetSocket() && IsServer())
					{
						NetworkSocket newClient = AcceptNewClient(client.m_Socket);
						if (newClient != HIO_ERROR_ACCEPTFAIL)
						{
							if (m_ClientCount >= m_Clients.size())
								return HIO_ERROR_TOOMANYCLIENTS;

							FD_SET(newClient, &m_FdSet);
							m_Clients[m_ClientCount++].m_Socket = newClient;
						}
					}
					else
					{
						if (RecvAndSendMsg(&client, GetSocket(), &m_FdSet) != HIO_ERROR_OK)
						{
							if (client.m_pService)
							{
								client.m_pService->DisconnectCallback(client.m_Socket);
								client.m_pService->m_CanRead = false;
								client.m_pService->m_CanWrite = false;
							}

							FD_CLR(client.m_Socket, &m_FdSet);
							m_ClientCount--;
						}
					}
				}
				
				if (FD_ISSET(client.m_Socket, &m_FdSet))
				{
					if (client.m_pService)
					{
						if (client.m_pService->m_CanWrite)
							client.m_pService->WriteCallback(client.m_Socket);
						else if (client.m_pService->m_CanRead)
						{
							PacketHeader header;
							MakePacketHeader(client.m_pService->m_Name, HIO_COMMAND_CLIENTLINK, header);
							HioError sendError = HIO_ERROR_OK;
							SendAll(client.m_Socket, &header, sizeof(header), &sendError);

							if (sendError == HIO_ERROR_OK)
								client.m_pService->m_CanWrite = true;
						}
					}
				}
			}

			return HIO_ERROR_OK;
		}

		bool AcceptNewClientLink(const PacketHeader* pHeader, csl::hio::HioServer::ClientSocket* pSock)
		{
			for (size_t i = 0; i < m_ServiceCount; i++)
			{
				auto& service = m_Services[i];
				if (!service.m_CanRead && pHeader->m_ServiceName == service.m_Name.c_str() && pHeader->m_CommandName == HIO_COMMAND_SERVERLINK)
				{
					pSock->m_pService = &service;
					service.m_CanRead = true;
					service.ConnectCallback(pSock->m_Socket);
					return true;
				}
			}
			
			return false;
		}
		
		HioError RecvAndSendMsg(ClientSocket* pSock, NetworkSocket hostSock, fd_set* pSet)
		{
			int bytesRecieved = 0;
			HioError error = HIO_ERROR_OK;
			PacketHeader* pPacket = RecvAllAlloc(pSock->m_Socket, &bytesRecieved, &error);

			if (error == HIO_ERROR_OK && (IsServer() ? pSock->m_Socket != hostSock : true) && FD_ISSET(pSock->m_Socket, pSet))
			{
				PacketHeader header{};
				GetPacketHeader(pPacket, &header);
				if (!AcceptNewClientLink(&header, pSock) && pSock->m_pService)
				{
					PacketReadArgs args{};
					args.m_Header = header;
					args.m_Socket = pSock->m_Socket;
					args.m_pPacket = pPacket;
					pSock->m_pService->ReadCallback(args);
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

		NetworkSocket AcceptNewClient(NetworkSocket sock)
		{
			sockaddr_in address{};
			int addrLen = sizeof(sockaddr_in);
			
			NetworkSocket clientSock = accept(sock, (sockaddr*)&address, &addrLen);
			if (clientSock == SOCKET_ERROR)
			{
				closesocket(sock);
				return HIO_ERROR_ACCEPTFAIL;
			}

			return clientSock;
		}
	
	public:
		const char* GetIPAddress(int i)
		{
			char nameBuf[256]{};
			hostent* ht{};
			
			if (gethostname(nameBuf, sizeof(nameBuf)) == SOCKET_ERROR || (ht = gethostbyname(nameBuf)) == nullptr)
			{
				m_Address = "unknown";
			}else
			{
				in_addr* addr = (in_addr*)ht->h_addr_list[i];
				if (addr)
					m_Address = inet_ntoa(*addr);
				else
					m_Address = "unknown";
			}
			return m_Address;
		}

		void SetConnectFunc(int service, ConnectFuncType* pFunc, void* pContext)
		{
			if (service >= m_ServiceCount)
				return;

			m_Services[service].m_pConnectFunc = pFunc;
			m_Services[service].m_pConnectContext = pContext;
		}

		void SetDisconnectFunc(int service, DisconnectFuncType* pFunc, void* pContext)
		{
			if (service >= m_ServiceCount)
				return;

			m_Services[service].m_pDisconnectFunc = pFunc;
			m_Services[service].m_pDisconnectContext = pContext;
		}

		void SetReadFunc(int service, ReadFuncType* pFunc, void* pContext)
		{
			if (service >= m_ServiceCount)
				return;

			m_Services[service].m_pReadFunc = pFunc;
			m_Services[service].m_pReadContext = pContext;
		}

		void SetWriteFunc(int service, WriteFuncType* pFunc, void* pContext)
		{
			if (service >= m_ServiceCount)
				return;

			m_Services[service].m_pWriteFunc = pFunc;
			m_Services[service].m_pWriteContext = pContext;
		}
		
		int SetServiceId(const char* pName)
		{
			size_t i = 0;
			for(auto& service : m_Services)
			{
				if (i >= m_ServiceCount)
				{
					service.m_Name = pName;
					return i;
				}
				
				if (service.m_Name == pName)
				{
					return i;
				}

				i++;
			}

			return HIO_SERVICE_INVALID;
		}

		const char* GetServiceId(int id) const
		{
			if (id >= m_Services.size())
				return nullptr;

			return m_Services[id].m_Name;
		}
	};
}