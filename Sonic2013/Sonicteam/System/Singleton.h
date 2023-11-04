#pragma once

namespace csl::fnd
{	
	template<typename T>
	class SingletonPointer
	{
	protected:
		static T** ms_ppInstance;

	public:
		static T** GetPointer()
		{
			return ms_ppInstance;
		}
		
		static T* GetInstance()
		{
			return *ms_ppInstance;
		}

		static T* SwapInstance(T* inst)
		{
			T* pOldInstance = *ms_ppInstance;
			*ms_ppInstance = inst;
			return pOldInstance;
		}

		static void ReplaceInstance(T* inst)
		{
			if (*ms_ppInstance) delete *ms_ppInstance;
			
			*ms_ppInstance = inst;
		}

		static bool IsInitialized()
		{
			return *ms_ppInstance == nullptr;
		}
	};

	template<typename T>
	inline T** SingletonPointer<T>::ms_ppInstance{ nullptr };
	
	template<typename T>
	class Singleton
	{
	public:
		inline static T* ms_ppInstance{};

		[[nodiscard]] static T* GetInstance()
		{
			if constexpr (std::is_base_of<SingletonPointer<T>, T>())
			{
				return SingletonPointer<T>::GetInstance();
			}

			return ms_ppInstance;
		}

		static void ReplaceInstance(T* in_pInstance)
		{
			if constexpr (std::is_base_of<SingletonPointer<T>, T>())
			{
				SingletonPointer<T>::ReplaceInstance(in_pInstance);
				return;
			}
			
			if (ms_ppInstance) delete ms_ppInstance;
			ms_ppInstance = in_pInstance;
		}

		static T* SwapInstance(T* in_pInstance)
		{
			if constexpr (std::is_base_of<SingletonPointer<T>, T>())
			{
				return SingletonPointer<T>::SwapInstance(in_pInstance);
			}

			T* pInst = ms_ppInstance;
			ms_ppInstance = in_pInstance;
			return pInst;
		}

		static bool IsInitialized()
		{
			if constexpr (std::is_base_of<SingletonPointer<T>, T>())
			{
				return SingletonPointer<T>::IsInitialized();
			}
			
			return ms_ppInstance != nullptr;
		}
	};
}

#define DEFINE_SINGLETONPTR(type, ptr) type** csl::fnd::SingletonPointer<type>::ms_ppInstance = reinterpret_cast<type**>(ptr);