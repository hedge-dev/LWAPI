#pragma once

namespace app::xgame
{
	class MsgSpringImpulse : public fnd::Message
	{
	public:
		INSERT_PADDING(8);
		csl::math::Vector3 Origin{};
		csl::math::Vector3 Direction{};
		float OutOfControl{};
		float SpeedDropoffTime{};
		float Unk1{};
		float OutOfParkour{};
		csl::ut::Bitset<uint> Flags{};
		bool IsHandled{};
		csl::math::Vector3 YawDirection{};

		inline const static unsigned int MessageID = 0x6000;
		
		MsgSpringImpulse(const csl::math::Vector3& in_rOrigin, const csl::math::Vector3& in_rDirection, float in_outOfControl, float in_speedDropoffTime) : fnd::Message(MessageID)
		{
			Origin = in_rOrigin;
			Direction = in_rDirection;
			OutOfControl = in_outOfControl;
			SpeedDropoffTime = in_speedDropoffTime;

			Flags.reset();
			Flags.set(2);
			Flags.set(3);
			Flags.set(5);
		}

		Message* Clone() override
		{
			return new MsgSpringImpulse(*this);
		}
	};
}