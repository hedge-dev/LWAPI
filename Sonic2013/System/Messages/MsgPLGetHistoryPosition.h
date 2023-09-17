#pragma once

namespace app::xgame
{
	class MsgPLGetHistoryPosition : public fnd::Message
	{
	public:
		csl::math::Vector3 HistoryPosition{};
		byte PositionIndex{};

		inline const static unsigned int MessageID = 0x5062;

		MsgPLGetHistoryPosition() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLGetHistoryPosition(*this);
		}
	};
}