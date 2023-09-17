#pragma once

namespace app::xgame
{
	class MsgBreakRollingStone : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x6052;

		MsgBreakRollingStone() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgBreakRollingStone(*this);
		}
	};
}