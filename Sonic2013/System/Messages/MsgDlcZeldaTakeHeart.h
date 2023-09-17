#pragma once

namespace app::xgame
{
	class MsgDlcZeldaTakeHeart : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x611B;
		
		MsgDlcZeldaTakeHeart() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgDlcZeldaTakeHeart(*this);
		}
	};
}