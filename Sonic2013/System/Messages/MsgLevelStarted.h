#pragma once

namespace app::xgame
{
	class MsgLevelStarted : public fnd::Message
	{
	public:
		inline static uint MessageID = 0x3007;

		MsgLevelStarted() : fnd::Message(MessageID)
		{

		}
	};
}