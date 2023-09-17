#pragma once

namespace app::xgame
{
	class MsgPLVisibleItemEffect : public fnd::Message
	{
	public:
		bool IsVisible{};
		
		inline const static unsigned int MessageID = 0x50A4;
		
		MsgPLVisibleItemEffect() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgPLVisibleItemEffect(*this);
		}
	};
}