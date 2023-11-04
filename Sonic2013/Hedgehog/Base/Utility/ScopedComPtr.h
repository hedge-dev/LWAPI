#pragma once

namespace hh::ut
{
	template<typename T>
	class RefCountStrategyBasic
	{
	public:
		static void AddRef(T* in_pObj)
		{
			in_pObj->AddRef();
		}

		static void Release(T* in_pObj)
		{
			in_pObj->Release();
		}
	};

	template <typename T, typename TRefCountStrategy = RefCountStrategyBasic<T>>
	class ScopedComPtr
	{
	public:
		T* pObj{};

		~ScopedComPtr()
		{
			resetaddref(nullptr);
		}

		T* get() const
		{
			return pObj;
		}

		void resetaddref(T* in_pObj)
		{
			if (pObj)
			{
				TRefCountStrategy::Release(pObj);
			}

			pObj = in_pObj;
			if (pObj)
			{
				TRefCountStrategy::AddRef(pObj);
			}
		}

		T** operator&()
		{
			return &pObj;
		}

		T* operator->() const
		{
			return pObj;
		}

		operator T*() const
		{
			return get();
		}
	};
}