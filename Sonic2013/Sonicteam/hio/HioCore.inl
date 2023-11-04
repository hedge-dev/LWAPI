#pragma once

namespace csl::hio
{
	inline HioError HioCore::MakePacketHeader(const char* in_pService, const char* in_pCommand, uint in_a3, int in_size, PacketHeader* out_pOutHeader)
	{
		out_pOutHeader->ServiceName = in_pService;
		out_pOutHeader->CommandName = in_pCommand;
		out_pOutHeader->Unk1 = htonl(in_a3);
		out_pOutHeader->Size = htonl(in_size);
		
		return HIO_ERROR_OK;
	}

	inline HioError HioCore::GetPacketHeader(const void* in_pData, PacketHeader* out_pOutHeader)
	{
		const PacketHeader* pHeader = static_cast<const PacketHeader*>(in_pData);
		out_pOutHeader->ServiceName = pHeader->ServiceName.c_str();
		out_pOutHeader->CommandName = pHeader->CommandName.c_str();
		out_pOutHeader->Unk1 = ntohl(pHeader->Unk1);
		out_pOutHeader->Size = ntohl(pHeader->Size);
		
		return HIO_ERROR_OK;
	}

	inline PacketHeader* HioCore::RecvAllAlloc(NetworkSocket in_sock, int* out_pOutBytesReceived, HioError* out_pOutError)
	{
		*out_pOutBytesReceived = 0;
		*out_pOutError = HIO_ERROR_OK;
		PacketHeader header{};
		int received = recv(in_sock, (char*)&header, sizeof(header), 0);
		char* pBuf{};
		int size{};
		
		if (received == sizeof(header))
		{
			size = ntohl(header.m_Size);
			pBuf = (char*)m_pAllocator->Alloc(size, 16);
			if (!pBuf)
			{
				*out_pOutError = HIO_ERROR_OUTOFMEMORY;
				return nullptr;
			}
			
			memcpy(pBuf, &header, sizeof(header));
		}else
		{
			*out_pOutError = HIO_ERROR_RECVERROR;
			return nullptr;
		}
		
		*out_pOutBytesReceived = received;

		while (received < size)
		{
			int nextRecv = recv(in_sock, pBuf + received, size - received, 0);
			if (nextRecv < 0)
			{
				*out_pOutError = HIO_ERROR_RECVERROR;
				break;
			}
			
			received += nextRecv;
		}
		
		return (PacketHeader*)pBuf;
	}
}
