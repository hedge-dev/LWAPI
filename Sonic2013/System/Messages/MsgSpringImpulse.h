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
		INSERT_PADDING(4);
		float m_OutOfParkour{};
		csl::ut::Bitset<uint> field_50{};
		INSERT_PADDING(28);

		inline const static unsigned int MessageID = 0x6000;
		
		MsgSpringImpulse(const csl::math::Vector3& rOrigin, const csl::math::Vector3& rDirection, float outOfControl, float speedDropoffTime) : fnd::Message(MessageID)
		{
			m_Origin = rOrigin;
			m_Direction = rDirection;
			m_OutOfControl = outOfControl;
			m_SpeedDropoffTime = speedDropoffTime;

			field_50.reset();
			field_50.set(2);
			field_50.set(3);
			field_50.set(5);
		}

		Message* Clone() override
		{
			return new MsgSpringImpulse(*this);
		}
	};
}