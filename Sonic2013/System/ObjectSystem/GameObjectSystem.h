#pragma once

namespace app
{
	class GameObject;

	struct GameObjectTableEntry
	{
		size_t handle{};
		GameObject* object{};
	};

	class GameObjectSystem : public fnd::ReferencedObject
	{
	private:
		csl::fnd::IAllocator* pooledAllocator{};
		INSERT_PADDING(0x110);
		
	public:
		fnd::HandleManagerBase* handleManager;
		inline static GameObjectSystem** ms_ppGameObjectSystem = (GameObjectSystem**)ASLR(0x00FD3FC4);
		inline static FUNCTION_PTR(void, __thiscall, fp_GameObjectSystemAddObject, ASLR(0x0049D9C0), GameObjectSystem* This, GameObject* object);

		GameObjectSystem()
		{
			ASSERT_OFFSETOF(GameObjectSystem, pooledAllocator, 12);
			ASSERT_OFFSETOF(GameObjectSystem, handleManager, 0x120);
		}
		
		void AddObject(GameObject* object)
		{
			fp_GameObjectSystemAddObject(this, object);
		}

		csl::fnd::IAllocator* GetPooledAllocator() const
		{
			return pooledAllocator;
		}

		inline static GameObjectSystem* GetSingleton()
		{
			return *ms_ppGameObjectSystem;
		}
	};
}
