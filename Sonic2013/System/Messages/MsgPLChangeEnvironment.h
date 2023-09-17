#pragma once

namespace app::xgame
{
	class MsgPLChangeEnvironment : public fnd::Message
	{
	public:
		typedef int Environment;

		Environment NewEnvironmnent{};

		inline const static unsigned int MessageID = 0x5028;

		MsgPLChangeEnvironment(Environment in_environment) : Message(MessageID), NewEnvironmnent(in_environment)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLChangeEnvironment(*this);
		}
	};
}