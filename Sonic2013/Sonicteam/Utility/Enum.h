#pragma once

namespace csl::ut
{
	template<typename EnumType, typename UnderlayingType>
	class Enum
	{
	protected:
		UnderlayingType m_value;

	public:
		Enum(EnumType in_value)
		{
			m_value = static_cast<UnderlayingType>(in_value);
		}

		Enum() : Enum(EnumType{})
		{
			
		}
		
		operator UnderlayingType() const
		{
			return m_value;
		}
		
		operator EnumType() const
		{
			return static_cast<EnumType>(m_value);
		}
		
		Enum<EnumType, UnderlayingType>& operator=(const EnumType in_value)
		{
			m_value = static_cast<UnderlayingType>(in_value);
			return *this;
		}

		Enum<EnumType, UnderlayingType>& operator=(const UnderlayingType in_value)
		{
			m_value = in_value;
			return *this;
		}
	};
}