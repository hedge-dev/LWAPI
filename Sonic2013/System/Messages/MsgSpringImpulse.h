#pragma once

namespace app::xgame
{
	class MsgSpringImpulse : public fnd::Message
	{
	public:
		INSERT_PADDING(8);
		csl::math::Vector3 m_Origin{};
		csl::math::Vector3 m_Direction{};
		float m_OutOfControl{};
		float m_SpeedDropoffTime{};
		float Unk1{};
		float m_OutOfParkour{};
		csl::ut::Bitset<uint> Flags{};
		bool IsHandled{};
		csl::math::Vector3 YawDirection{};

		inline const static unsigned int MessageID = 0x6000;
		
		MsgSpringImpulse(const csl::math::Vector3& rOrigin, const csl::math::Vector3& rDirection, float outOfControl, float speedDropoffTime) : fnd::Message(MessageID)
		{
			m_Origin = rOrigin;
			m_Direction = rDirection;
			m_OutOfControl = outOfControl;
			m_SpeedDropoffTime = speedDropoffTime;

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