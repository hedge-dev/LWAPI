#pragma once

namespace app::xgame
{
	class MsgNotifyBossStart : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x5074;

		MsgNotifyBossStart() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgNotifyBossStart(*this);
		}
	};
}