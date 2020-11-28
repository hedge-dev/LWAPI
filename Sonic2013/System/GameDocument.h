#pragma once

#include <cslib/utils.h>
#include <Hedgehog/Base/System/ReferencedObject.h>

namespace app
{
	class GameObject;
	
	class GameDocument : public fnd::ReferencedObject
	{
	public:
		inline static GameDocument** ms_ppGameDocument = (GameDocument**)ASLR(0xFEFEF4);
		inline static FUNCTION_PTR(void, __thiscall, fp_GameDocumentAddGameObject, ASLR(0x0090B3C0), GameDocument* This, GameObject* object);

	private:
		void* gameMode{};
		unsigned int unk1{};
		void* unk2{};
		float time{};

	public:
		void AddGameObject(GameObject* object)
		{
			fp_GameDocumentAddGameObject(this, object);
		}
	};
}
