#pragma once

namespace hh::base
{
	class CRefCountObject
	{
	private:
		size_t m_RefCount{};

	public:
		virtual ~CRefCountObject() = default;

		inline void* operator new(size_t in_size)
		{
			return __HH_ALLOC(in_size);
		}

		inline void operator delete(void* in_pMem)
		{
			__HH_FREE(in_pMem);
		}
		
		void AddRef()
		{
			InterlockedIncrement(&m_RefCount);
		}

		void Release()
		{
			if (!InterlockedDecrement(&m_RefCount))
			{
				delete this;
			}
		}
	};
}