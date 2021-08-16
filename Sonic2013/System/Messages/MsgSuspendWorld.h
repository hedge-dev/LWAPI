#pragma once

namespace app::xgame
{
	class MsgSuspendWorld : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x300D;
		float m_Time{};
		size_t m_Flags{};
		
		MsgSuspendWorld(float time) : Message(MessageID)
		{
			m_Time = time;
		}

		Message* Clone() override
		{
			return new MsgSuspendWorld(*this);
		}
	};
}