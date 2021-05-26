#pragma once

namespace app::ut
{
	template<typename T>
	class RefPtr
	{
	protected:
		T* m_pObj{};

		void swap(T* pObj)
		{
			if (m_pObj == pObj)
				return;

			if (pObj)
				pObj->AddRef();
			
			if (m_pObj)
				m_pObj->Release();

			m_pObj = pObj;
		}

	public:
		RefPtr() {}
		
		RefPtr(T* pObj)
		{
			swap(pObj);
		}
		RefPtr(const RefPtr& rOther)
		{
			swap(rOther.m_pObj);
		}
		
		~RefPtr()
		{
			swap(nullptr);
		}
		
		RefPtr<T>& operator=(T* pObj)
		{
			swap(pObj);
			return *this;
		}

		operator bool() const
		{
			return m_pObj != nullptr;
		}

		operator T* () const {
			return m_pObj;
		}
		
		T* get() const
		{
			return m_pObj;
		}
		
		T* operator->() const
		{
			return m_pObj;
		}
	};
}