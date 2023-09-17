#pragma once

namespace app::xgame
{
	class MsgWarpNewArea : public fnd::Message
	{
	public:
		uint PlayerNo{};
		bool ToSideView{};
		csl::math::Vector3 TargetPosition{};
		csl::math::Quaternion TargetRotation{};
		int Unk1{};
		char Unk2{};
		char Unk3{};

		inline const static unsigned int MessageID = 0x6061;

		MsgWarpNewArea() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgWarpNewArea(*this);
		}
	};
}