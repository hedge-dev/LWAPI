#pragma once

namespace app::xgame
{
	class MsgRestrictWarpCancel : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x50A2;

		MsgRestrictWarpCancel() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgRestrictWarpCancel(*this);
		}
	};
}