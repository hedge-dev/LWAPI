#pragma once

namespace app::xgame
{
	class MsgShowHintMessage : public app::fnd::Message
	{
	public:
		size_t Hide{};
		
		inline const static unsigned int MessageID = 0x3023;

		MsgShowHintMessage(bool in_hide) : Message(MessageID)
		{
			Hide = in_hide;
		}

		Message* Clone() override
		{
			return new MsgShowHintMessage(*this);
		}
	};
}