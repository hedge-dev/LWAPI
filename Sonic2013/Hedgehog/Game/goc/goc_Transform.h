#pragma once

namespace app::fnd
{
	class GOCTransform : public GOComponent
	{
	private:
		csl::ut::LinkListNode m_ChildNode;
		INSERT_PADDING(12);
		csl::ut::LinkList<GOCTransform> m_Children{ &GOCTransform::m_ChildNode };
		csl::math::Transform m_Transform;
		app::fnd::HFrame m_Frame; // app::fnd::BranchHFrame
		INSERT_PADDING(14);
		
	public:
		inline static const char* ms_pGOCTransformFamilyID = (const char*)ASLR(0x00D60B44);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x00494600), GOCTransform* This);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDtor, ASLR(0x00494750), GOCTransform* This);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalTranslation, ASLR(0x00494440), GOCTransform* This, const csl::math::Vector3& translation);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalRotation, ASLR(0x00494470), GOCTransform* This, const csl::math::Quaternion& rotation);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalTranslationAndRotation, ASLR(0x004944A0), 
			GOCTransform* This, const csl::math::Vector3& translation, const csl::math::Quaternion& rotation);

		
		static GOComponentClass ms_GOCTransformStaticClass;
		
		GOCTransform() : GOComponent(true)
		{
			ASSERT_OFFSETOF(GOCTransform, m_Transform, 0x60);
			ASSERT_OFFSETOF(GOCTransform, m_Frame, 0xA0);
			
			ms_fpCtor(this);
		}

		~GOCTransform() override
		{
			ms_fpDtor(this);
		}

		void SetLocalTranslation(const csl::math::Vector3& translation)
		{
			ms_fpSetLocalTranslation(this, translation);
		}

		void SetLocalRotation(const csl::math::Quaternion& rotation)
		{
			ms_fpSetLocalRotation(this, rotation);
		}

		void SetLocalTranslationAndRotation(const csl::math::Vector3& translation, const csl::math::Quaternion& rotation)
		{
			ms_fpSetLocalTranslationAndRotation(this, translation, rotation);
		}

		const csl::math::Vector3& GetLocalPosition() const
		{
			return m_Transform.m_Position;
		}

		const csl::math::Quaternion& GetLocalRotation() const
		{
			return m_Transform.m_Rotation;
		}
		
		const char* GetFamilyID() override
		{
			return ms_pGOCTransformFamilyID;
		}

		void AddListener(HFrameListener* pListener) 
		{
			m_Frame.AddHFrameListener(pListener);
		}

		void RemoveListener(HFrameListener* pListener)
		{
			m_Frame.RemoveHFrameListener(pListener);
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