#pragma once

namespace app::xgame
{
	class MsgLeaveEventCollision : public fnd::Message
	{
	public:
		fnd::Handle<game::ColliShape> Self{};
		INSERT_PADDING(8);
		size_t Sender{};

		inline const static unsigned int MessageID = 0x9001;

		MsgLeaveEventCollision() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgLeaveEventCollision(*this);
		}
	};
}