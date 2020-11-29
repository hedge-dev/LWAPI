#pragma once

namespace app
{
	class GameObject;
	
	namespace fnd
	{
		class GOComponent : public RefByHandleObject
		{
			friend GameObject;
			
		protected:
			GameObject* activeObject{};
			unsigned short unk1{};
			char componentType{};
			char componentFlags{};
			unsigned int componentStats{};
			unsigned int unk2{};
			csl::ut::LinkListNode visualComponentNode;
			csl::ut::LinkListNode physicsComponentNode;
			csl::ut::LinkListNode audibleComponentNode;
			
		public:
			GOComponent()
			{
				
			}
			
			virtual const char* GetFamilyID() = 0;
			virtual void Update(UpdatingPhase phase, const SUpdateInfo& updateInfo)
			{
				
			}
			
			virtual void OnGOCEvent(int event, GameObject& object, void* data)
			{
				
			}
			
			virtual bool ProcessMessage(const Message& message)
			{
				return false;
			}

			void SetGameObject(GameObject* object)
			{
				activeObject = object;
			}
		};
	}
}
