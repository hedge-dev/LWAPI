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
		const RflClassEnumMember* GetValues() const
		{
			return m_pValues;
		}

		size_t GetValueCount() const
		{
			return m_MemberCount;
		}

		bool GetNameOfValue(size_t in_value, const char** in_ppName) const
		{
			if (m_MemberCount <= 0)
				return false;

			if (!in_ppName)
				return false;
			
			for (size_t i = 0; i < m_MemberCount; i++)
			{
				const RflClassEnumMember* p_member = &m_pValues[i];
				
				if (p_member->GetValue() == in_value)
				{
					*in_ppName = p_member->GetName();
					return true;
				}
			}
			
			return false;
		}

		bool GetValueOfName(const char* in_pName, size_t* in_pValue) const
		{
			if (m_MemberCount <= 0)
				return false;

			if (!in_pValue)
				return false;

			for (size_t i = 0; i < m_MemberCount; i++)
			{
				const RflClassEnumMember* pMember = &m_pValues[i];

				if (pMember->GetName() == in_pName || !strcmp(pMember->GetName(), in_pName))
				{
					*in_pValue = pMember->GetValue();
					return true;
				}
			}

			return false;
		}
	};
}