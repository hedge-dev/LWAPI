#pragma once

namespace app::Player
{
	class MsgSetupGroundImpulse : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x5081;

		bool Unk1{};;

		MsgSetupGroundImpulse() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgSetupGroundImpulse(*this);
		}
	};
}