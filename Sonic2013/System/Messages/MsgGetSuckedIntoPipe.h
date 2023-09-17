#pragma once

namespace app::xgame
{
	class MsgGetSuckedIntoPipe : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x609A;

		int Unk1{};
		int Unk2{};
		csl::math::Vector3 Unk3{};

		MsgGetSuckedIntoPipe() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgGetSuckedIntoPipe(*this);
		}
	};
}