#pragma once

namespace app::xgame
{
	class MsgSandDriveStarter : public fnd::Message
	{
	public:
		int Unk1{};

		inline const static unsigned int MessageID = 0x6084;

		MsgSandDriveStarter() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgSandDriveStarter(*this);
		}
	};
}