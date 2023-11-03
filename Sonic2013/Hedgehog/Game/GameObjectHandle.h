#pragma once

namespace app
{
	class GameObjectHandleBase
	{
	protected:
		size_t m_ObjectHandle{};
		GameObjectTableEntry* m_pEntry{};

		void Set(const GameObject* in_pObj)
		{
			if (in_pObj)
			{
				m_pEntry = in_pObj->m_pObjectEntry;
				m_ObjectHandle = in_pObj->m_ObjectHandle;
			}
			else
			{
				m_ObjectHandle = 0;
				m_pEntry = nullptr;
			}
		}
		
	public:
		GameObjectHandleBase()
		{
			
		}
		
		GameObjectHandleBase(const GameObject* in_pObj)
		{
			Set(in_pObj);
		}

		bool IsValid() const
		{
			if (!m_pEntry)
				return false;

			return (m_pEntry->Handle == m_ObjectHandle) && m_pEntry->pObject;
		}

		GameObject* Get() const
		{
			if (!IsValid())
				return nullptr;

			return m_pEntry->pObject;
		}

		bool IsAlive() const
		{
			GameObject* pObj = Get();
			if (!pObj)
				return false;

			return !pObj->IsKilled();
		}

		operator bool() const
		{
			return IsValid();
		}

		bool operator==(const GameObject* in_pObj) const
		{
			if (!IsValid())
				return false;

			return in_pObj->m_ObjectHandle == m_ObjectHandle;
		}

		bool operator==(const GameObjectHandleBase& in_rOther) const
		{
			if (!IsValid() || !in_rOther.IsValid())
				return false;

			return m_ObjectHandle == in_rOther.m_ObjectHandle;
		}

		bool operator!=(const GameObject* in_pObj) const
		{
			return !operator==(in_pObj);
		}

		GameObjectHandleBase& operator=(const GameObject* in_pObj)
		{
			Set(in_pObj);
			return *this;
		}
	};

	template<typename T = GameObject>
	class GameObjectHandle : public GameObjectHandleBase
	{
	public:
		GameObjectHandle() : GameObjectHandleBase(){}
		GameObjectHandle(T* in_pObj) : GameObjectHandleBase(in_pObj){}

		T* Get() const
		{
			return reinterpret_cast<T*>(GameObjectHandleBase::Get());
		}

		GameObjectHandle<T>& operator=(T* in_pObj)
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