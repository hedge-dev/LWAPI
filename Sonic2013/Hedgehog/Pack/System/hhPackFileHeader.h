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
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpConvertEndian, ASLR(0x00C1A620), PackFileHeaderDataTag**);

	public:
		size_t Signature{};
		char Version[3]{};
		EEndianType Endian{};
		size_t Size{};
		ushort BlockCount{};
		char Status{};
		char RemainingDepends{};

	public:
		void ConvertEndian()
		{
			auto* pTemp = this;
			ms_fpConvertEndian(&pTemp);
		}
	};
}