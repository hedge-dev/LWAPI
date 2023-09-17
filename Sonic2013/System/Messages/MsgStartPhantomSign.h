#pragma once

namespace app::xgame
{
	class MsgStartPhantomSign : public fnd::Message
	{
	public:
		float Unk1{};
		byte Unk2{};
		byte Unk3{};

		inline const static unsigned int MessageID = 0xC026;

		MsgStartPhantomSign() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgStartPhantomSign(*this);
		}
	};
}