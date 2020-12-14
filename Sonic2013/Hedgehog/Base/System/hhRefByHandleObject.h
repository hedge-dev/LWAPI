#pragma once

namespace app::fnd
{
	class RefByHandleObject;
	
	struct HandleTableEntry
	{
		size_t handle{};
		RefByHandleObject* object{};
	};
	
	class RefByHandleObject : public ReferencedObject
	{
	private:
		size_t handle{};
		HandleTableEntry* entry{};

	public:
		~RefByHandleObject() override
		{
			GameObjectSystem::GetSingleton()->handleManager->RemoveObject(*this);
		}
		
		RefByHandleObject()
		{
			GameObjectSystem::GetSingleton()->handleManager->AddObject(*this);
		}

	protected:
		RefByHandleObject(bool skip)
		{
			
		}
	};
}