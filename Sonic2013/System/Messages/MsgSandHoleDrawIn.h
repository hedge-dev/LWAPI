#pragma once

namespace app::xgame
{
	class MsgSandHoleDrawIn : public fnd::Message
	{
	public:
		csl::math::Vector3 Unk1{};
		float Unk2{};

		inline const static unsigned int MessageID = 0x606B;

		MsgSandHoleDrawIn() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgSandHoleDrawIn(*this);
		}
	};
}