#pragma once

namespace app::game
{
	class ColliShape;
}

namespace app::xgame
{
	class MsgHitEventCollision : public MsgHitTriggerBase
	{
	public:
		inline const static unsigned int MessageID = 0x9000;
		
		MsgHitEventCollision(game::ColliShape* pShape1, game::ColliShape* pShape2) : MsgHitTriggerBase(MessageID, pShape1, pShape2)
		{
			
		}

		Message* Clone() override
		{
			return new MsgHitEventCollision(*this);
		}
	};
}