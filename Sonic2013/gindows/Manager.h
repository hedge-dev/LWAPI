#pragma once
#include "ManagerImpl.h"
#include "WindowManager.h"
#include "Desktop.h"

namespace gindows
{
	class Manager : public Object, csl::ut::NonCopyable
	{
	private:
		inline static Manager** ms_ppInstance = reinterpret_cast<Manager**>(ASLR(0x00FF00A4));
		inline static FUNCTION_PTR(void, __cdecl, ms_fpInitialize, ASLR(0x0096EE00));
		
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
		
		[[nodiscard]] Control* FindControl(const csl::ut::Point2<int>& point)
		{
			return GetDesktop()->FindControl(point);
		}
		
		void SetFont(uint id, device::Font* pFont) const
		{
			m_pImpl->SetFont(id, pFont);
		}

		void SetGraphics(device::Graphics* pGraphics) const
		{
			m_pImpl->SetGraphics(pGraphics);
		}

		void SetMouse(device::Mouse* pMouse) const
		{
			m_pImpl->SetMouse(pMouse);
		}
		
		void SetDefaultFontIndex(size_t idx) const
		{
			m_pImpl->SetDefaultFontIndex(idx);
		}

		void SetFocusControl(Control* pControl)
		{
			if (GetFocusControl() == pControl)
				return;
			
			if (!pControl)
			{
				if (GetFocusControl())
				{
					GetFocusControl()->OnLostFocus();
				}
				m_pImpl->SetFocusControl(pControl);
				
				return;
			}

			if (GetFocusControl())
			{
				GetFocusControl()->OnLostFocus();
			}
			
			m_pImpl->SetFocusControl(pControl);
			pControl->OnGotFocus();
		}
		
		void Render()
		{
			GetGraphicsPointer()->BeginDraw();

			GetDesktop()->Render();
			if (GetMouse())
				GetMouse()->Draw();
			
			GetGraphicsPointer()->EndDraw();
		}

		void Execute(float delta)
		{
			GetDesktop()->OnExecute(delta);
			m_pImpl->Execute(delta);
		}
	};
}