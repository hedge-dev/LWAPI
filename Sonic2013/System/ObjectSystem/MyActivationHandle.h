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
		void ActivationProc(EActivationOp in_op) override;

		void SetOwner(CSetObjectListener* in_pActor)
		{
			m_pOwner = in_pActor;
		}
	};
}

#pragma pop_macro("SendMessage")