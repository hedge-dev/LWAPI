#pragma once

namespace app::xgame
{
	class MsgJumpBoardImpulse : public fnd::Message
	{
	public:
		enum EType
		{
			eType_Default
		};
		
		INSERT_PADDING(8);
		csl::math::Vector3 Origin{};
		csl::math::Vector3 Direction{};
		csl::math::Vector3 BoostDirection{};
		float SpeedDropoffTime{};
		EType Type{};
		bool Unk3{};
		INSERT_PADDING(4);

		inline const static unsigned int MessageID = 0x6003;

		MsgJumpBoardImpulse(const csl::math::Vector3& in_rOrigin, const csl::math::Vector3& in_rDir, const csl::math::Vector3& in_rBoostDir, EType in_type, float in_speedDropoffTime) : fnd::Message(MessageID)
		{
			Origin = in_rOrigin;
			Direction = in_rDir;
			BoostDirection = in_rBoostDir;
			SpeedDropoffTime = in_speedDropoffTime;
			Type = in_type;
			Unk3 = false;
		}

		Message* Clone() override
		{
			return new MsgJumpBoardImpulse(*this);
		}
	};
}