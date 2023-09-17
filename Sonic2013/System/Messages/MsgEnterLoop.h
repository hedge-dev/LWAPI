#pragma once

namespace app::xgame
{
	class MsgEnterLoop : public fnd::Message
	{
	public:
		fnd::Handle<game::PathComponent> PathComponent{};
		float Distance{};

		inline const static unsigned int MessageID = 0x606D;

		MsgEnterLoop() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgEnterLoop(*this);
		}
	};
}