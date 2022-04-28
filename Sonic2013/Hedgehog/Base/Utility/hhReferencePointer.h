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
		RefPtr() = default;
		
		RefPtr(T* pObj)
		{
			swap(pObj);
		}

		RefPtr(const RefPtr& rOther)
		{
			swap(rOther.get());
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

		RefPtr<T>& operator=(const RefPtr& rOther)
		{
			if (this == &rOther)
				return *this;

			swap(rOther.get());
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

		T& ref() const
		{
			return *m_pObj;
		}
		
		T* operator->() const
		{
			return m_pObj;
		}
	};

	template<class T, size_t Allocator = 2, typename... Args>
	inline static RefPtr<T> make_ref(Args&&... args)
	{
		return RefPtr<T>(new(game::GlobalAllocator::GetAllocator(Allocator)) T(std::forward<Args>(args)...));
	}
}