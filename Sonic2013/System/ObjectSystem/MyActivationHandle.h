#pragma once
#pragma push_macro("SendMessage")
#undef SendMessage

namespace app
{
	class CSetObjectListener;
	class alignas(16) CMyActivationHandle : public CActivationHandle
	{
	protected:
		CSetObjectListener* m_pOwner{};
		
	public:
		void ActivationProc(EActivationOp op) override;

		void SetOwner(CSetObjectListener* pActor)
		{
			m_pOwner = pActor;
		}
	};
}

#pragma pop_macro("SendMessage")