#pragma once

namespace app::xgame
{
	class MsgNotifySilhouetteState : public fnd::Message
	{
	public:
		bool DisableLockOn{};
		int Unk2{};
		float Unk3{};

		inline const static unsigned int MessageID = 0x60C4;

		MsgNotifySilhouetteState() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgNotifySilhouetteState(*this);
		}
	};
}