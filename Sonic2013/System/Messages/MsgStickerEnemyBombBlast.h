#pragma once

namespace app::xgame
{
	class MsgStickerBombBlast : public fnd::Message
	{
	public:
		int Unk1{};
		int Unk2{};
		csl::math::Vector3 Unk3{};
		float Unk4{};
		int Unk5{};
		int Unk6{};
		int Unk7{};
		
		inline const static unsigned int MessageID = 0x6030;

		MsgStickerBombBlast() : Message(MessageID)
		{

		}

		Message* Clone() override
		{
			return new MsgStickerBombBlast(*this);
		}
	};
}