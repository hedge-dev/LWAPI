#pragma once

namespace app::xgame
{
	class MsgShowHintMessage : public app::fnd::Message
	{
	public:
		inline static uint MessageID = 0x3023;
		size_t m_Hide{};

		MsgShowHintMessage(bool hide) : Message(MessageID)
		{
			m_Hide = hide;
		}

		Message* Clone() override
		{
			return new MsgShowHintMessage(*this);
		}
	};
}