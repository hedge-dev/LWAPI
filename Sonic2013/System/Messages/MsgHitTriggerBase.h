#pragma once

namespace app::game
{
	class ColliShape;
}

namespace app::xgame
{
	class MsgHitTriggerBase : public fnd::Message
	{
	public:
		game::ColliShape* m_pShape1{}; // Sender?
		game::ColliShape* m_pShape2{};
		uint m_Sender{};
		
		MsgHitTriggerBase(uint id, game::ColliShape* pShape1, game::ColliShape* pShape2) : fnd::Message(id), m_pShape1(pShape1), m_pShape2(pShape2)
		{
			
		}

		Message* Clone() override
		{
			return new MsgHitTriggerBase(*this);
		}
	};
}