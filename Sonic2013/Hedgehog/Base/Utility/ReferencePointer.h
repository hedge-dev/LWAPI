#pragma once

namespace app::ut
{
	template<typename T>
	class RefPtr
	{
	protected:
		T* m_pObj{};

		void swap(T* in_pObj)
		{
			if (m_pObj == in_pObj)
				return;

			if (in_pObj)
				in_pObj->AddRef();
			
			if (m_pObj)
				m_pObj->Release();

			m_pObj = in_pObj;
		}

	public:
		RefPtr() = default;
		
		RefPtr(T* in_pObj)
		{
			swap(in_pObj);
		}

		RefPtr(const RefPtr& in_rOther)
		{
			swap(in_rOther.get());
		}
		
		~RefPtr()
		{
			swap(nullptr);
		}
		
		RefPtr<T>& operator=(T* in_pObj)
		{
			swap(in_pObj);
			return *this;
		}

		RefPtr<T>& operator=(const RefPtr& in_rOther)
		{
			if (this == &in_rOther)
				return *this;

			swap(in_rOther.get());
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

		bool operator<(const RefPtr& in_rOther) const
		{
			return m_pObj < in_rOther.m_pObj;
		}

		bool operator>(const RefPtr& in_rOther) const
		{
			return m_pObj > in_rOther.m_pObj;
		}
	};

	template<class T, size_t Allocator = 2, typename... Args>
	inline static RefPtr<T> make_ref(Args&&... args)
	{
		return RefPtr<T>(new(game::GlobalAllocator::GetAllocator(Allocator)) T(std::forward<Args>(args)...));
	}
}