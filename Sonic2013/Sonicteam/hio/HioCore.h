#pragma once

#define MAKE_FLAG(F) (1 << F)

#define HIO_ERROR_OK                       0
#define HIO_ERROR_OPENFAIL                -1
#define HIO_ERROR_CLEANUPFAIL             -2
#define HIO_ERROR_SOCKOPEN                -3
#define HIO_ERROR_SOCKCLOSE               -4
#define HIO_ERROR_BINDFAIL                -5
#define HIO_ERROR_LISTENFAIL              -6
#define HIO_ERROR_CONNECTFAIL             -7
#define HIO_ERROR_SELECTFAIL              -8
#define HIO_ERROR_ACCEPTFAIL              -9
#define HIO_ERROR_OUTOFMEMORY             -12
#define HIO_ERROR_RECVERROR               -13
#define HIO_ERROR_SENDERROR               -15
#define HIO_ERROR_TOOMANYCLIENTS          -16
#define HIO_ERROR_NOSOCKETS               -17

#define HIO_FLAG_INIT                     MAKE_FLAG(0)
#define HIO_FLAG_SOCKINIT                 MAKE_FLAG(2)
#define HIO_FLAG_SOCKCONNECTED            MAKE_FLAG(6)
#define HIO_FLAG_SERVER                   MAKE_FLAG(7)
#define HIO_FLAG_INITEX                   MAKE_FLAG(8)

typedef signed HioError;

namespace csl::hio
{
	typedef SOCKET NetworkSocket;
	struct PacketHeader;
	class HioCore
	{
	protected:
		csl::fnd::IAllocator* m_pAllocator{};
		NetworkSocket m_Socket{};
		ut::FixedString<64> m_Address{ "unknown"};
		ushort m_Port{};
		HioError m_LastError{ HIO_ERROR_OK };
		uint m_Flags{};
	
	public:
		virtual ~HioCore() = default;

		HioCore(csl::fnd::IAllocator* in_pAlloc)
		{
			m_pAllocator = in_pAlloc;
		}
	
	protected:
		inline void SetFlag(uint in_flag, bool in_value)
		{
			if (in_value)
				m_Flags |= in_flag;
			else
				m_Flags &= ~in_flag;
		}

		inline void SetServer(bool in_value)
		{
			SetFlag(HIO_FLAG_SERVER, in_value);
		}
	
	public:
		inline bool TestFlag(uint in_flag) const
		{
			return m_Flags & in_flag;
		}

	protected:
		virtual HioError PollCore()
		{
			return HIO_ERROR_OK;
		};

		virtual HioError StartupCore(const char* in_pAddress, ushort in_port)
		{
			return HIO_ERROR_OK;
		}

		virtual HioError CleanupCore()
		{
			return HIO_ERROR_OK;
		}
	
	public:
		inline NetworkSocket GetSocket() const  { return m_Socket;                  }
		inline HioError GetLastError() const    { return m_LastError;               }

		inline bool IsServer() const            { return TestFlag(HIO_FLAG_SERVER); }
		inline bool IsInit() const              { return TestFlag(HIO_FLAG_INIT);   }
		inline bool IsInitEx() const            { return TestFlag(HIO_FLAG_INITEX); }
		
		bool Startup(const char* in_pAddress, ushort in_port)
		{
			m_LastError = StartupCore(in_pAddress, in_port);
			return m_LastError == HIO_ERROR_OK;
		}

		bool Cleanup()
		{
			m_LastError = CleanupCore();
			return m_LastError == HIO_ERROR_OK;
		}

		HioError DisconnectSocket()
		{
			HioError result = HIO_ERROR_OK;

			if (TestFlag(HIO_FLAG_SOCKCONNECTED))
			{
				if (closesocket(m_Socket) == SOCKET_ERROR)
					result = HIO_ERROR_SOCKCLOSE;
				
				SetFlag(HIO_FLAG_SOCKCONNECTED, false);
				SetFlag(HIO_FLAG_INIT, false);
			}

			if (TestFlag(HIO_FLAG_SOCKINIT))
			{
				if (WSACleanup() == SOCKET_ERROR)
					result = HIO_ERROR_CLEANUPFAIL;
				
				SetFlag(HIO_FLAG_SOCKINIT, false);
			}
			
			return result;
		}
		
		HioError ConnectSocket(const char* in_pAddress, ushort in_port)
		{
			if (TestFlag(HIO_FLAG_SOCKCONNECTED))
				return HIO_ERROR_OK;

			m_Port = in_port;
			NetworkSocket sock = socket(AF_INET, SOCK_STREAM, 0);
			if (sock == -1)
				return HIO_ERROR_SOCKOPEN;

			sockaddr_in addr{};
			addr.sin_family = AF_INET;
			addr.sin_port = htons(in_port);

			if (IsServer())
			{
				if (bind(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
				{
					closesocket(sock);
					return HIO_ERROR_BINDFAIL;
				}
				
				if (listen(sock, 5) == SOCKET_ERROR)
				{
					closesocket(sock);
					return HIO_ERROR_LISTENFAIL;
				}
			}
			else
			{
				addr.sin_addr.S_un.S_addr = inet_addr(in_pAddress);
				m_Address = pAddress;
				if (connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0)
				{
					closesocket(sock);
					return HIO_ERROR_CONNECTFAIL;
				}
			}

			SetFlag(HIO_FLAG_SOCKCONNECTED | HIO_FLAG_INIT, true);
			m_Socket = sock;
			return HIO_ERROR_OK;
		}
		
		HioError SocketInit(const char* in_pAddress, ushort in_port)
		{
			if (!TestFlag(HIO_FLAG_SOCKINIT))
			{
				WSADATA wsaData;
				if (WSAStartup(MAKEWORD(2, 2), &wsaData))
					return HIO_ERROR_OPENFAIL;

				SetFlag(HIO_FLAG_SOCKINIT, true);
			}
			
			SetFlag(HIO_FLAG_INITEX, true);
			return ConnectSocket(in_pAddress, in_port);
		}
		
		HioError Poll()
		{
			m_LastError = PollCore();
			return m_LastError;
		}

		int SendAll(NetworkSocket in_sock, const void* in_pData, int in_dataSize, HioError* in_pOutError)
		{
			int bytesSent = 0;
			if (in_pOutError)
				in_pOutError = HIO_ERROR_OK;

			if (in_dataSize <= 0)
				return 0;
			
			while (bytesSent < in_dataSize)
			{
				int sent = send(in_sock, ((const char*)in_pData) + bytesSent, in_dataSize - bytesSent, 0);
				if (sent <= 0)
				{
					if (in_pOutError)
						*in_pOutError = HIO_ERROR_SENDERROR;

					break;
				}

				bytesSent += sent;
			}
			
			return bytesSent;
		}

		
		PacketHeader* RecvAllAlloc(NetworkSocket in_sock, int* in_pOutBytesReceived, HioError* in_pOutError);
		void RecvAllFree(void* in_pMem)
		{
			if (in_pMem)
				m_pAllocator->Free(in_pMem);
		}
		
		HioError MakePacketHeader(const char* in_pService, const char* in_pCommand, uint in_a3, int in_size, PacketHeader* in_pOutHeader);
		HioError GetPacketHeader(const void* in_pData, PacketHeader* in_pOutHeader);

		template<typename T>
		inline HioError MakePacketHeader(const char* in_pService, const char* in_pCommand, T& in_rOutHeader)
		{
			return MakePacketHeader(in_pService, in_pCommand, 0, sizeof(T), &in_rOutHeader);
		}
	};
}
