#pragma once

namespace app::xgame
{
	class MsgStayTrigger : public fnd::Message
	{
	public:
		const game::ColliShape* Unk1{};
		int Unk2{};
		int Sender{};

		inline const static unsigned int MessageID = 0x9002;

		MsgStayTrigger() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgStayTrigger(*this);
		}
	};
}