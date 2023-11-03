#pragma once

namespace app::fnd
{
	class RflClass;
	class RflClassEnum;
	class RflCustomAttributes;
	
	struct RflClassMemberInternal
	{
		const char* pName{};
		RflClass* pClass{};
		RflClassEnum* pEnum{};
		uint8 Type{};
		uint8 SubType{};
		uint16 ArrayLength{};
		uint16 Flags{};
		uint16 Offset{};
		const RflCustomAttributes* pAttributes{};
	};
}