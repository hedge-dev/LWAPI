#pragma once

namespace app::xgame
{
	class MsgWaterWorks : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x607A;

		csl::math::Vector3 Unk1{};
		csl::math::Vector3 Unk2{};

		MsgWaterWorks() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgWaterWorks(*this);
		}
	};
}