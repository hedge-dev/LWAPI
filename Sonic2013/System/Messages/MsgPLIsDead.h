#pragma once

namespace app::xgame
{
	class MsgPLIsDead : public fnd::Message
	{
	public:
		bool IsDead{};
		
		inline const static unsigned int MessageID = 0x5054;
		
		MsgPLIsDead() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgPLIsDead(*this);
		}
	};
}