#pragma once

namespace app::fnd
{
	class RflClassMember;
	
	class RflClass
	{
	protected:
		const char* m_pName{};
		const RflClass* m_pParent{};
		size_t m_ClassSize{};
		const RflClassEnum* m_pEnums{};
		size_t m_EnumCount{};
		const RflClassMember* m_pMembers{};
		size_t m_MemberCount{};
		const RflCustomAttributes* m_pAttributes{};

	public:
		RflClass(const char* pName, 
			const RflClass* pParent,
			size_t objectSizeInBytes,
			const RflClassEnum* pDeclaredEnums,
			size_t declaredEnumsNum,
			const RflClassMember* pDeclaredMembers,
			size_t declaredMembersNum,
			const RflCustomAttributes* pAttributes)
		{
			m_pName = pName;
			m_pParent = pParent;
			m_ClassSize = objectSizeInBytes;
			m_pEnums = pDeclaredEnums;
			m_EnumCount = declaredEnumsNum;
			m_pMembers = pDeclaredMembers;
			m_MemberCount = declaredMembersNum;
			m_pAttributes = pAttributes;
		}
		
		[[nodiscard]] const char* GetName() const
		{
			return m_pName;
		}

		[[nodiscard]] const RflClass* GetBaseType() const
		{
			return m_pParent;
		}

		[[nodiscard]] size_t GetSizeInBytes() const
		{
			return m_ClassSize;
		}
		
		[[nodiscard]] size_t GetNumMembers() const
		{
			size_t count = m_MemberCount;

			for (const RflClass* base = m_pParent; base != nullptr; base = base->m_pParent)
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

				cls = cls->m_pParent;
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