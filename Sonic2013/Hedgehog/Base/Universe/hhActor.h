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
		virtual size_t Callback(CActor& actor) = 0;
	};

	// CActor : boost::noncopyable
	class CActor : public csl::ut::NonCopyable
	{
		friend MessageManager;
		
	protected:
		uint m_ActorID{};
		MessageManager* m_pMessageManager{};
		CActor* m_pParent{};
		csl::ut::Bitset<uint16> m_updateFlags {};
		char m_Flags{ 1 };
		bool m_Enabled{ true };
		unsigned int m_AllowedMessageFlags{ static_cast<unsigned>(-1) };
		bool isDeactivated{};

		void MessageSetup(uint to, fnd::Message& msg) const
		{
			msg.m_Receiver = to;
			msg.m_Sender = m_ActorID;
		}
		
	public:
		void RemoveFromAllParents()
		{
			if (m_pParent)
				m_pParent->ActorProc(2, this);
		}
		
		virtual ~CActor()
		{
			RemoveFromAllParents();
			if (m_pMessageManager)
				m_pMessageManager->Remove(this);
		}
		
		virtual size_t ForEach(CActorTraverser& traverser) = 0;

	protected:
		virtual bool PreProcessMessage(Message& msg)
		{
			return false;
		}

		virtual bool ProcessMessage(Message& msg)
		{
			return PreProcessMessage(msg);
		}

		virtual void Update(const SUpdateInfo& info)
		{

		}

	public:
		virtual bool ActorProc(int id, void* data) = 0;

		HH_FORCE_INLINE size_t GetID() const
		{
			return m_ActorID;
		}
		
		HH_FORCE_INLINE void SetUpdateFlag(uint16 flag, bool value)
		{
			m_updateFlags.set(flag, value);
		}

		HH_FORCE_INLINE bool GetUpdateFlag(uint16 flag) const
		{
			return m_updateFlags.test(flag);
		}

		void SetParent(CActor* pParent)
		{
			m_pParent = pParent;
		}
		
		bool SendMessageImm(uint to, fnd::Message& msg) const
		{
			if (msg.mask & m_AllowedMessageFlags)
			{
				MessageSetup(to, msg);
				CActor* actor = m_pMessageManager->GetActor(to);
				
				if (!actor)
					return false;

				return actor->ActorProc(0, &msg);
			}
			return false;
		}

		bool BroadcastMessageImm(uint group, fnd::Message& msg) const
		{
			if (msg.mask & m_AllowedMessageFlags)
			{
				MessageSetup(group, msg);

				CActor* actor = m_pMessageManager->GetActor(group);

				if (!actor)
					return false;

				return actor->ActorProc(1, &msg);
			}
			
			return false;
		}
		
		bool SendMessage(fnd::Message& msg)
		{
			if (m_AllowedMessageFlags & msg.mask)
			{
				MessageSetup(m_ActorID, msg);
				return ActorProc(0, &msg);
			}

			return false;
		}

		void SendMessage(uint to, fnd::Message& msg) const
		{
			if (m_AllowedMessageFlags & msg.mask)
			{
				MessageSetup(to, msg);
				m_pMessageManager->AddMessage(msg);
			}
		}

		void BroadcastMessage(uint group, fnd::Message& msg) const
		{
			MessageSetup(group, msg);
			msg.m_Broadcasted = true;
			m_pMessageManager->AddMessage(msg);
		}
	};
}

#pragma pop_macro("SendMessage")