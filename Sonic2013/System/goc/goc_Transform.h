#pragma once

namespace app::fnd
{
	class GOCTransform : public GOComponent
	{
	private:
		INSERT_PADDING(420);
		
	public:
		inline static const char* ms_pGOCTransformFamilyID = (const char*)ASLR(0x00F68ED4);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpGOCTransformCtor, ASLR(0x00494600), GOCTransform* This);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpGOCTransformDtor, ASLR(0x00494750), GOCTransform* This);

		GOCTransform()
		{
			GameObjectSystem::GetSingleton()->handleManager->RemoveObject(*this);
			ms_fpGOCTransformCtor(this);

			// The game's constructor sets the reference count to zero which causes the object to die prematurely if its on the heap
			AddRef();
		}

		~GOCTransform() override
		{
			ms_fpGOCTransformDtor(this);
			FORCE_RET
		}
		
		const char* GetFamilyID() override
		{
			return ms_pGOCTransformFamilyID;
		}
	};
}