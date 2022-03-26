#pragma once

namespace app::xgame
{
	class MsgCatchEndPlayer : public fnd::Message
	{
	public:
		INSERT_PADDING(4);

		inline const static unsigned int MessageID = 0x601D;
		
		MsgCatchEndPlayer() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgCatchEndPlayer(*this);
		}
	};
}