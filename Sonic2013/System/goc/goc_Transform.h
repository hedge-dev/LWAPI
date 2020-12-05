#pragma once

namespace app::fnd
{
	class GOCTransform : public GOComponent
	{
	private:
		INSERT_PADDING(420);
		
	public:
		inline static const char* ms_pGOCTransformFamilyID = (const char*)ASLR(0x00F68ED4);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x00494600), GOCTransform* This);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDtor, ASLR(0x00494750), GOCTransform* This);
		static GOComponentClass ms_GOCTransformStaticClass;
		
		GOCTransform()
		{
			GameObjectSystem::GetSingleton()->handleManager->RemoveObject(*this);
			ms_fpCtor(this);

			// The game's constructor sets the reference count to zero which causes the object to die prematurely if its on the heap
			AddRef();
		}

		~GOCTransform() override
		{
			ms_fpDtor(this);
			FORCE_RET
		}
		
		const char* GetFamilyID() override
		{
			return ms_pGOCTransformFamilyID;
		}

		inline static GOComponentClass* staticClass()
		{
			return &ms_GOCTransformStaticClass;
		}

		inline static GOComponent* Initialize(csl::fnd::IAllocator* allocator)
		{
			return new(allocator) GOCTransform();
		}
	};

	inline GOComponentClass GOCTransform::ms_GOCTransformStaticClass
	{
		"GOCTransform", 0,
		GOCTransform::ms_pGOCTransformFamilyID,
		sizeof(GOCTransform),
		&GOCTransform::Initialize, 16, 0
	};
}