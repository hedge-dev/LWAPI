#pragma once

namespace app::xgame
{
	class MsgOnRunningSand : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x6071;

		csl::math::Vector3 Unk1{};
		csl::math::Vector3 Unk2{};
		int Unk3{};

		MsgOnRunningSand() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgOnRunningSand(*this);
		}
	};
}