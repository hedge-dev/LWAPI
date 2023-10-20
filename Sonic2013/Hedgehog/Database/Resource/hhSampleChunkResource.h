#pragma once

namespace hh::db
{
	class CSampleChunkResource2
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpResolvePointer, ASLR(0x00C27CB0), CSampleChunkResource2*);

	public:
		uint32_t m_Size;
		uint32_t m_Signature;
		uint32_t m_OffsetTablePtr;
		uint32_t m_OffsetCount;

		void* GetData()
		{
			return reinterpret_cast<void*>(this + 1);
		}

		void ResolvePointer()
		{
			uint32_t* offsets = reinterpret_cast<uint32_t*>((char*)this + _byteswap_ulong(m_OffsetTablePtr));
			auto* data = (char*)GetData();

			for (size_t i = 0; i < _byteswap_ulong(m_OffsetCount); i++)
			{
				auto offset = _byteswap_ulong(offsets[i]);
				auto* ptr = data + offset;
				*(size_t*)ptr = (size_t)ptr;
			}
		}

		void UnresolvePointer()
		{
			uint32_t* offsets = reinterpret_cast<uint32_t*>((char*)this + _byteswap_ulong(m_OffsetTablePtr));
			auto* data = (char*)GetData();

			for (size_t i = 0; i < _byteswap_ulong(m_OffsetCount); i++)
			{
				auto offset = _byteswap_ulong(offsets[i]);
				auto* ptr = data + offset;
				*(size_t*)ptr = _byteswap_ulong((size_t)ptr - (size_t)data); // Re-save in flipped endianness
			}
		}
	};
}