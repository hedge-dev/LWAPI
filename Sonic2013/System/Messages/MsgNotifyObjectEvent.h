#pragma once

namespace app::xgame
{
	class MsgNotifyObjectEvent : public fnd::Message
	{
	public:
		typedef uint EEventType;

		EEventType EventType;
		
		inline const static unsigned int MessageID = 0x6013;

		MsgNotifyObjectEvent(EEventType in_type) : Message(MessageID)
		{
			EventType = in_type;
		}

		Message* Clone() override
		{
			auto* msg = new MsgNotifyObjectEvent(*this);
			msg->EventType = EventType;
			return msg;
		}

		[[nodiscard]] EEventType GetEventType() const
		{
			return EventType;
		}
	};
}