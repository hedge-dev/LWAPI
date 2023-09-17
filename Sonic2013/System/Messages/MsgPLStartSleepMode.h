#pragma once

namespace app::xgame
{
	class MsgPLStartSleepMode : public fnd::Message
	{
	public:
		csl::ut::Bitset<uint> Flags{};
		const csl::math::Vector3* Position{};
		const csl::math::Quaternion* Rotation{};
		
		inline const static unsigned int MessageID = 0x502D;
		
		MsgPLStartSleepMode(bool in_unk) : Message(MessageID)
		{
			Flags.set(0, in_unk);
		}

		MsgPLStartSleepMode(bool in_unk, const csl::math::Vector3& in_rPosition, const csl::math::Quaternion& in_rRotation)
			: Message(MessageID)
			, Position(&in_rPosition)
			, Rotation(&in_rRotation)
		{
			Flags.set(0, in_unk);
			Flags.set(1, true);
		}

		Message* Clone() override
		{
			return new MsgPLStartSleepMode(*this);
		}
	};
}