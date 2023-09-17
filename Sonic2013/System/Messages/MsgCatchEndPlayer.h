#pragma once

namespace app::xgame
{
	class MsgCatchEndPlayer : public fnd::Message
	{
	public:
		bool Unk1{};

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