#pragma once
#include "Control.h"

namespace gindows
{
	// Form : ScrollableContent
	class Form : public Control
	{
	private:
		inline static const ControlVftable* ms_fpVftable = reinterpret_cast<const ControlVftable*>(ASLR(0x00E0D46C));
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x0096F930), Form* pThis);

	protected:
		csl::ut::Bitset<uint> m_FormFlags;
		INSERT_PADDING(40){};
		
	public:
		csl::ut::LinkListNode FormsNode{nullptr, nullptr};
		csl::ut::LinkListNode ActiveFormsNode{nullptr, nullptr};
		
		Form() : Control(true)
		{
			ASSERT_OFFSETOF(Form, FormsNode, 604);
			ms_fpCtor(this);
		}

	protected:
		Form(bool in_skipFp) : Control(in_skipFp)
		{
			m_Name._Mypad |= 2;
		}

	public:
		~Form()
		{
			if (!(m_Name._Mypad & 2))
				ms_fpVftable->fpDtor(this, 0);
		}

		size_t GetControlArea(const csl::ut::Point2<int>& in_rPoint) override
		{
			size_t type = ms_fpVftable->fpGetControlArea(this, in_rPoint);
			return type == 2 ? 16 : type;
		}
		
		void OnRender() override
		{
			ms_fpVftable->fpOnRender(this);
		}

		void OnSizeChanged() override
		{
			ms_fpVftable->fpOnSizeChanged(this);
		}

		void OnMouseLeave() override
		{
			ms_fpVftable->fpOnMouseLeave(this);
		}

		void OnMouseEnter() override
		{
			ms_fpVftable->fpOnMouseEnter(this);
		}
		
		void OnMouseDown(MouseEventArgs& in_rArgs) override
		{
			ms_fpVftable->fpOnMouseDown(this, in_rArgs);
		}

		void OnMouseUp(MouseEventArgs& in_rArgs) override
		{
			ms_fpVftable->fpOnMouseUp(this, in_rArgs);
		}

		void OnMouseMove(MouseEventArgs& in_rArgs) override
		{
			ms_fpVftable->fpOnMouseMove(this, in_rArgs);
		}

		void OnUpdate() override
		{
			ms_fpVftable->fpOnUpdate(this);
		}

		void GetClientOffsetInflate(csl::ut::Point2<int>* in_pA1, csl::ut::Size2<int>* in_pA2) const override
		{
			ms_fpVftable->fpGetClientOffsetInflate(this, in_pA1, in_pA2);
		}

		bool ControlProc(int in_param, EventArgs& in_rArgs) override
		{
			return ms_fpVftable->fpControlProc(this, in_param, in_rArgs);
		}
	};
}