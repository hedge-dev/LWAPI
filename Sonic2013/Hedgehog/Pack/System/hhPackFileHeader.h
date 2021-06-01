#pragma once

namespace hh::ut
{
	enum class EEndianType : char
	{
		eEndianType_Big = 'B',
		eEndianType_Little = 'L'
	};
	
	struct PackFileHeaderDataTag
	{
		size_t m_Signature{};
		char m_Version[3]{};
		EEndianType m_Endian{};
		size_t m_Size{};
		ushort m_BlockCount{};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpConvertEndian, ASLR(0x00C1A620), PackFileHeaderDataTag**);
		
	public:
		void ConvertEndian()
		{
			auto* pTemp = this;
			ms_fpConvertEndian(&pTemp);
		}
	};
}