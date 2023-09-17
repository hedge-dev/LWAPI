#pragma once

namespace app::xgame
{
	class MsgLoftBirdCollision : public fnd::Message
	{
	public:
		int ActionType{};

		inline const static unsigned int MessageID = 0x6121;

		MsgLoftBirdCollision() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgLoftBirdCollision(*this);
		}
	};
}