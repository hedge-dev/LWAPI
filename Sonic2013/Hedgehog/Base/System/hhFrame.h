#pragma once

namespace app::fnd
{
	class HFrame;

	class HFrameListener
	{
	public:
		virtual ~HFrameListener() = default;
		virtual void HFrameUpdatedCallback(const HFrame* pFrame, bool a2) {}
	};

	class HFrame : public ReferencedObject
	{
	public:
		typedef uint8 FlagType;
		
		csl::ut::LinkListNode m_Child;
		HFrame* m_pParent;
		HFrame* m_pFrame{ this };
		int m_Unk2{};
		FlagType m_Flags{};
		csl::ut::LinkList<HFrame> m_Children{ &HFrame::m_Child };
		csl::ut::InplaceMoveArray<HFrameListener*, 10> m_Listeners{ GetAllocator() };
		math::CalculatedTransform m_Unk3;
		math::CalculatedTransform m_Transform;

	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddChild, ASLR(0x0048E650), HFrame*, HFrame*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddHFrameListener, ASLR(0x0048E2E0), void* This, HFrameListener* pListener);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpRemoveHFrameListener, ASLR(0x0048E1D0), void* This, HFrameListener* pListener);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalTransform, ASLR(0x0048E160), void*, const csl::math::Matrix34&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalTranslation, ASLR(0x0048DD30), void*, const csl::math::Vector3&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalRotation, ASLR(0x0048DD80), void*, const csl::math::Quaternion&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpMarkUpdate, ASLR(0x0048DD00), void* This);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpResetFlag, ASLR(0x0048DCD0), void*, FlagType);

		HFrame()
		{
			SetFlag(16);
			SetFlag(32);
		}

		void AddChild(HFrame* in_pChild)
		{
			ms_fpAddChild(this, in_pChild);
		}

		void AddHFrameListener(HFrameListener* pListener)
		{
			return ms_fpAddHFrameListener(this, pListener);
		}

		void RemoveHFrameListener(HFrameListener* pListener)
		{
			return ms_fpRemoveHFrameListener(this, pListener);
		}

		csl::math::Vector3 GetLocalTranslation() const
		{
			return m_Transform.GetTranslation();
		}

		void SetLocalTransform(const csl::math::Matrix34& in_rMatrix)
		{
			ms_fpSetLocalTransform(this, in_rMatrix);
		}

		void SetLocalTranslation(const csl::math::Vector3& in_rTranslation)
		{
			ms_fpSetLocalTranslation(this, in_rTranslation);
		}

		void SetLocalRotation(const csl::math::Quaternion& in_rRotation)
		{
			ms_fpSetLocalRotation(this, in_rRotation);
		}

		void MarkUpdate()
		{
			ms_fpMarkUpdate(this);
		}
		
		void SetFlag(FlagType in_flag)
		{
			m_Flags |= in_flag;
		}

		void ResetFlag(FlagType flag)
		{
			ms_fpResetFlag(this, flag);
		}

		void SetFlag(FlagType in_flag, bool in_enable)
		{
			if (in_enable)
				SetFlag(in_flag);
			else
				ResetFlag(in_flag);
		}
	};
}