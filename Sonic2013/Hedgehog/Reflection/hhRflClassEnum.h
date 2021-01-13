#pragma once

namespace app::fnd
{
	class RflClassEnumMember
	{
	protected:
		const size_t m_value{};
		const char* p_name{};

	public:
		[[nodiscard]] const char* GetName() const
		{
			return p_name;
		}

		[[nodiscard]] size_t GetValue() const
		{
			return m_value;
		}
	};
	
	class RflClassEnum
	{
	protected:
		const char* p_name{};
		const RflClassEnumMember* p_values{};
		const size_t m_memberCount{};

	public:
		[[nodiscard]] bool GetNameOfValue(size_t value, const char** pp_name) const
		{
			if (m_memberCount <= 0)
				return false;

			if (!pp_name)
				return false;
			
			for (size_t i = 0; i < m_memberCount; i++)
			{
				const RflClassEnumMember* p_member = &p_values[i];
				
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
			if (m_memberCount <= 0)
				return false;

			if (!p_value)
				return false;

			for (size_t i = 0; i < m_memberCount; i++)
			{
				const RflClassEnumMember* p_member = &p_values[i];

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