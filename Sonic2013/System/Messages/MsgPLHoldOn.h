#pragma once

namespace app::xgame
{
	class MsgPLHoldOn : public fnd::Message
	{
	public:
		int Unk1{};

		inline const static unsigned int MessageID = 0x5079;
		
		MsgPLHoldOn() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgPLHoldOn(*this);
		}
	};
}