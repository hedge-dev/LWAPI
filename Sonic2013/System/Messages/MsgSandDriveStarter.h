#pragma once

namespace app::xgame
{
	class MsgSandDriveStarter : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x6084;

		int Unk1{};

		MsgSandDriveStarter() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgSandDriveStarter(*this);
		}
	};
}