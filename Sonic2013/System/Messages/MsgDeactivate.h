#pragma once

namespace app::xgame
{
	class MsgDeactivate : public fnd::Message
	{
	public:
		bool m_Deactivate{ true };
		inline static unsigned int MessageID = 0x4005;

		MsgDeactivate() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgDeactivate(*this);
		}
	};
}
