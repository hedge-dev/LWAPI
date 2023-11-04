#pragma once

namespace app::fnd
{
	class HandleBase
	{
	protected:
		size_t m_Handle{};
		HandleTableEntry* m_pEntry{};

		void Set(const RefByHandleObject* in_pObj)
		{
			if (in_pObj)
			{
				m_Handle = in_pObj->m_Handle;
				m_pEntry = in_pObj->m_pHandleEntry;
			}
		}
		
	public:
		HandleBase()
		{
			
		}
		
		HandleBase(const RefByHandleObject* in_pObj)
		{
			Set(in_pObj);
		}

		bool IsValid() const
		{
			if (!m_pEntry)
				return false;

			return m_pEntry->Handle == m_Handle && m_pEntry->pObject;
		}

		RefByHandleObject* Get() const
		{
			if (!IsValid())
				return nullptr;

			return m_pEntry->pObject;
		}

		operator bool() const
		{
			return IsValid();
		}

		bool operator==(const RefByHandleObject* in_pObj)
		{
			if (!IsValid())
				return false;

			return m_Handle == in_pObj->m_Handle;
		}

		bool operator!=(const RefByHandleObject* in_pObj)
		{
			return !operator==(in_pObj);
		}

		HandleBase& operator=(const RefByHandleObject* in_pObj)
		{
			Set(in_pObj);
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

		Handle(const T* in_pObj) : HandleBase(in_pObj)
		{
			
		}

		T* Get() const
		{
			return reinterpret_cast<T*>(HandleBase::Get());
		}

		Handle<T>& operator=(T* in_pObj)
		{
			Set(in_pObj);
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