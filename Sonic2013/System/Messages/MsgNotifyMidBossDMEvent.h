#pragma once

namespace app::xgame
{
	class MsgNotifyMidBossDMEvent : public fnd::Message
	{
	public:
		int Unk1{};
		csl::math::Vector3 Unk2{};
		bool Unk3{};

		inline const static unsigned int MessageID = 0x60DC;

		MsgNotifyMidBossDMEvent() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgNotifyMidBossDMEvent(*this);
		}
	};
}