#pragma once

namespace app::xgame
{
	class MsgPlayerReachGoal : public fnd::Message
	{
	public:
		int Unk1{};
		csl::math::Vector3 Unk2{};
		csl::math::Vector3 Unk3{};

		inline const static unsigned int MessageID = 0x507B;
		
		MsgPlayerReachGoal() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgPlayerReachGoal(*this);
		}
	};
}