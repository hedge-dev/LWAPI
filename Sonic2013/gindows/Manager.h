#pragma once
#include "ManagerImpl.h"
#include "WindowManager.h"
#include "Desktop.h"

namespace gindows
{
	class Manager : public Object, csl::ut::NonCopyable
	{
	private:
		inline static FUNCTION_PTR(void, __cdecl, ms_fpInitialize, ASLR(0x0096EE00));
		inline static Manager** ms_ppInstance = reinterpret_cast<Manager**>(ASLR(0x00FF00A4));
		
	protected:
		ManagerImpl* m_pImpl{};
		WindowManager* m_pWindowManager{};

	public:
		static void Initialize()
		{
			ms_fpInitialize();
		}
		
		static Manager* GetInstance()
		{
			return *ms_ppInstance;
		}

		[[nodiscard]] WindowManager* GetWindowManager()
		{
			return m_pWindowManager;
		}
		
		[[nodiscard]] device::Font* GetDefaultFontPointer()
		{
			return m_pImpl->GetDefaultFontPointer();
		}

		[[nodiscard]] device::Graphics* GetGraphicsPointer()
		{
			return m_pImpl->GetGraphicsPointer();
		}

		[[nodiscard]] Desktop* GetDesktop()
		{
			return m_pImpl->GetDesktop();
		}
		
		[[nodiscard]] device::Mouse* GetMouse()
		{
			return m_pImpl->GetMouse();
		}
		
		[[nodiscard]] csl::ut::Color8* GetDefaultBackColorPointer()
		{
			return m_pImpl->GetDefaultBackColorPointer();
		}

		[[nodiscard]] csl::ut::Color8* GetDefaultForeColorPointer()
		{
			return m_pImpl->GetDefaultForeColorPointer();
		}

		[[nodiscard]] csl::ut::Color8* GetSelectCaptionColorL()
		{
			return m_pImpl->GetSelectCaptionColorL();
		}

		[[nodiscard]] csl::ut::Color8* GetSelectCaptionColorR()
		{
			return m_pImpl->GetSelectCaptionColorR();
		}

		[[nodiscard]] csl::ut::Color8* GetUnselectCaptionColor()
		{
			return m_pImpl->GetUnselectCaptionColor();
		}

		[[nodiscard]] Control* GetFocusControl()
		{
			return m_pImpl->GetFocusControl();
		}

		[[nodiscard]] Control* GetMouseOverControl()
		{
			return m_pImpl->GetFocusControl();
		}
		
		[[nodiscard]] Control* FindControl(const csl::ut::Point2<int>& in_rPoint)
		{
			return GetDesktop()->FindControl(in_rPoint);
		}
		
		void SetFont(uint in_id, device::Font* in_pFont) const
		{
			m_pImpl->SetFont(in_id, in_pFont);
		}

		void SetGraphics(device::Graphics* in_pGraphics) const
		{
			m_pImpl->SetGraphics(in_pGraphics);
		}

		void SetMouse(device::Mouse* in_pMouse) const
		{
			m_pImpl->SetMouse(in_pMouse);
		}
		
		void SetDefaultFontIndex(size_t in_idx) const
		{
			m_pImpl->SetDefaultFontIndex(in_idx);
		}

		void SetFocusControl(Control* in_pControl)
		{
			if (GetFocusControl() == in_pControl)
				return;
			
			if (!in_pControl)
			{
				if (GetFocusControl())
				{
					GetFocusControl()->OnLostFocus();
				}
				m_pImpl->SetFocusControl(in_pControl);
				
				return;
			}

			if (GetFocusControl())
			{
				GetFocusControl()->OnLostFocus();
			}
			
			m_pImpl->SetFocusControl(in_pControl);
			in_pControl->OnGotFocus();
		}
		
		void Render()
		{
			GetGraphicsPointer()->BeginDraw();

			GetDesktop()->Render();
			if (GetMouse())
				GetMouse()->Draw();
			
			GetGraphicsPointer()->EndDraw();
		}

		void Execute(float in_delta)
		{
			GetDesktop()->OnExecute(in_delta);
			m_pImpl->Execute(in_delta);
		}
	};
}