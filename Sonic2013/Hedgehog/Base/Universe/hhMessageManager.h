#pragma once

namespace app::fnd
{
	class CActor;
	
	class MessageManager : public ReferencedObject, public csl::fnd::SingletonPointer<MessageManager>
	{
	protected:
		size_t m_NextID{};
		csl::ut::PointerMap<size_t, CActor*> m_Actors{ GetAllocator() };
		csl::ut::MoveArray<Message*> m_Messages{ GetAllocator() };
		csl::ut::MoveArray<Message*> m_ExecutingMessages{ GetAllocator() };
		void* m_Unk1{};
		
		size_t GenerateID()
		{
			return m_NextID++;
		}
		
	public:
		MessageManager()
		{
			m_Actors.reserve(1024);
			m_Messages.reserve(512);
			m_ExecutingMessages.reserve(512);
		}
		
		void AddMessage(Message& msg)
		{
			auto* pMsg = msg.Clone();

			if (pMsg)
				m_Messages.push_back(pMsg);
		}

		const csl::ut::PointerMap<size_t, CActor*>& Actors() const
		{
			return m_Actors;
		}
		
		void Update();
		
		void Add(CActor* actor);

		void Remove(CActor* actor);
		
		[[nodiscard]] CActor* GetActor(uint id) const
		{
			const auto result = m_Actors.find(id);

			if (result != m_Actors.end())
				return result;

			return nullptr;
		}
	};
}

#include "hhActor.h"
inline void app::fnd::MessageManager::Add(CActor* actor)
{
	if (!actor)
		return;

	actor->m_ActorID = GenerateID();
	actor->m_pMessageManager = this;
	m_Actors.insert(actor->m_ActorID, actor);
}


inline void app::fnd::MessageManager::Remove(CActor* actor)
{
	if (!actor)
		return;

	m_Actors.erase(actor->m_ActorID);
	actor->m_ActorID = 0;
	actor->m_pMessageManager = nullptr;
}

inline void app::fnd::MessageManager::Update()
{
	if (m_Messages.empty())
		return;

	m_ExecutingMessages.swap(m_Messages);
	
	for (Message* msg : m_ExecutingMessages)
	{
		CActor* pActor = GetActor(msg->m_Receiver);
		if (pActor)
		{
			pActor->ActorProc(msg->m_Broadcasted != false, msg);
		}

		delete msg;
	}

	m_ExecutingMessages.clear();
}


DEFINE_SINGLETONPTR(app::fnd::MessageManager, ASLR(0x00FD4300));