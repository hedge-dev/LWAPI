#pragma once

namespace gindows
{
	class TreeView;
}

namespace app::dev
{
	struct VariableChangedEventArgs
	{
		
	};
	
	class S13VariableEditControl : public gindows::Control
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x00459FA0), S13VariableEditControl*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetGroup, ASLR(0x00459E90), S13VariableEditControl*, S13VariableGroup*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpClearGroup, ASLR(0x00459800), S13VariableEditControl*);
		inline static const gindows::ControlVftable* ms_fpVftable = reinterpret_cast<const gindows::ControlVftable*>(ASLR(0x00D5D954));

	public:
		csl::fnd::Delegate<void (gindows::Object*, VariableChangedEventArgs&), gindows::DelegateAllocator> OnVariableChanged;

	protected:
		S13VariableGroup* m_pGroup{};
		gindows::TreeView* m_pVariableTree{};
		char m_Unk1;
		
	public:
		S13VariableEditControl() : Control(true)
		{
			ms_fpCtor(this);
		}

	protected:
		S13VariableEditControl(bool in_skipFp)
		{
			m_Name._Mypad |= 2;
		}

	public:
		~S13VariableEditControl()
		{
			if (!(m_Name._Mypad & 2))
				ms_fpVftable->fpDtor(this, 0);
		}

		void OnRender() override
		{
			ms_fpVftable->fpOnRender(this);
		}

		void OnKeyDown(gindows::KeyEventArgs& in_rArgs) override
		{
			ms_fpVftable->fpOnKeyDown(this, in_rArgs);
		}

		void SetGroup(S13VariableGroup* in_pGroup)
		{
			ms_fpSetGroup(this, in_pGroup);
		}

		void ClearGroup()
		{
			ms_fpClearGroup(this);
		}

		S13VariableGroup* GetGroup() const
		{
			return m_pGroup;
		}
	};
}