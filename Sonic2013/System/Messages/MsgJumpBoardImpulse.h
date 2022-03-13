#pragma once

namespace app::xgame
{
	class MsgJumpBoardImpulse : public fnd::Message
	{
	public:
		MsgJumpBoardImpulse(unsigned int messageID) : fnd::Message(messageID){}

		Message* Clone() override
		{
			return new MsgJumpBoardImpulse(*this);
		}
	};

	class MsgJJumpBoardImpulse : public MsgJumpBoardImpulse
	{
	public:
		enum EType
		{
			eType_Default
		};
		
		INSERT_PADDING(8);
		csl::math::Vector3 m_Origin{};
		csl::math::Vector3 m_Direction{};
		csl::math::Vector3 m_BoostDirection{};
		float m_SpeedDropoffTime{};
		EType m_Type{};
		bool m_Unk3{};
		INSERT_PADDING(4);

		inline const static unsigned int MessageID = 0x6003;

		MsgJJumpBoardImpulse(const csl::math::Vector3& rOrigin, const csl::math::Vector3& rDir, const csl::math::Vector3& rBoostDir, EType type, float speedDropoffTime) : MsgJumpBoardImpulse(MessageID)
		{
			m_Origin = rOrigin;
			m_Direction = rDir;
			m_BoostDirection = rBoostDir;
			m_SpeedDropoffTime = speedDropoffTime;
			m_Type = type;
			m_Unk3 = false;
		}
	};
}