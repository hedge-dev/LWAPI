#pragma once

namespace app::xgame
{
	class MsgPLStagger : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x5085;

		MsgPLStagger() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLStagger(*this);
		}
	};
}