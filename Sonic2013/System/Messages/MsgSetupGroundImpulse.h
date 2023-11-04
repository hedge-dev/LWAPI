#pragma once

namespace app::Player
{
	class MsgSetupGroundImpulse : public fnd::Message
	{
	public:
		bool Unk1{};;

		inline const static unsigned int MessageID = 0x5081;

		MsgSetupGroundImpulse() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgSetupGroundImpulse(*this);
		}
	};
}