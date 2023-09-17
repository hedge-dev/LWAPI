#pragma once

namespace app::xgame
{
	class MsgRemovedFromSnowBall : public fnd::Message
	{
	public:
		bool IsRemoved;

		inline const static unsigned int MessageID = 0x60F6;

		MsgRemovedFromSnowBall() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgRemovedFromSnowBall(*this);
		}
	};
}