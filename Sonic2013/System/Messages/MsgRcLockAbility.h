#pragma once

namespace app::xgame
{
	class MsgRcLockAbility : public fnd::Message
	{
	public:
		enum LockType
		{

		};

		csl::ut::Enum<LockType, byte> Type{};

		inline const static unsigned int MessageID = 0x60E5;

		MsgRcLockAbility() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgRcLockAbility(*this);
		}
	};
}