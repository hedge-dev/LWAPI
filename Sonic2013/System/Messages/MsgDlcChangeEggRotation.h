#pragma once

namespace app::xgame
{
	class MsgDlcChangeEggRotation : public fnd::Message
	{
	public:
		bool IsEnter{};

		inline const static unsigned int MessageID = 0x611A;
		
		MsgDlcChangeEggRotation() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgDlcChangeEggRotation(*this);
		}
	};
}