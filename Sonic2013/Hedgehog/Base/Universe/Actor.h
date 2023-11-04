#pragma once
#pragma push_macro("SendMessage")
#undef SendMessage

namespace app::fnd
{
	class CActor;

	// this class doesn't exist in the PC version at all and i don't know what to do with this
	class CActorTraverser : public ReferencedObject
	{
	public:
		virtual size_t Callback(CActor& in_rActor) = 0;
	};

	// CActor : boost::noncopyable
	class CActor : public csl::ut::NonCopyable
	{
		friend MessageManager;
		
	public:
		uint ActorID{};
		MessageManager* pMessageManager{};
		CActor* pParent{};
		csl::ut::Bitset<uint16> UpdateFlags {};
		char Flags{ 1 };
		bool Enabled{ true };
		unsigned int AllowedMessageFlags{ static_cast<unsigned>(-1) };
		bool IsDeactivated{};

		void MessageSetup(uint in_to, fnd::Message& in_rMessage) const
		{
			in_rMessage.Receiver = in_to;
			in_rMessage.Sender = ActorID;
		}
		
	public:
		void RemoveFromAllParents()
		{
			if (pParent)
				pParent->ActorProc(2, this);
		}

		CActor()
		{
			SetUpdateFlag(0, true);
		}
		
		virtual ~CActor()
		{
			RemoveFromAllParents();
			if (pMessageManager)
				pMessageManager->Remove(this);
		}
		
		virtual size_t ForEach(CActorTraverser& in_rTraverser) = 0;

	protected:
		virtual bool PreProcessMessage(Message& in_rMessage)
		{
			return false;
		}

		virtual bool ProcessMessage(Message& in_rMessage)
		{
			return PreProcessMessage(in_rMessage);
		}

		virtual void Update(const SUpdateInfo& in_rUpdateInfo)
		{

		}

	public:
		virtual bool ActorProc(int in_id, void* in_pData) = 0;

		HH_FORCE_INLINE size_t GetID() const
		{
			return ActorID;
		}
		
		HH_FORCE_INLINE void SetUpdateFlag(uint16 in_flag, bool in_value)
		{
			UpdateFlags.set(in_flag, in_value);
		}

		HH_FORCE_INLINE bool GetUpdateFlag(uint16 in_flag) const
		{
			return UpdateFlags.test(in_flag);
		}

		void SetParent(CActor* in_pParent)
		{
			pParent = in_pParent;
		}
		
		bool SendMessageImm(uint in_to, fnd::Message& in_rMessage) const
		{
			if (in_rMessage.Mask & AllowedMessageFlags)
			{
				MessageSetup(in_to, in_rMessage);
				CActor* pActor = pMessageManager->GetActor(in_to);
				
				if (!pActor)
					return false;

				return pActor->ActorProc(0, &in_rMessage);
			}
			return false;
		}

		bool BroadcastMessageImm(uint in_group, fnd::Message& in_rMessage) const
		{
			if (in_rMessage.Mask & AllowedMessageFlags)
			{
				MessageSetup(in_group, in_rMessage);

				CActor* pActor = pMessageManager->GetActor(in_group);

				if (!pActor)
					return false;

				return pActor->ActorProc(1, &in_rMessage);
			}
			
			return false;
		}
		
		bool SendMessage(fnd::Message& in_rMessage)
		{
			if (AllowedMessageFlags & in_rMessage.Mask)
			{
				MessageSetup(ActorID, in_rMessage);
				return ActorProc(0, &in_rMessage);
			}

			return false;
		}

		void SendMessage(uint in_to, fnd::Message& in_rMessage) const
		{
			if (AllowedMessageFlags & in_rMessage.Mask)
			{
				MessageSetup(in_to, in_rMessage);
				pMessageManager->AddMessage(in_rMessage);
			}
		}

		void BroadcastMessage(uint in_group, fnd::Message& in_rMessage) const
		{
			MessageSetup(in_group, in_rMessage);
			in_rMessage.Broadcasted = true;
			pMessageManager->AddMessage(in_rMessage);
		}
	};
}

#pragma pop_macro("SendMessage")