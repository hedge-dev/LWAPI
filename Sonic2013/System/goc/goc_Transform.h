#pragma once

using namespace csl::math;

namespace app::fnd
{
	class GOCTransform : public GOComponent
	{
	private:
		INSERT_PADDING(36);
		Vector3 position;
		Quaternion rotation;
		INSERT_PADDING(0x160);
		
	public:
		inline static const char* ms_pGOCTransformFamilyID = (const char*)ASLR(0x00D60B44);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x00494600), GOCTransform* This);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDtor, ASLR(0x00494750), GOCTransform* This);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalTranslation, ASLR(0x00494440), GOCTransform* This, const Vector3& translation);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalRotation, ASLR(0x00494470), GOCTransform* This, const Quaternion& rotation);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalTranslationAndRotation, ASLR(0x004944A0), 
			GOCTransform* This, const Vector3& translation, const Quaternion& rotation);

		
		static GOComponentClass ms_GOCTransformStaticClass;
		
		GOCTransform() : GOComponent(true)
		{
			ASSERT_OFFSETOF(GOCTransform, position, 0x60);
			ASSERT_OFFSETOF(GOCTransform, rotation, 0x70);
			
			ms_fpCtor(this);
		}

		~GOCTransform() override
		{
			ms_fpDtor(this);
			FORCE_RET
		}

		void SetLocalTranslation(const Vector3& translation)
		{
			ms_fpSetLocalTranslation(this, translation);
		}

		void SetLocalRotation(const Quaternion& rotation)
		{
			ms_fpSetLocalRotation(this, rotation);
		}

		void SetLocalTranslationAndRotation(const Vector3& translation, const Quaternion& rotation)
		{
			ms_fpSetLocalTranslationAndRotation(this, translation, rotation);
		}

		const Vector3& GetLocalPosition() const
		{
			return position;
		}

		const Quaternion& GetLocalRotation() const
		{
			return rotation;
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