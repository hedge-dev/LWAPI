#pragma once

namespace app::xgame
{
	class MsgHitUpdraftCollision : public fnd::Message
	{
	public:
		int Unk1{};

		inline const static unsigned int MessageID = 0x60A7;

		MsgHitUpdraftCollision() : Message(MessageID)
		{
			
		}

		Message* Clone() override
		{
			return new MsgHitUpdraftCollision(*this);
		}
	};
}