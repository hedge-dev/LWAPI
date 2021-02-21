#pragma once
namespace gindows
{
	class Control : Object
	{
	public:
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnDestroy;
		csl::fnd::Delegate<void(Object*, EventArgs&), DelegateAllocator> m_OnExecute; // ExecuteEventArgs

	protected:
		INSERT_PADDING(0xF0){};
		Canvas m_Canvas{};
		INSERT_PADDING(0x44){};
		
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

		Canvas& GetCanvas()
		{
			return m_Canvas;
		}
	};
}