#pragma once

namespace csl::hio
{
	inline HioError HioCore::MakePacketHeader(const char* pService, const char* pCommand, uint a3, int size, PacketHeader* pOutHeader)
	{
		pOutHeader->m_ServiceName = pService;
		pOutHeader->m_CommandName = pCommand;
		pOutHeader->m_Unk1 = htonl(a3);
		pOutHeader->m_Size = htonl(size);
		
		return HIO_ERROR_OK;
	}

	inline HioError HioCore::GetPacketHeader(const void* pData, PacketHeader* pOutHeader)
	{
		const PacketHeader* pHeader = static_cast<const PacketHeader*>(pData);
		pOutHeader->m_ServiceName = pHeader->m_ServiceName.c_str();
		pOutHeader->m_CommandName = pHeader->m_CommandName.c_str();
		pOutHeader->m_Unk1 = ntohl(pHeader->m_Unk1);
		pOutHeader->m_Size = ntohl(pHeader->m_Size);
		
		return HIO_ERROR_OK;
	}

	inline PacketHeader* HioCore::RecvAllAlloc(NetworkSocket sock, int* pOutBytesReceived, HioError* pOutError)
	{
		*pOutBytesReceived = 0;
		*pOutError = HIO_ERROR_OK;
		PacketHeader header{};
		int received = recv(sock, (char*)&header, sizeof(header), 0);
		char* pBuf{};
		int size{};
		
		if (received == sizeof(header))
		{
			size = ntohl(header.m_Size);
			pBuf = (char*)m_pAllocator->Alloc(size, 16);
			if (!pBuf)
			{
				*pOutError = HIO_ERROR_OUTOFMEMORY;
				return nullptr;
			}
			
			memcpy(pBuf, &header, sizeof(header));
		}else
		{
			*pOutError = HIO_ERROR_RECVERROR;
			return nullptr;
		}
		
		*pOutBytesReceived = received;

		while (received < size)
		{
			int nextRecv = recv(sock, pBuf + received, size - received, 0);
			if (nextRecv < 0)
			{
				*pOutError = HIO_ERROR_RECVERROR;
				break;
			}
			
			received += nextRecv;
		}
		
		return (PacketHeader*)pBuf;
	}
}
