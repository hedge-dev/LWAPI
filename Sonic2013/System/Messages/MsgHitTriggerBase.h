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
		game::ColliShape* m_pSelf{};
		game::ColliShape* m_pOther{};
		uint m_Sender{};
		
		MsgHitTriggerBase(uint id, game::ColliShape* pSelf, game::ColliShape* pOther) : fnd::Message(id), m_pSelf(pSelf), m_pOther(pOther)
		{
			
		}

		Message* Clone() override
		{
			return new MsgHitTriggerBase(*this);
		}
	};
}