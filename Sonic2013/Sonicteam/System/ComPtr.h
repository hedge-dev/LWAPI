#pragma once

namespace csl::fnd
{
	template<typename T>
	class com_ptr
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
		com_ptr() {}

		com_ptr(T* pObj)
		{
			swap(pObj);
		}

		com_ptr(T* pObj, bool addRef)
		{
			if (addRef)
				swap(pObj);
			else
				m_pObj = pObj;
		}
		
		com_ptr(const com_ptr& rOther)
		{
			swap(rOther.m_pObj);
		}

		~com_ptr()
		{
			swap(nullptr);
		}

		com_ptr<T>& operator=(T* pObj)
		{
			swap(pObj);
			return *this;
		}

		operator bool() const
		{
			return m_pObj != nullptr;
		}

		operator T* () const
		{
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