#pragma once

namespace app
{
	class GameObject;

	struct GameObjectTableEntry
	{
		size_t handle{};
		GameObject* object{};
	};
	
	class GameObjectSystem : fnd::ReferencedObject
	{
	private:
		csl::fnd::IAllocator* pooledAllocator{};
		
	public:
		inline static GameObjectSystem** ms_ppGameObjectSystem = (GameObjectSystem**)ASLR(0xFD3FC4);
		inline static FUNCTION_PTR(void, __thiscall, fp_GameObjectSystemAddObject, ASLR(0x0049D9C0), GameObjectSystem* This, GameObject* object);
		
		void AddObject(GameObject* object)
		{
			fp_GameObjectSystemAddObject(this, object);
		}

		csl::fnd::IAllocator* getPooledAllocator() const
		{
			return pooledAllocator;
		}
	};
}
