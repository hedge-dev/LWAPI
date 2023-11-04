#pragma once

namespace app::xgame
{
	class MsgSheepRollingImpulse : public fnd::Message
	{
	public:
		float Unk1{};
		bool Unk2{};
		
		inline const static unsigned int MessageID = 0x604E;

		MsgSheepRollingImpulse() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgSheepRollingImpulse(*this);
		}
	};
}