#pragma once

namespace app::xgame
{
	class MsgShakeCamera : public fnd::Message
	{
	public:
		float Unk1{ 1.0f };
		float Unk2{ 0.5f };
		int Unk3{ 10 };
		float Unk4{};
		float Unk5{ 0.25f };
		bool Unk6{};
		csl::math::Vector3 Unk7{};

		inline const static unsigned int MessageID = 0x8012;

		MsgShakeCamera() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgShakeCamera(*this);
		}
	};
}