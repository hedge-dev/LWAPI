#pragma once

namespace app::xgame
{
	class MsgPLIsDisableChangePhantomArea : public fnd::Message
	{
	public:
		bool IsDisable{};
		
		inline const static unsigned int MessageID = 0x5059;
		
		MsgPLIsDisableChangePhantomArea() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgPLIsDisableChangePhantomArea(*this);
		}
	};
}