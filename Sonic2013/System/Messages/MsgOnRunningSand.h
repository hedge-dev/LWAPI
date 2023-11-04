#pragma once

namespace app::xgame
{
	class MsgOnRunningSand : public fnd::Message
	{
	public:
		csl::math::Vector3 Unk1{};
		csl::math::Vector3 Unk2{};
		int Unk3{};

		inline const static unsigned int MessageID = 0x6071;

		MsgOnRunningSand() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgOnRunningSand(*this);
		}
	};
}