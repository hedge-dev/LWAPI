#pragma once
#undef SendMessage

namespace app::fnd
{
	class CActor;

	// this class doesn't exist in the PC version at all and i don't know what to do with this
	class CActorTraverser : public ReferencedObject
	{
	public:
		virtual bool Callback(CActor& actor) = 0;
	};

	class CActor
	{
	protected:
		uint actorID{};
		MessageManager* messageManager{};
		CActor* parent{};
		unsigned short updateFlags{ 0 };
		char flags{ 1 };
		bool enabled{ true };
		unsigned int allowedMessageMask{ static_cast<unsigned>(-1) };
		bool isDeactivated{};

		void MessageSetup(uint to, fnd::Message& msg)
		{
			msg.receiver = to;
			msg.sender = actorID;
		}
		
	public:
		virtual ~CActor() = default;
		virtual void ForEach(CActorTraverser& traverser) = 0;

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

		virtual bool ActorProc(int id, void* data) = 0;

		void SetUpdateFlag(unsigned short flag, bool value)
		{
			char temp = 1 << flag;
			if (value)
				updateFlags |= temp;
			else
				updateFlags &= ~temp;
		}
		
		bool SendMessageImm(uint to, fnd::Message& msg)
		{
			if (msg.mask & allowedMessageMask)
			{
				MessageSetup(to, msg);
				CActor* actor = messageManager->GetActor(to);
				
				if (!actor)
					return false;

				return actor->ActorProc(0, &msg);
			}
			return false;
		}

		bool BroadcastMessageImm(uint group, fnd::Message& msg)
		{
			if (msg.mask & allowedMessageMask)
			{
				MessageSetup(group, msg);

				CActor* actor = messageManager->GetActor(group);

				if (!actor)
					return false;

				return actor->ActorProc(1, &msg);
			}
			
			return false;
		}
		
		bool SendMessage(fnd::Message& msg)
		{
			if (allowedMessageMask & msg.mask)
			{
				return ActorProc(0, &msg);
			}

			return false;
		}

		void SendMessage(uint to, fnd::Message& msg)
		{
			if (allowedMessageMask & msg.mask)
			{
				messageManager->AddMessage(msg);
			}
		}

		void BroadcastMessage(uint group, fnd::Message& msg)
		{
			MessageSetup(group, msg);
			msg.broadcasted = true;
			messageManager->AddMessage(msg);
		}
	};
}