#pragma once

namespace app::game
{
	class PathComponent;
}

namespace app::xgame
{
	class MsgBeginGPathMode : public fnd::Message
	{
	public:
		fnd::Handle<game::PathComponent> Path{};

		inline const static unsigned int MessageID = 0x6049;

		MsgBeginGPathMode() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgBeginGPathMode(*this);
		}
	};
}