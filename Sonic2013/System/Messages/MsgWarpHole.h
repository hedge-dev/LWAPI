#pragma once

namespace app::xgame
{
	class MsgWarpHole : public fnd::Message
	{
	public:
		uint PlayerNo{};
		bool ToSideView{};
		csl::math::Vector3 TargetPosition{};
		csl::math::Quaternion TargetRotation{};
		char Unk1{};

		inline const static unsigned int MessageID = 0x6064;

		MsgWarpHole() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgWarpHole(*this);
		}
	};
}