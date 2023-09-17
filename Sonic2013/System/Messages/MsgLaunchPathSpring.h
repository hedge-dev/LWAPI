#pragma once

namespace app::xgame
{
	class MsgLaunchPathSpring : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x606C;

		csl::math::Vector3 Origin{};
		csl::math::Vector3 Direction{};
		float Unk1{};
		float Unk2{};
		bool Unk3{};

		MsgLaunchPathSpring() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgLaunchPathSpring(*this);
		}
	};
}