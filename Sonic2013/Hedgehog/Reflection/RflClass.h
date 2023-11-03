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
		RflClass(const char* in_pName, 
			const RflClass* in_pParent,
			size_t in_objectSizeInBytes,
			const RflClassEnum* in_pDeclaredEnums,
			size_t in_declaredEnumsNum,
			const RflClassMember* in_pDeclaredMembers,
			size_t in_declaredMembersNum,
			const RflCustomAttributes* in_pAttributes)
		{
			m_pName = in_pName;
			m_pParent = in_pParent;
			m_ClassSize = in_objectSizeInBytes;
			m_pEnums = in_pDeclaredEnums;
			m_EnumCount = in_declaredEnumsNum;
			m_pMembers = in_pDeclaredMembers;
			m_MemberCount = in_declaredMembersNum;
			m_pAttributes = in_pAttributes;
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

			for (const RflClass* pBase = m_pParent; pBase != nullptr; pBase = pBase->m_pParent)
			{
				count += pBase->m_MemberCount;
			}
			
			return count;
		}

		[[nodiscard]] const RflClassMember* GetMember(size_t in_index) const
		{
			const size_t num = GetNumMembers();

			if (in_index > num)
			{
				return nullptr;
			}

			const RflClass* cls = this;
			int j = in_index - num;

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

		[[nodiscard]] const RflClassMember* GetMemberByName(const char* in_pName) const
		{
			for (size_t i = 0; i < GetNumMembers(); i++)
			{
				const RflClassMember* pMember = GetMember(i);
				if (pMember->GetName() == in_pName || !strcmp(pMember->GetName(), in_pName))
				{
					return pMember;
				}				
			}
			
			return nullptr;
		}

		[[nodiscard]] size_t GetDeclaredMemberIndexByName(const char* in_pName) const
		{
			if (m_MemberCount <= 0)
				return -1;

			for (size_t i = 0; i < m_MemberCount; i++)
			{
				const auto* pMemberName = m_pMembers[i].GetName();
				if (pMemberName == in_pName || !strcmp(pMemberName, in_pName))
				{
					return i;
				}
			}
			
			return -1;
		}

		[[nodiscard]] const RflClassMember* GetDeclaredMemberByName(const char* in_pName) const
		{
			const size_t i = GetDeclaredMemberIndexByName(in_pName);

			if (i == static_cast<size_t>(-1))
				return nullptr;

			return &m_pMembers[i];
		}
		
		[[nodiscard]] const RflCustomAttribute* GetAttribute(const char* in_pName) const
		{
			if (!m_pAttributes)
				return nullptr;

			return m_pAttributes->GetAttribute(in_pName);
		}
	};
}