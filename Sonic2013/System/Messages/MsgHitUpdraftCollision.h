#pragma once

namespace app::xgame
{
	class MsgHitUpdraftCollision : public fnd::Message
	{
	public:
		inline const static unsigned int MessageID = 0x60A7;

		int Unk1{};

		MsgHitUpdraftCollision() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgHitUpdraftCollision(*this);
		}
	};
}