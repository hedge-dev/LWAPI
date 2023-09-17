#pragma once

namespace app::xgame
{
	class MsgDead : public fnd::Message
	{
		typedef int EDeadType;

	public:
		EDeadType DeadType{};
		csl::math::Vector3 Unk1{};
		csl::math::Vector3 Unk2{};

		inline const static unsigned int MessageID = 0x4004;

		MsgDead(EDeadType in_deadType) : Message(MessageID), DeadType(in_deadType)
		{

		}

		Message* Clone() override
		{
			return new MsgDead(*this);
		}
	};
}