#pragma once

namespace app::xgame
{
	class MsgPLStargGroundImpulse : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x5081;

		csl::math::Matrix34 Unk1{};
		csl::math::Vector3 Unk2{};
		float Unk3{};;

		MsgPLStargGroundImpulse() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLStargGroundImpulse(*this);
		}
	};

	typedef MsgPLStargGroundImpulse MsgPLStartGroundImpulse;
}