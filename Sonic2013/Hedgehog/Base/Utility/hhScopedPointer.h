#pragma once

namespace app::ut
{
	template<typename T>
	class ScopedPtr : csl::ut::NonCopyable
	{
	protected:
		csl::fnd::IAllocator* m_pAllocator{};
		T* m_pX{};

	public:
		ScopedPtr() : m_pAllocator(nullptr), m_pX(nullptr)
		{
			
		}

		ScopedPtr(T* pX) : m_pAllocator(nullptr), m_pX(pX)
		{
			
		}
		
		ScopedPtr(T* pX, csl::fnd::IAllocator* pAllocator) : m_pAllocator(pAllocator), m_pX(pX)
		{
			
		}

		~ScopedPtr()
		{
			delete m_pX;
		}
		
		void reset(T* pX)
		{
			if (m_pX)
				delete m_pX;

			m_pX = pX;
		}

		T* get() const
		{
			return m_pX;
		}

		T* operator ->() const
		{
			return get();
		}

		T& operator *() const
		{
			return *get();
		}

		ScopedPtr& operator=(T* ptr)
		{
			reset(ptr);
			return *this;
		}

		operator bool() const
		{
			return m_pX != 0;
		}
	};
}