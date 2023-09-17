#pragma once

namespace app::xgame
{
	class MsgPLSendGameInfo : public fnd::Message
	{
	public:
		Game::EUser PlayerNo{};
		float HorzVelocityLength{};
		int RingNum{};
		int NumHearts{};
		int MaxNumHearts{};

		inline const static unsigned int MessageID = 0x5013;

		MsgPLSendGameInfo(Game::EUser in_user, float in_horzVelLength, int in_ringNum, int in_numHearts, int in_maxNumHearts)
			: Message(MessageID)
			, PlayerNo(in_user)
			, HorzVelocityLength(in_horzVelLength)
			, RingNum(in_ringNum)
			, NumHearts(in_numHearts)
			, MaxNumHearts(in_maxNumHearts)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLSendGameInfo(*this);
		}
	};
}