#pragma once

namespace app::xgame
{
	class MsgRestrictWarp : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x50A1;

		MsgRestrictWarp() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgRestrictWarp(*this);
		}
	};
}