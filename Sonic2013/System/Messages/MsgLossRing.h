#pragma once

namespace app::xgame
{
	class MsgLossRing : public fnd::Message
	{
	public:
		int Unk1{};
		bool Unk2{};
		int RingCount{};

		inline const static unsigned int MessageID = 0x6095;

		MsgLossRing() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgLossRing(*this);
		}
	};
}