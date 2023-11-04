#pragma once

namespace app::xgame
{
	class MsgSuspendWorld : public fnd::Message
	{
	public:
		float Time{};
		size_t Flags{};
		
		inline const static unsigned int MessageID = 0x300D;

		MsgSuspendWorld(float in_time) : Message(MessageID)
		{
			Time = in_time;
		}

		Message* Clone() override
		{
			return new MsgSuspendWorld(*this);
		}
	};
}