#pragma once

namespace app::xgame
{
	class MsgNotifyObjectEvent : public fnd::Message
	{
	public:
		typedef uint EEventType;

	private:
		EEventType eventType;
		
	public:
		inline static uint MessageID = 0x6013;

		MsgNotifyObjectEvent(EEventType type) : Message(MessageID)
		{
			eventType = type;
		}

		Message* Clone() override
		{
			auto* msg = new MsgNotifyObjectEvent(*this);
			msg->eventType = eventType;
			return msg;
		}

		[[nodiscard]] EEventType GetEventType() const
		{
			return eventType;
		}
	};
}