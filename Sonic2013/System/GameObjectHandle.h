#pragma once

namespace app
{
	class GameObjectHandleBase
	{
	protected:
		size_t m_ObjectHandle{};
		GameObjectTableEntry* m_pEntry{};

		void Set(const GameObject* pObj)
		{
			m_pEntry = pObj->m_pObjectEntry;
			m_ObjectHandle = pObj->m_ObjectHandle;
		}
		
	public:
		GameObjectHandleBase()
		{
			
		}
		
		GameObjectHandleBase(const GameObject* pObj)
		{
			Set(pObj);
		}

		bool IsValid() const
		{
			if (!m_pEntry)
				return false;

			return (m_pEntry->handle == m_ObjectHandle) && m_pEntry->object;
		}

		GameObject* Get() const
		{
			if (!IsValid())
				return nullptr;

			return m_pEntry->object;
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

		bool operator==(GameObject* pObj) const
		{
			if (!IsValid())
				return false;

			return pObj->m_ObjectHandle == m_ObjectHandle;
		}

		bool operator!=(GameObject* pObj) const
		{
			return !operator==(pObj);
		}

		GameObjectHandleBase& operator=(GameObject* pObj)
		{
			Set(pObj);
			return *this;
		}
	};

	template<typename T = GameObject>
	class GameObjectHandle : public GameObjectHandleBase
	{
	public:
		GameObjectHandle() : GameObjectHandleBase(){}
		GameObjectHandle(T* pObj) : GameObjectHandleBase(pObj){}

		T* Get() const
		{
			return reinterpret_cast<T*>(GameObjectHandleBase::Get());
		}

		GameObjectHandle<T>& operator=(T* pObj)
		{
			Set(pObj);
			return *this;
		}

		operator T*() const
		{
			return Get();
		}
	};
}