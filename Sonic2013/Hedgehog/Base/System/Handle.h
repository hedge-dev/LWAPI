#pragma once

namespace app::fnd
{
	class HandleBase
	{
	protected:
		size_t m_Handle{};
		HandleTableEntry* m_pEntry{};

		void Set(const RefByHandleObject* pObj)
		{
			if (pObj)
			{
				m_Handle = pObj->m_Handle;
				m_pEntry = pObj->m_pHandleEntry;
			}
		}
		
	public:
		HandleBase()
		{
			
		}
		
		HandleBase(const RefByHandleObject* pObj)
		{
			Set(pObj);
		}

		bool IsValid() const
		{
			if (!m_pEntry)
				return false;

			return m_pEntry->m_Handle == m_Handle && m_pEntry->m_pObject;
		}

		RefByHandleObject* Get() const
		{
			if (!IsValid())
				return nullptr;

			return m_pEntry->m_pObject;
		}

		operator bool() const
		{
			return IsValid();
		}

		bool operator==(const RefByHandleObject* pObj)
		{
			if (!IsValid())
				return false;

			return m_Handle == pObj->m_Handle;
		}

		bool operator!=(const RefByHandleObject* pObj)
		{
			return !operator==(pObj);
		}

		HandleBase& operator=(const RefByHandleObject* pObj)
		{
			Set(pObj);
			return *this;
		}
	};

	template<class T>
	class Handle : public HandleBase
	{
	public:
		Handle()
		{
			
		}

		Handle(const T* pObj) : HandleBase(pObj)
		{
			
		}

		T* Get() const
		{
			return reinterpret_cast<T*>(HandleBase::Get());
		}

		Handle<T>& operator=(T* pObj)
		{
			Set(pObj);
			return *this;
		}

		operator T*() const
		{
			return Get();
		}

		T* operator->() const
		{
			return Get();
		}
	};
}