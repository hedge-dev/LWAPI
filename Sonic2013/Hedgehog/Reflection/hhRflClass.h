#pragma once

namespace app::fnd
{
	class RflClassMember;
	
	class RflClass
	{
	protected:
		const char* p_name{};
		const RflClass* m_baseClass{};
		const size_t m_classSize{};
		const RflClassEnum* p_enums{};
		const size_t m_enumCount{};
		const RflClassMember* p_members{};
		const size_t m_memberCount{};
		const RflCustomAttributes* p_attributes{};

	public:
		[[nodiscard]] const char* GetName() const
		{
			return p_name;
		}

		[[nodiscard]] const RflClass* GetBaseType() const
		{
			return m_baseClass;
		}

		[[nodiscard]] size_t GetSizeInBytes() const
		{
			return m_classSize;
		}
		
		[[nodiscard]] size_t GetNumMembers() const
		{
			size_t count = m_memberCount;

			for (const RflClass* base = m_baseClass; base != nullptr; base = base->m_baseClass)
			{
				count += base->m_memberCount;
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
				j += cls->m_memberCount;
				if (j >= 0)
					break;

				cls = cls->m_baseClass;
				if (!cls)
					return cls->p_members;
			}
			
			return &cls->p_members[j];
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
			if (m_memberCount <= 0)
				return -1;

			for (size_t i = 0; i < m_memberCount; i++)
			{
				const auto* memberName = p_members[i].GetName();
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

			return &p_members[i];
		}
		
		[[nodiscard]] const RflCustomAttribute* GetAttribute(const char* name) const
		{
			if (!p_attributes)
				return nullptr;

			return p_attributes->GetAttribute(name);
		}
	};
}