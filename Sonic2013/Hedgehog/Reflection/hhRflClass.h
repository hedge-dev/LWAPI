#pragma once

namespace app::fnd
{
	class RflClassMember;
	
	class RflClass
	{
	protected:
		const char* m_pName{};
		const RflClass* m_pBaseClass{};
		const size_t m_ClassSize{};
		const RflClassEnum* m_pEnums{};
		const size_t m_EnumCount{};
		const RflClassMember* m_pMembers{};
		const size_t m_MemberCount{};
		const RflCustomAttributes* m_pAttributes{};

	public:
		[[nodiscard]] const char* GetName() const
		{
			return m_pName;
		}

		[[nodiscard]] const RflClass* GetBaseType() const
		{
			return m_pBaseClass;
		}

		[[nodiscard]] size_t GetSizeInBytes() const
		{
			return m_ClassSize;
		}
		
		[[nodiscard]] size_t GetNumMembers() const
		{
			size_t count = m_MemberCount;

			for (const RflClass* base = m_pBaseClass; base != nullptr; base = base->m_pBaseClass)
			{
				count += base->m_MemberCount;
			}
			
			return count;
		}

		[[nodiscard]] const RflClassMember* GetMember(size_t i) const
		{
			const size_t num = GetNumMembers();

			if (i > num)
			{
				return nullptr;
			}

			const RflClass* cls = this;
			int j = i - num;

			while(true)
			{
				j += cls->m_MemberCount;
				if (j >= 0)
					break;

				cls = cls->m_pBaseClass;
				if (!cls)
					return cls->m_pMembers;
			}
			
			return &cls->m_pMembers[j];
		}

		[[nodiscard]] const RflClassMember* GetMemberByName(const char* name) const
		{
			for (size_t i = 0; i < GetNumMembers(); i++)
			{
				const RflClassMember* member = GetMember(i);
				if (member->GetName() == name || !strcmp(member->GetName(), name))
				{
					return member;
				}				
			}
			
			return nullptr;
		}

		[[nodiscard]] size_t GetDeclaredMemberIndexByName(const char* name) const
		{
			if (m_MemberCount <= 0)
				return -1;

			for (size_t i = 0; i < m_MemberCount; i++)
			{
				const auto* memberName = m_pMembers[i].GetName();
				if (memberName == name || !strcmp(memberName, name))
				{
					return i;
				}
			}
			
			return -1;
		}

		[[nodiscard]] const RflClassMember* GetDeclaredMemberByName(const char* name) const
		{
			const size_t i = GetDeclaredMemberIndexByName(name);

			if (i == static_cast<size_t>(-1))
				return nullptr;

			return &m_pMembers[i];
		}
		
		[[nodiscard]] const RflCustomAttribute* GetAttribute(const char* name) const
		{
			if (!m_pAttributes)
				return nullptr;

			return m_pAttributes->GetAttribute(name);
		}
	};
}