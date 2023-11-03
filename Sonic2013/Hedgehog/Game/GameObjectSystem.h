#pragma once

namespace app
{
	class GameObject;

	struct GameObjectTableEntry
	{
		size_t Handle{};
		GameObject* pObject{};
	};

	class GameObjectSystem : public fnd::ReferencedObject, csl::fnd::SingletonPointer<GameObjectSystem>
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddObject, ASLR(0x0049D9C0), GameObjectSystem* This, GameObject* object);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpRemoveObject, ASLR(0x0049DA30), GameObjectSystem* This, GameObject* object);
		inline static GameObjectSystem** ms_ppGameObjectSystem = (GameObjectSystem**)ASLR(0x00FD3FC4);

	public:
		app::fnd::PooledAllocator* pPooledAllocator{};
		app::fnd::PooledAllocator PooledAllocator{ &PoolList };
		csl::fnd::LinkHeapTemplate<csl::fnd::DummyLock> PoolList{};
		csl::ut::MoveArray<GameObjectTableEntry> Handles{ pPooledAllocator };
		INSERT_PADDING(24) {}; // csl::ut::Queue<uint>
		app::ut::RefPtr<app::fnd::HandleManagerBase> rpHandleManager{};

		GameObjectSystem()
		{
			ASSERT_OFFSETOF(GameObjectSystem, pPooledAllocator, 12);
			ASSERT_OFFSETOF(GameObjectSystem, rpHandleManager, 0x120);
		}
		
		void AddObject(GameObject* in_pObject)
		{
			ms_fpAddObject(this, in_pObject);
		}

		void RemoveObject(GameObject* in_pObject)
		{
			ms_fpRemoveObject(this, in_pObject);
		}

		csl::fnd::IAllocator* GetPooledAllocator() const
		{
			return pPooledAllocator;
		}
	};
}

DEFINE_SINGLETONPTR(app::GameObjectSystem, ASLR(0x00FD3FC4));