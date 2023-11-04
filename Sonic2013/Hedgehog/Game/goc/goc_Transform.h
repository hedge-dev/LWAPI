#pragma once

namespace app::fnd
{
	class GOCTransform : public GOComponent
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x00494600), GOCTransform*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDtor, ASLR(0x00494750), GOCTransform*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalTranslation, ASLR(0x00494440), GOCTransform*, const csl::math::Vector3&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalRotation, ASLR(0x00494470), GOCTransform*, const csl::math::Quaternion&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalTranslationAndRotation, ASLR(0x004944A0), GOCTransform*, const csl::math::Vector3&, const csl::math::Quaternion&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalTransform, ASLR(0x00494690), GOCTransform*, const math::Transform&);
		inline static const char* ms_pGOCTransformFamilyID = (const char*)ASLR(0x00D60B44);

	public:
		csl::ut::LinkListNode ChildNode;
		INSERT_PADDING(8);
		GOCTransform* pParent;
		csl::ut::LinkList<GOCTransform> Children{ &GOCTransform::ChildNode };
		app::math::Transform Transform;
		app::fnd::HFrame Frame; // app::fnd::BranchHFrame
		bool Unk1{};
		bool Unk2{};
		int Unk3{};
		int Unk4{};
		int Unk5{};
		
	public:
		static GOComponentClass ms_GOCTransformStaticClass;
		
		GOCTransform() : GOComponent(true)
		{
			ASSERT_OFFSETOF(GOCTransform, Transform, 0x60);
			ASSERT_OFFSETOF(GOCTransform, Frame, 0xA0);
			
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
					in_pParent->Children.push_back(this);
			}
		}

		bool IsExistParent() const
		{
			return pParent != nullptr;
		}

		void SetInheriteFlags(byte in_flag)
		{
			Frame.SetFlag(16, in_flag & 1);
			Frame.SetFlag(32, in_flag & 2);
		}
		
		void RemoveChild(GOCTransform* in_pChild)
		{
			pParent->Children.erase(in_pChild);
		}

		void SetLocalTranslation(const csl::math::Vector3& in_rTranslation)
		{
			ms_fpSetLocalTranslation(this, in_rTranslation);
		}

		void SetLocalRotation(const csl::math::Quaternion& in_rRotation)
		{
			ms_fpSetLocalRotation(this, in_rRotation);
		}

		void SetLocalTranslationAndRotation(const csl::math::Vector3& in_rTranslation, const csl::math::Quaternion& in_rRotation)
		{
			ms_fpSetLocalTranslationAndRotation(this, in_rTranslation, in_rRotation);
		}

		void SetLocalTransform(const math::Transform& in_rTransform)
		{
			ms_fpSetLocalTransform(this, in_rTransform);
		}

		csl::math::Vector3 GetLocalPosition() const
		{
			return Transform.Position;
		}

		csl::math::Quaternion GetLocalRotation() const 
		{
			return Transform.Rotation;
		}
		
		const char* GetFamilyID() const override
		{
			return ms_pGOCTransformFamilyID;
		}

		void AddListener(HFrameListener* in_pListener) 
		{
			Frame.AddHFrameListener(in_pListener);
		}

		void RemoveListener(HFrameListener* in_pListener)
		{
			Frame.RemoveHFrameListener(in_pListener);
		}

		inline static GOComponentClass* staticClass()
		{
			return &ms_GOCTransformStaticClass;
		}

		inline static GOComponent* Initialize(csl::fnd::IAllocator* in_pAllocator)
		{
			return new(in_pAllocator) GOCTransform();
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