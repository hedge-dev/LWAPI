#pragma once

namespace hh::base
{
	class CRefCountObject
	{
	private:
		size_t m_RefCount{};

	public:
		virtual ~CRefCountObject() = default;

		inline void* operator new(size_t size)
		{
			return __HH_ALLOC(size);
		}

		inline void operator delete(void* mem)
		{
			__HH_FREE(mem);
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