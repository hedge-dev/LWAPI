#pragma once

namespace app::xgame
{
	class MsgPLBeginAutorun : public fnd::Message
	{
	public:
		int Unk1{};
		int Unk2{};
		float Unk3{};
		csl::math::Vector3 Unk4{};
		float Unk5{};

		inline const static unsigned int MessageID = 0x5070;

		MsgPLBeginAutorun() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgPLBeginAutorun(*this);
		}
	};
}