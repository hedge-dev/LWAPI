#pragma once

namespace app::xgame
{
	class MsgWaterWorks : public fnd::Message
	{
	public:
		csl::math::Vector3 Unk1{};
		csl::math::Vector3 Unk2{};

		inline const static unsigned int MessageID = 0x607A;

		MsgWaterWorks() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgWaterWorks(*this);
		}
	};
}