#pragma once

namespace app::xgame
{
	typedef int BattleItemType;

	class MsgNotihyChangeRing : public fnd::Message
	{
	public:
		Game::EUser UserNo{};
		BattleItemType Type{};
		int Unk2{};
		int Unk3{};

		inline const static unsigned int MessageID = 0x508D;

		MsgNotihyChangeRing() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgNotihyChangeRing(*this);
		}
	};

	typedef MsgNotihyChangeRing MsgNotifyChangeRing;
}