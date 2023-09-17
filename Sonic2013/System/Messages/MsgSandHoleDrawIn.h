#pragma once

namespace app::xgame
{
	class MsgSandHoleDrawIn : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x606B;

		csl::math::Vector3 Unk1{};
		float Unk2{};

		MsgSandHoleDrawIn() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgSandHoleDrawIn(*this);
		}
	};
}