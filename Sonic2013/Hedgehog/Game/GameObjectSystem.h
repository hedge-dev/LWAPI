#pragma once

namespace app
{
	class GameObject;

	struct GameObjectTableEntry
	{
		size_t m_Handle{};
		GameObject* m_pObject{};
	};

	class GameObjectSystem : public fnd::ReferencedObject, csl::fnd::SingletonPointer<GameObjectSystem>
	{
	public:
		app::fnd::PooledAllocator* m_pPooledAllocator{};
		app::fnd::PooledAllocator m_PooledAllocator{ &m_PoolList };
		csl::fnd::LinkHeapTemplate<csl::fnd::DummyLock> m_PoolList{};
		csl::ut::MoveArray<GameObjectTableEntry> m_Handles{ m_pPooledAllocator };
		INSERT_PADDING(24) {}; // csl::ut::Queue<uint>
		app::ut::RefPtr<app::fnd::HandleManagerBase> m_rpHandleManager{};

		inline static GameObjectSystem** ms_ppGameObjectSystem = (GameObjectSystem**)ASLR(0x00FD3FC4);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddObject, ASLR(0x0049D9C0), GameObjectSystem* This, GameObject* object);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpRemoveObject, ASLR(0x0049DA30), GameObjectSystem* This, GameObject* object);

		GameObjectSystem()
		{
			ASSERT_OFFSETOF(GameObjectSystem, m_pPooledAllocator, 12);
			ASSERT_OFFSETOF(GameObjectSystem, m_rpHandleManager, 0x120);
		}
		
		void AddObject(GameObject* object)
		{
			ms_fpAddObject(this, object);
		}

		void RemoveObject(GameObject* object)
		{
			ms_fpRemoveObject(this, object);
		}

		csl::fnd::IAllocator* GetPooledAllocator() const
		{
			return m_pPooledAllocator;
		}
	};
}

DEFINE_SINGLETONPTR(app::GameObjectSystem, ASLR(0x00FD3FC4));