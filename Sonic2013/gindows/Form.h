#pragma once
#include "Control.h"

namespace gindows
{
	// Form : ScrollableContent
	class Form : public Control
	{
	protected:
		csl::ut::Bitset<uint> m_FormFlags;
		INSERT_PADDING(40){};
		
	public:
		csl::ut::LinkListNode m_FormsNode{nullptr, nullptr};
		csl::ut::LinkListNode m_ActiveFormsNode{nullptr, nullptr};

		inline static const ControlVftable* ms_fpVftable = reinterpret_cast<const ControlVftable*>(ASLR(0x00E0D46C));
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x0096F930), Form* pThis);
		
		Form() : Control(true)
		{
			ASSERT_OFFSETOF(Form, m_FormsNode, 604);
			ms_fpCtor(this);
		}

	protected:
		Form(bool skipFp) : Control(skipFp)
		{
			m_Name._Mypad |= 2;
		}

	public:
		~Form()
		{
			if (!(m_Name._Mypad & 2))
				ms_fpVftable->fpDtor(this, 0);
		}

		size_t GetControlArea(const csl::ut::Point2<int>& point) override
		{
			size_t type = ms_fpVftable->fpGetControlArea(this, point);
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
		
		void OnMouseDown(MouseEventArgs& args) override
		{
			ms_fpVftable->fpOnMouseDown(this, args);
		}

		void OnMouseUp(MouseEventArgs& args) override
		{
			ms_fpVftable->fpOnMouseUp(this, args);
		}

		void OnMouseMove(MouseEventArgs& args) override
		{
			ms_fpVftable->fpOnMouseMove(this, args);
		}

		void OnUpdate() override
		{
			ms_fpVftable->fpOnUpdate(this);
		}

		void GetClientOffsetInflate(csl::ut::Point2<int>* a1, csl::ut::Size2<int>* a2) const override
		{
			ms_fpVftable->fpGetClientOffsetInflate(this, a1, a2);
		}

		bool ControlProc(int param, EventArgs& args) override
		{
			return ms_fpVftable->fpControlProc(this, param, args);
		}
	};
}