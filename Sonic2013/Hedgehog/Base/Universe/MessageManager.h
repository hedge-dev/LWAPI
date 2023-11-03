#pragma once

namespace app::fnd
{
	class CActor;
	
	class MessageManager : public ReferencedObject, public csl::fnd::SingletonPointer<MessageManager>
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpRemove, ASLR(0x0049A910), MessageManager*, CActor*);

	public:
		size_t NextID{};
		csl::ut::PointerMap<size_t, CActor*> Actors{ GetAllocator() };
		csl::ut::MoveArray<Message*> Messages{ GetAllocator() };
		csl::ut::MoveArray<Message*> ExecutingMessages{ GetAllocator() };
		void* pUnk1{};
		
		size_t GenerateID()
		{
			return NextID++;
		}
		
		MessageManager()
		{
			Actors.reserve(1024);
			Messages.reserve(512);
			ExecutingMessages.reserve(512);
		}
		
		void AddMessage(Message& in_rMessage)
		{
			auto* pMessage = in_rMessage.Clone();

			if (pMessage)
				Messages.push_back(pMessage);
		}

		const csl::ut::PointerMap<size_t, CActor*>& Actors() const
		{
			return Actors;
		}
		
		void Update();
		
		void Add(CActor* in_pActor);

		void Remove(CActor* in_pActor);
		
		[[nodiscard]] CActor* GetActor(uint in_id) const
		{
			const auto result = Actors.find(in_id);

			if (result != Actors.end())
				return result;

			return nullptr;
		}
	};
}

#include "hhActor.h"
inline void app::fnd::MessageManager::Add(CActor* in_pActor)
{
	if (!in_pActor)
		return;

	in_pActor->ActorID = GenerateID();
	in_pActor->pMessageManager = this;
	Actors.insert(actor->ActorID, actor);
}


inline void app::fnd::MessageManager::Remove(CActor* in_pActor)
{
	ms_fpRemove(this, in_pActor);

	// TODO: erase is broken, fix it
	/*if (!actor)
		return;

	m_Actors.erase(actor->m_ActorID);
	actor->m_ActorID = 0;
	actor->m_pMessageManager = nullptr;*/
}

inline void app::fnd::MessageManager::Update()
{
	if (Messages.empty())
		return;

	ExecutingMessages.swap(Messages);
	
	for (Message* pMessage : ExecutingMessages)
	{
		CActor* pActor = GetActor(pMessage->Receiver);
		if (pActor)
		{
			pActor->ActorProc(pMessage->Broadcasted != false, pMessage);
		}

		delete pMessage;
	}

	ExecutingMessages.clear();
}

DEFINE_SINGLETONPTR(app::fnd::MessageManager, ASLR(0x00FD4300));