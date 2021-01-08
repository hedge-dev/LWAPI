#pragma once

namespace app::xgame
{
	class MsgNotifyObjectEvent : public fnd::Message
	{
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
			return new MsgNotifyObjectEvent(eventType);
		}

		[[nodiscard]] EEventType GetEventType() const
		{
			return eventType;
		}
	};
}