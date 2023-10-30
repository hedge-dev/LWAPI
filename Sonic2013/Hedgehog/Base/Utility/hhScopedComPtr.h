#pragma once

namespace hh::ut
{
	template<typename T>
	class RefCountStrategyBasic
	{
	public:
		static void AddRef(T* in_obj)
		{
			in_obj->AddRef();
		}

		static void Release(T* in_obj)
		{
			in_obj->Release();
		}
	};

	template <typename T, typename TRefCountStrategy = RefCountStrategyBasic<T>>
	class ScopedComPtr
	{
	public:
		T* m_pObj{};

		~ScopedComPtr()
		{
			resetaddref(nullptr);
		}

		T* get() const
		{
			return m_pObj;
		}

		void resetaddref(T* in_obj)
		{
			if (m_pObj)
			{
				TRefCountStrategy::Release(m_pObj);
			}

			m_pObj = in_obj;
			if (m_pObj)
			{
				TRefCountStrategy::AddRef(m_pObj);
			}
		}

		T** operator&()
		{
			return &m_pObj;
		}

		T* operator->() const
		{
			return m_pObj;
		}

		operator T*() const
		{
			return get();
		}
	};
}