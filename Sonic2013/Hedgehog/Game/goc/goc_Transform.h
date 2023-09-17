#pragma once

namespace app::fnd
{
	class GOCTransform : public GOComponent
	{
	public:
		csl::ut::LinkListNode m_ChildNode;
		INSERT_PADDING(8);
		GOCTransform* pParent;
		csl::ut::LinkList<GOCTransform> m_Children{ &GOCTransform::m_ChildNode };
		app::math::Transform m_Transform;
		app::fnd::HFrame m_Frame; // app::fnd::BranchHFrame
		bool Unk1{};
		bool Unk2{};
		int Unk3{};
		int Unk4{};
		int Unk5{};
		
	public:
		inline static const char* ms_pGOCTransformFamilyID = (const char*)ASLR(0x00D60B44);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x00494600), GOCTransform* This);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDtor, ASLR(0x00494750), GOCTransform* This);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalTranslation, ASLR(0x00494440), GOCTransform* This, const csl::math::Vector3& translation);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalRotation, ASLR(0x00494470), GOCTransform* This, const csl::math::Quaternion& rotation);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalTranslationAndRotation, ASLR(0x004944A0), 
			GOCTransform* This, const csl::math::Vector3& translation, const csl::math::Quaternion& rotation);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalTransform, ASLR(0x00494690), GOCTransform*, const math::Transform&);
		
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

		void SetParent(GOCTransform* in_pParent)
		{
			if (pParent != in_pParent)
			{
				if (pParent)
					pParent->RemoveChild(this);
			
				pParent = in_pParent;
				if (in_pParent)
					in_pParent->m_Children.push_back(this);
			}
		}

		bool IsExistParent()
		{
			return pParent != nullptr;
		}

		void SetInheriteFlags(byte in_flag)
		{
			m_Frame.SetFlag(16, in_flag & 1);
			m_Frame.SetFlag(32, in_flag & 2);
		}
		
		void RemoveChild(GOCTransform* in_pChild)
		{
			pParent->m_Children.erase(in_pChild);
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

		void SetLocalTransform(const math::Transform& in_rTransform)
		{
			ms_fpSetLocalTransform(this, in_rTransform);
		}

		csl::math::Vector3 GetLocalPosition() const
		{
			return m_Transform.m_Position;
		}

		csl::math::Quaternion GetLocalRotation() const 
		{
			return m_Transform.m_Rotation;
		}
		
		const char* GetFamilyID() const override
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