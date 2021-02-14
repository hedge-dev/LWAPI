#pragma once
#pragma push_macro("SendMessage")
#undef SendMessage

namespace app
{
	class CMyActivationHandle : public CActivationHandle
	{
	protected:
		GameObject* m_pOwner{};
		
	public:
		void ActivationProc(EActivationOp op) override
		{
			xgame::MsgDeactivate msg{};
			m_pOwner->SendMessage(msg);
		}

		void SetOwner(GameObject* pActor)
		{
			m_pOwner = pActor;
		}
	};
}

#pragma pop_macro("SendMessage")