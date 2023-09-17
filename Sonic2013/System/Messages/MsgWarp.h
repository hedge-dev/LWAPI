#pragma once

namespace app::xgame
{
	class MsgWarp : public fnd::Message
	{
	public:
		bool Unk1{};
		csl::math::Vector3 TargetPosition{};
		csl::math::Quaternion TargetRotation{};
		int Unk2{};

		inline const static unsigned int MessageID = 0x605F;

		MsgWarp() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgWarp(*this);
		}
	};
}