#pragma once
namespace gindows
{
	class Control : Object
	{
	public:
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnDestroy;
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnExecute; // ExecuteEventArgs
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnRender; // RenderEventArgs
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnLocationChanged;
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnSizeChanged;
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnGotFocus;
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnLostFocus;
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnClick;
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnMouseLeave;
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnMouseEnter;
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnMouseDown; // MouseEventArgs
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnMouseUp; // MouseEventArgs
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnMouseMove; // MouseEventArgs
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnMouseWheel; // MouseEventArgs
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnKeyDown; // KeyEventArgs
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnKeyUp; // KeyEventArgs
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnKeyPress; // KeyPressEventArgs
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnFont;
		
	protected:
		csl::ut::Bitset<uint> m_Flags{};
		void* m_pUnk1{};
		INSERT_PADDING(12){}; //std::list<gindows::Control>
		std::dummy::string m_Name;
		INSERT_PADDING(8){};
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
		virtual void Add(Control* pControl) = 0;
		virtual void Remove(Control* pControl) = 0;
		virtual void SetContainsFocus(bool focused) = 0;
		virtual Control* FindControl(const csl::ut::Point2<int>& point) = 0;
		virtual bool GetControlArea(const csl::ut::Point2<int>& point) = 0;
		virtual void Show() = 0;
		virtual void Hide() = 0;
		virtual void Render() = 0;
		virtual void OnDestroy() = 0;
		virtual void OnExecute(float a1) = 0; // delta?
		virtual void OnRender() = 0;
		virtual void OnLocationChanged() = 0;
		virtual void OnSizeChanged() = 0;
		virtual void OnGotFocus() = 0;
		virtual void OnLostFocus() = 0;
		virtual void OnClick() = 0;
		virtual void OnMouseLeave() = 0;
		virtual void OnMouseEnter() = 0;
		virtual void OnMouseDown(MouseEventArgs& args) = 0;
		virtual void OnMouseUp(MouseEventArgs& args) = 0;
		virtual void OnMouseMove(MouseEventArgs& args) = 0;
		virtual void OnMouseWheel(MouseEventArgs& args) = 0;
		virtual void OnKeyDown(KeyEventArgs& args) = 0;
		virtual void OnKeyUp(KeyEventArgs& args) = 0;
		virtual void OnKeyPress(KeyPressEventArgs& args) = 0;
		virtual void OnFont() = 0;
		virtual void OnUpdate() = 0;
		virtual void GetClientOffsetInflate(csl::ut::Point2<int>*, csl::ut::Size2<int>*) const = 0;
		virtual bool ControlProc(int param, EventArgs& args) = 0;

		Control()
		{
			ASSERT_OFFSETOF(Control, m_Canvas, 272);
			ASSERT(sizeof(Control) == 564, "Control size not 564");
		}
		
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
		
		const char* GetName() const
		{
			return m_Name.c_str();
		}

		bool IsShow() const
		{
			return !m_Flags.test(1);
		}
	};
}