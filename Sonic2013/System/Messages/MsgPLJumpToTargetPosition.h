#pragma once

namespace app::xgame
{
	class MsgPLJumpToTargetPosition : public fnd::Message
	{
	public:
		float Unk1{ 200.0f };
		float Unk2{};
		csl::math::Vector3 TargetPosition{};
		csl::math::Quaternion TargetRotation{};
		bool Unk3{};

		inline const static unsigned int MessageID = 0x507E;
		
		MsgPLJumpToTargetPosition() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgPLJumpToTargetPosition(*this);
		}
	};
}