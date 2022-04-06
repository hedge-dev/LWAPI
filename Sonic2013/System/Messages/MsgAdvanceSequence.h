#pragma once

namespace app::xgame
{
	class MsgAdvanceSequence : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x1004;

		MsgAdvanceSequence() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgAdvanceSequence(*this);
		}
	};
}