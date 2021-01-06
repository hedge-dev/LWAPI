#pragma once

namespace app::fnd
{
	typedef void* Singleton_init();
	typedef void Singleton_destroy(void* singleton);
	
	struct SingletonInitNode
	{
		inline static SingletonInitNode** ms_ppCurNode = reinterpret_cast<SingletonInitNode**>(ASLR(0xFD4218));
		Singleton_init* init;
		Singleton_destroy* destroy;
		SingletonInitNode* prevNode;
		void** instance;

		SingletonInitNode() = default;
		
		SingletonInitNode(Singleton_init* init_, Singleton_destroy* destroy_, void** inst) : init(init_), destroy(destroy_), prevNode(*ms_ppCurNode), instance(inst)
		{
			*ms_ppCurNode = this;
		}
	};
}

#define DECLARE_SINGLETON static app::fnd::SingletonInitNode singletonInitNode;
#define DEFINE_SINGLETON(type) app::fnd::SingletonInitNode type::singletonInitNode = \
	app::fnd::SingletonInitNode(type##_init, type##_destroy, (void**)&instance);