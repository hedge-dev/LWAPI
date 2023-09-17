#pragma once

namespace app::xgame
{
	class MsgPressedBySnowBall : public fnd::Message
	{
	public:
		csl::math::Matrix34 Mtx{};
		GameObject* pSnowBall{}; // app::Player::CSnowBall*;

		inline const static unsigned int MessageID = 0x6085;

		MsgPressedBySnowBall() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPressedBySnowBall(*this);
		}
	};
}