#pragma once

namespace app::xgame
{
	class MsgRcUnlockAbility : public fnd::Message
	{
	public:
		enum UnlockType
		{

		};

		csl::ut::Enum<UnlockType, byte> Type{};

		inline const static unsigned int MessageID = 0x60E6;

		MsgRcUnlockAbility() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgRcUnlockAbility(*this);
		}
	};
}