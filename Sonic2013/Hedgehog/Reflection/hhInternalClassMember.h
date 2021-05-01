#pragma once

namespace app::fnd
{
	class RflClass;
	class RflClassEnum;
	class RflCustomAttributes;
	
	struct RflClassMemberInternal
	{
		const char* m_pName{};
		RflClass* m_pClass{};
		RflClassEnum* m_pEnum{};
		uint8 m_Type{};
		uint8 m_SubType{};
		uint16 m_ArrayLength{};
		uint16 m_Flags{};
		uint16 m_Offset{};
		const RflCustomAttributes* m_pAttributes{};
	};
}