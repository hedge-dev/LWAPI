#pragma once

namespace app::xgame
{
	class MsgRcGetHomingTargetInfo : public fnd::Message
	{
	public:
		csl::math::Vector3 Unk1{};
		csl::ut::Bitset<uint32> Unk2{};

		inline const static unsigned int MessageID = 0x60E8;

		MsgRcGetHomingTargetInfo() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgRcGetHomingTargetInfo(*this);
		}
	};
}