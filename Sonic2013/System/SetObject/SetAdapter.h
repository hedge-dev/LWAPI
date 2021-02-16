#pragma once

namespace app
{
	class CSetObjectListener;
	typedef void CSetAdapterMgr;
	
	class CSetAdapter
	{
	protected:
		CSetAdapterMgr* m_pAdapterManager;
		CSetObjectListener* m_pListener;
		SetEd::CResObject* m_pObject;
		void* m_Unk1;
		uint m_StatusFlags;
		float m_RetireTime;
		
	public:
		void SetListener(CSetObjectListener* pListener)
		{
			m_pListener = pListener;
		}
	};
}