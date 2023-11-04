#pragma once

namespace app::fnd
{
	typedef void* Singleton_init();
	typedef void Singleton_destroy(void* singleton);
	
	struct SingletonInitNode
	{
	private:
		inline static SingletonInitNode** ms_ppCurNode = reinterpret_cast<SingletonInitNode**>(ASLR(0x00FD4218));
	
	public:
		Singleton_init* pInit;
		Singleton_destroy* pDestroy;
		SingletonInitNode* pPreviousNode;
		void** ppInstance;

		SingletonInitNode() = default;
		
		SingletonInitNode(Singleton_init* in_pInit, Singleton_destroy* in_pDestroy, void** ppInstance) : pInit(in_pInit), pDestroy(in_pDestroy), pPreviousNode(*ms_ppCurNode), ppInstance(ppInstance)
		{
			*ms_ppCurNode = this;
		}
	};

	// Utility class
	template<typename T>
	class SingletonUtil : public csl::fnd::Singleton<T>
	{
	protected:
		static void* CreateInstance()
		{
			if constexpr (std::is_base_of<fnd::ReferencedObject, T>())
				return new(GetSingletonAllocator()) T();
			else
				return new T();
		}

		static void DeleteInstance(void* pInstance)
		{
			delete static_cast<T*>(pInstance);
		}

		inline static SingletonInitNode singletonInitNode{ CreateInstance,
			DeleteInstance, reinterpret_cast<void**>(&csl::fnd::Singleton<T>::instance) };
	};
}

#define DECLARE_SINGLETON static app::fnd::SingletonInitNode singletonInitNode;
#define DEFINE_SINGLETON(type) app::fnd::SingletonInitNode type::singletonInitNode = \
	app::fnd::SingletonInitNode(type##_init, type##_destroy, (void**)&instance);