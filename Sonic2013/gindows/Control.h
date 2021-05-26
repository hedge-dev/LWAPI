#pragma once
namespace gindows
{
	class Desktop;
	class Control;
	
#define MEMBER_FUNC(TYPE, RET, NAME, ...) RET (__thiscall *fp##NAME)(TYPE* pThis, __VA_ARGS__)
	struct ControlVftable
	{
		MEMBER_FUNC(Control, void, Dtor, size_t deleterFlags);
		MEMBER_FUNC(Control, void, Add, Control* pControl);
		MEMBER_FUNC(Control, void, Remove, Control* pControl);
		MEMBER_FUNC(Control, void, SetContainsFocus, bool focused);
		MEMBER_FUNC(Control, Control*, FindControl, const csl::ut::Point2<int>& point);
		MEMBER_FUNC(Control, size_t, GetControlArea, const csl::ut::Point2<int>& point);
		MEMBER_FUNC(Control, void, Show);
		MEMBER_FUNC(Control, void, Hide);
		MEMBER_FUNC(Control, void, Render);
		MEMBER_FUNC(Control, void, OnDestroy);
		MEMBER_FUNC(Control, void, OnExecute, float a1); // delta?
		MEMBER_FUNC(Control, void, OnRender);
		MEMBER_FUNC(Control, void, OnLocationChanged);
		MEMBER_FUNC(Control, void, OnSizeChanged);
		MEMBER_FUNC(Control, void, OnGotFocus);
		MEMBER_FUNC(Control, void, OnLostFocus);
		MEMBER_FUNC(Control, void, OnClick);
		MEMBER_FUNC(Control, void, OnMouseLeave);
		MEMBER_FUNC(Control, void, OnMouseEnter);
		MEMBER_FUNC(Control, void, OnMouseDown, MouseEventArgs& args);
		MEMBER_FUNC(Control, void, OnMouseUp, MouseEventArgs& args);
		MEMBER_FUNC(Control, void, OnMouseMove, MouseEventArgs& args);
		MEMBER_FUNC(Control, void, OnMouseWheel, MouseEventArgs& args);
		MEMBER_FUNC(Control, void, OnKeyDown, KeyEventArgs& args);
		MEMBER_FUNC(Control, void, OnKeyUp, KeyEventArgs& args);
		MEMBER_FUNC(Control, void, OnKeyPress, KeyPressEventArgs& args);
		MEMBER_FUNC(Control, void, OnFont);
		MEMBER_FUNC(Control, void, OnUpdate);
		MEMBER_FUNC(const Control, void, GetClientOffsetInflate, csl::ut::Point2<int>*, csl::ut::Size2<int>*);
		MEMBER_FUNC(Control, bool, ControlProc, int param, EventArgs& args);
	};
#undef MEMBER_FUNC
	
	class Control : public Object
	{
	public:
		typedef size_t ControlDock;
		
		inline static const ControlVftable* ms_fpVftable = reinterpret_cast<const ControlVftable*>(ASLR(0x00E0D6B4));
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x009714A0), Control* pThis);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetSize, ASLR(0x0096FFD0), Control* pControl, const csl::ut::Size2<int>& size);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetLocation, ASLR(0x00971630), Control* pControl, const csl::ut::Point2<int>& point);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetDock, ASLR(0x00971700), Control* pControl, ControlDock dock);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetFont, ASLR(0x0096FE80), Control* pControl, uint font);
		
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnDestroy;
		csl::fnd::Delegate<void(Object*, ExecuteEventArgs&), DelegateAllocator> m_OnExecute; // ExecuteEventArgs
		csl::fnd::Delegate<void(Object*, RenderEventArgs&), DelegateAllocator> m_OnRender; // RenderEventArgs
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnLocationChanged;
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnSizeChanged;
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnGotFocus;
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnLostFocus;
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnClick;
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnMouseLeave;
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnMouseEnter;
		csl::fnd::Delegate<void(Object*, MouseEventArgs&), DelegateAllocator> m_OnMouseDown; // MouseEventArgs
		csl::fnd::Delegate<void(Object*, MouseEventArgs&), DelegateAllocator> m_OnMouseUp; // MouseEventArgs
		csl::fnd::Delegate<void(Object*, MouseEventArgs&), DelegateAllocator> m_OnMouseMove; // MouseEventArgs
		csl::fnd::Delegate<void(Object*, MouseEventArgs&), DelegateAllocator> m_OnMouseWheel; // MouseEventArgs
		csl::fnd::Delegate<void(Object*, KeyEventArgs&), DelegateAllocator> m_OnKeyDown; // KeyEventArgs
		csl::fnd::Delegate<void(Object*, KeyEventArgs&), DelegateAllocator> m_OnKeyUp; // KeyEventArgs
		csl::fnd::Delegate<void(Object*, KeyPressEventArgs&), DelegateAllocator> m_OnKeyPress; // KeyPressEventArgs
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnFont;
		
	protected:
		csl::ut::Bitset<uint> m_Flags{};
		Desktop* m_pDesktop{};
		INSERT_PADDING(12){}; //std::list<gindows::Control>
		union
		{
			std::dummy::basic_string<char, std::char_traits<char>, Allocator<char>> m_Name;
		};
		Canvas m_Canvas{};

	public:
		csl::ut::Rectangle2<int> m_TransformRect;
		
	protected:
		csl::ut::Rectangle2<int> m_Unk2;
		uint m_Unk3{};
		uint m_Unk4{};
		short m_Unk5;
		short m_Unk6;
		uint m_Unk7;
		csl::ut::Point2<int> m_Unk8;
		csl::ut::Point2<int> m_Unk9;
		
	public:
		Control()
		{
			ms_fpCtor(this);
			ASSERT_OFFSETOF(Control, m_Canvas, 268);
			ASSERT(sizeof(Control) == 560, "Control size not 560");
		}

	protected:
		Control(bool skipFp)
		{
			new (&m_Name) std::dummy::string();
			m_Name._Mypad |= true;
		}

	public:
		~Control()
		{
			if (!(m_Name._Mypad & 1))
				ms_fpVftable->fpDtor(this, 0);
		}
		
		virtual void Add(Control* pControl) { ms_fpVftable->fpAdd(this, pControl); }
		virtual void Remove(Control* pControl) { ms_fpVftable->fpRemove(this, pControl); }
		virtual void SetContainsFocus(bool focused) { ms_fpVftable->fpSetContainsFocus(this, focused); }
		virtual Control* FindControl(const csl::ut::Point2<int>& point) { return ms_fpVftable->fpFindControl(this, point); }
		virtual size_t GetControlArea(const csl::ut::Point2<int>& point) { return ms_fpVftable->fpGetControlArea(this, point); }
		virtual void Show() { m_Flags.reset(1); }
		virtual void Hide() { m_Flags.set(1); }
		virtual void Render() { ms_fpVftable->fpRender(this); }
		virtual void OnDestroy()
		{
			EventArgs args{};
			m_OnDestroy(this, args);
		}
		
		virtual void OnExecute(float a1) { ms_fpVftable->fpOnExecute(this, a1); }
		virtual void OnRender() { ms_fpVftable->fpOnRender(this); }
		virtual void OnLocationChanged() { EventArgs args{}; m_OnLocationChanged(this, args); }
		virtual void OnSizeChanged() { ms_fpVftable->fpOnSizeChanged(this); }
		virtual void OnGotFocus() { EventArgs args{}; m_OnGotFocus(this, args); }
		virtual void OnLostFocus() { EventArgs args{}; m_OnLostFocus(this, args); }
		virtual void OnClick() { EventArgs args{}; m_OnClick(this, args); }
		virtual void OnMouseLeave() { EventArgs args{}; m_OnMouseLeave(this, args); }
		virtual void OnMouseEnter() { EventArgs args{}; m_OnMouseEnter(this, args); }
		virtual void OnMouseDown(MouseEventArgs& args) { m_OnMouseDown(this, args); }
		virtual void OnMouseUp(MouseEventArgs& args) { m_OnMouseUp(this, args); }
		virtual void OnMouseMove(MouseEventArgs& args) { m_OnMouseMove(this, args); }
		virtual void OnMouseWheel(MouseEventArgs& args) { m_OnMouseWheel(this, args); }
		virtual void OnKeyDown(KeyEventArgs& args) { ms_fpVftable->fpOnKeyDown(this, args); }
		virtual void OnKeyUp(KeyEventArgs& args) { ms_fpVftable->fpOnKeyUp(this, args); }
		virtual void OnKeyPress(KeyPressEventArgs& args) { ms_fpVftable->fpOnKeyPress(this, args); }
		virtual void OnFont() { ms_fpVftable->fpOnFont(this); }
		virtual void OnUpdate() { ms_fpVftable->fpOnUpdate(this); }
		virtual void GetClientOffsetInflate(csl::ut::Point2<int>* a1, csl::ut::Size2<int>* a2) const { ms_fpVftable->fpGetClientOffsetInflate(this, a1, a2); }
		virtual bool ControlProc(int param, EventArgs& args) { return ms_fpVftable->fpControlProc(this, param, args); }
		
		const Canvas& GetCanvas() const { return m_Canvas; }
		Canvas& GetCanvas() { return m_Canvas; }
		
		void SetName(const char* pName)
		{
			m_Name = pName;
		}

		void SetHideContent(bool hide)
		{
			m_Flags.set(2, hide);
		}

		void SetIgnoreHide(bool ignore)
		{
			m_Flags.set(3, ignore);
		}

		void SetSize(const csl::ut::Size2<int>& size)
		{
			ms_fpSetSize(this, size);
		}

		void SetLocation(const csl::ut::Point2<int>& point)
		{
			ms_fpSetLocation(this, point);
		}

		void SetDock(ControlDock dock)
		{
			ms_fpSetDock(this, dock);
		}

		void SetFont(uint font)
		{
			ms_fpSetFont(this, font);
		}
		
		const char* GetName() const
		{
			return m_Name.c_str();
		}

		bool IsShow() const
		{
			return !m_Flags.test(1);
		}

		csl::ut::Size2<int> GetSize() const
		{
			return { m_TransformRect.GetWidth(), m_TransformRect.GetHeight() };
		}

		csl::ut::Point2<int> GetLocation() const
		{
			return { m_TransformRect.GetLeft(), m_TransformRect.GetTop() };
		}
		
		void SetFocus();
	};
}