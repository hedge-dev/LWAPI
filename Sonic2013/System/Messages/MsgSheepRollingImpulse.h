#pragma once

namespace app::xgame
{
	class MsgSheepRollingImpulse : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x604E;

		float Unk1{};
		bool Unk2{};

		MsgSheepRollingImpulse() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgSheepRollingImpulse(*this);
		}
	};
}