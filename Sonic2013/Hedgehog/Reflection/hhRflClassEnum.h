#pragma once

namespace app::fnd
{
	class RflClassEnumMember
	{
	protected:
		const size_t m_Value{};
		const char* m_pName{};

	public:
		[[nodiscard]] const char* GetName() const
		{
			return m_pName;
		}

		[[nodiscard]] size_t GetValue() const
		{
			return m_Value;
		}
	};
	
	class RflClassEnum
	{
	protected:
		const char* m_pName{};
		const RflClassEnumMember* m_pValues{};
		const size_t m_MemberCount{};

	public:
		[[nodiscard]] bool GetNameOfValue(size_t value, const char** pp_name) const
		{
			if (m_MemberCount <= 0)
				return false;

			if (!pp_name)
				return false;
			
			for (size_t i = 0; i < m_MemberCount; i++)
			{
				const RflClassEnumMember* p_member = &m_pValues[i];
				
				if (p_member->GetValue() == value)
				{
					*pp_name = p_member->GetName();
					return true;
				}
			}
			
			return false;
		}

		[[nodiscard]] bool GetValueOfName(const char* name, size_t* p_value) const
		{
			if (m_MemberCount <= 0)
				return false;

			if (!p_value)
				return false;

			for (size_t i = 0; i < m_MemberCount; i++)
			{
				const RflClassEnumMember* p_member = &m_pValues[i];

				if (p_member->GetName() == name || !strcmp(p_member->GetName(), name))
				{
					*p_value = p_member->GetValue();
					return true;
				}
			}

			return false;
		}
	};
}