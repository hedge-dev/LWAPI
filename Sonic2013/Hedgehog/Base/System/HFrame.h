#pragma once

namespace app::fnd
{
	class HFrame;

	class HFrameListener
	{
	public:
		virtual ~HFrameListener() = default;
		virtual void HFrameUpdatedCallback(const HFrame* in_pFrame, bool in_a2) {}
	};

	class HFrame : public ReferencedObject
	{
	public:
		typedef uint8 FlagType;

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddChild, ASLR(0x0048E650), HFrame*, HFrame*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddHFrameListener, ASLR(0x0048E2E0), void* This, HFrameListener* pListener);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpRemoveHFrameListener, ASLR(0x0048E1D0), void* This, HFrameListener* pListener);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalTransform, ASLR(0x0048E160), void*, const csl::math::Matrix34&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalTranslation, ASLR(0x0048DD30), void*, const csl::math::Vector3&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocalRotation, ASLR(0x0048DD80), void*, const csl::math::Quaternion&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpMarkUpdate, ASLR(0x0048DD00), void* This);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpResetFlag, ASLR(0x0048DCD0), void*, FlagType);

	public:
		csl::ut::LinkListNode Child;
		HFrame* pParent;
		HFrame* pFrame{ this };
		int Unk2{};
		FlagType Flags{};
		csl::ut::LinkList<HFrame> Children{ &HFrame::Child };
		csl::ut::InplaceMoveArray<HFrameListener*, 10> Listeners{ GetAllocator() };
		math::CalculatedTransform Unk3;
		math::CalculatedTransform Transform;

		HFrame()
		{
			SetFlag(16);
			SetFlag(32);
		}

		void AddChild(HFrame* in_pChild)
		{
			ms_fpAddChild(this, in_pChild);
		}

		void AddHFrameListener(HFrameListener* in_pListener)
		{
			return ms_fpAddHFrameListener(this, in_pListener);
		}

		void RemoveHFrameListener(HFrameListener* in_pListener)
		{
			return ms_fpRemoveHFrameListener(this, in_pListener);
		}

		csl::math::Vector3 GetLocalTranslation() const
		{
			return Transform.GetTranslation();
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
			Flags |= in_flag;
		}

		void ResetFlag(FlagType in_flag)
		{
			ms_fpResetFlag(this, in_flag);
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