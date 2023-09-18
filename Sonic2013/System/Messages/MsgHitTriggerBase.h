#pragma once

namespace app::game
{
	class ColliShape;
}

namespace app::xgame
{
	inline static void getContactPoint(game::ColliShape* in_pSelf, game::ColliShape* in_pOther, game::PhysicsContactPoint* out_pPoint)
	{

	}

	class MsgHitTriggerBase : public fnd::Message
	{
	private:
		inline static FUNCTION_PTR(csl::math::Vector3*, __thiscall, ms_fpGetContactPointNormal, ASLR(0x00534520), const MsgHitTriggerBase*, csl::math::Vector3*);
		inline static FUNCTION_PTR(csl::math::Vector3*, __thiscall, ms_fpGetContactPointPosition, ASLR(0x005344D0), const MsgHitTriggerBase*, csl::math::Vector3*);

	public:
		game::ColliShape* m_pSelf{};
		game::ColliShape* m_pOther{};
		uint m_Sender{};
		
		MsgHitTriggerBase(uint id, game::ColliShape* pSelf, game::ColliShape* pOther) : fnd::Message(id), m_pSelf(pSelf), m_pOther(pOther)
		{
			
		}

		csl::math::Vector3* GetContactPointPosition() const
		{
			csl::math::Vector3 out{};
			return ms_fpGetContactPointPosition(this, &out);
		}

		csl::math::Vector3* GetContactPointNormal() const
		{
			csl::math::Vector3 out{};
			return ms_fpGetContactPointNormal(this, &out);
		}

		Message* Clone() override
		{
			return new MsgHitTriggerBase(*this);
		}
	};
}