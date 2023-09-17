#pragma once

namespace app::xgame
{
	class MsgHudStartStomping : public fnd::Message
	{
	public:
		float Unk1{};
		byte Unk2{};
		byte Unk3{};

		inline const static unsigned int MessageID = 0xC027;

		MsgHudStartStomping() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgHudStartStomping(*this);
		}
	};
}