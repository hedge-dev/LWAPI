#pragma once

namespace app::xgame
{
	class MsgHudUnderWater : public fnd::Message
	{
	public:
		float RestTime{};
		bool Unk1{};

		inline const static unsigned int MessageID = 0xC012;

		MsgHudUnderWater(bool in_unk, float in_restTime) : Message(MessageID), RestTime(in_restTime), Unk1(in_unk)
		{
			
		}

		Message* Clone() override
		{
			return new MsgHudUnderWater(*this);
		}
	};
}