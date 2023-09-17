#pragma once

namespace app::xgame
{
	class MsgPLEnableSearchAllDirections : public fnd::Message
	{
	public:
		bool IsEnabled{};

		inline const static unsigned int MessageID = 0x507D;

		MsgPLEnableSearchAllDirections() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLEnableSearchAllDirections(*this);
		}
	};
}