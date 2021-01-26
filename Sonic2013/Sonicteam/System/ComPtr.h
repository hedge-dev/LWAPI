#pragma once

namespace csl::fnd
{
	template<typename T>
	class com_ptr
	{
		T* m_pT{};

	public:
		com_ptr()
		{
			
		}

		com_ptr(T* pT) : m_pT(pT)
		{
			if (pT)
				pT->AddRef();
		}

		~com_ptr()
		{
			if (m_pT)
				m_pT->Release();
		}
		
		T* get() const
		{
			return m_pT;
		}

		T* operator ->() const
		{
			return get();
		}

		T& operator *() const
		{
			return *get();
		}
	};
}