#pragma once

namespace app::xgame
{
	class MsgGoalForBattle : public fnd::Message
	{
	public:
		uint WinnerPlayerNo{};
		csl::math::Matrix34 TrsMatrixP1{};
		csl::math::Matrix34 TrsMatrixP2{};

		inline const static unsigned int MessageID = 0x300B;

		MsgGoalForBattle() : Message(MessageID)
		{
	
		}

		Message* Clone() override
		{
			return new MsgGoalForBattle(*this);
		}
	};
}