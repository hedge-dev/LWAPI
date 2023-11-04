#pragma once

namespace app::Gops
{
	class CActorManager;
	
	class CActorPack
	{
	public:
		csl::ut::LinkListNode ListNode{};

	protected:
		CActorManager* m_pManager{};
		size_t m_ObjectUID{};
		void* m_Unk1{};
		csl::ut::LinkList<CActor> m_Actors{ &CActor::ListNode };
		SetEd::CResObject m_Object{ nullptr };

	public:
		const csl::ut::LinkList<CActor>& GetActors() const
		{
			return m_Actors;
		}

		SetEd::CResObject GetObjectResource()
		{
			return m_Object;
		}

		size_t GetObjectUID() const
		{
			return m_ObjectUID;
		}
	};
}