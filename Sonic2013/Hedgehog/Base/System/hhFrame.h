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
	protected:
		csl::ut::LinkListNode m_Child;
		HFrame* m_pParent;
		INSERT_PADDING(12);
		csl::ut::LinkList<HFrame> m_Children{ &HFrame::m_Child };
		csl::ut::InplaceMoveArray<HFrameListener*, 10> m_Listeners{ GetAllocator() };
		csl::math::CalculatedTransform m_Unk1;
		csl::math::CalculatedTransform m_Transform;

	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddHFrameListener, ASLR(0x0048E2E0), void* This, HFrameListener* pListener);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpRemoveHFrameListener, ASLR(0x0048E1D0), void* This, HFrameListener* pListener);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetTranslation, ASLR(0x0048DD30), void* This, const csl::math::Vector3& rTranslation);

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

		void SetTranslation(csl::math::Vector3& rTranslation)
		{
			ms_fpSetTranslation(this, rTranslation);
		}
	};
}