#pragma once

namespace app::xgame
{
	class MsgPLStealth : public fnd::Message
	{
	public:
		bool IsStealth{};

		inline const static unsigned int MessageID = 0x5087;

		MsgPLStealth() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLStealth(*this);
		}
	};
}