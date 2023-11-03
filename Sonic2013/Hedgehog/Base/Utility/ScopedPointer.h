#pragma once

namespace app::ut
{
	template<typename T>
	class ScopedPtr : csl::ut::NonCopyable
	{
	protected:
		T* m_pX{};
		csl::fnd::IAllocator* m_pAllocator{};

	public:
		ScopedPtr() : m_pAllocator(nullptr), m_pX(nullptr)
		{
			
		}

		ScopedPtr(T* in_pX) : m_pAllocator(nullptr), m_pX(in_pX)
		{
			
		}
		
		ScopedPtr(T* in_pX, csl::fnd::IAllocator* in_pAllocator) : m_pAllocator(in_pAllocator), m_pX(in_pX)
		{
			
		}

		~ScopedPtr()
		{
			delete m_pX;
		}
		
		void reset(T* in_pX)
		{
			if (m_pX)
				delete m_pX;

			m_pX = in_pX;
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

		ScopedPtr& operator=(T* in_pPtr)
		{
			reset(in_pPtr);
			return *this;
		}

		operator bool() const
		{
			return m_pX != 0;
		}
	};
}