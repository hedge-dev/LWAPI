#pragma once

namespace gindows
{
	class Desktop;
	class Control;
	
	class ManagerImpl : Object
	{
	protected:
		Font* m_pDefaultFont{};
		csl::ut::Color8 m_BackColor{ 0xFF, 0x64, 0x64, 0x64 };
		csl::ut::Color8 m_ForeColor{ 0xFF, 0xFF, 0xFF, 0xFF };
		csl::ut::Color8 m_SelectCaptionColorL{ 0xFF, 0xB4, 0x64, 0x50 };
		csl::ut::Color8 m_SelectCaptionColorR{ 0xFF, 0xC8, 0xA0, 0xA0 };
		csl::ut::Color8 m_UnSelectCaptionColor{ 0xFF, 0x50, 0x50, 0x50 };
		Mouse* m_pMouse{};
		Graphics* m_pGraphics{};
		Desktop* m_pDesktop{};
		Font* m_pFonts[16]{};
		Control* m_pFocusedControl{};
		Control* m_pControlBelowMouse{}; // Maybe
		INSERT_PADDING(12){}; // One day
		float m_TimeElapsed{};
		float m_MouseClickInterval{};

	public:
		[[nodiscard]] Font* GetDefaultFontPointer() const
		{
			return m_pDefaultFont;
		}

		[[nodiscard]] Graphics* GetGraphicsPointer() const
		{
			return m_pGraphics;
		}

		[[nodiscard]] Desktop* GetDesktop() const
		{
			return m_pDesktop;
		}
		
		[[nodiscard]] Mouse* GetMouse() const
		{
			return m_pMouse;
		}
		
		[[nodiscard]] csl::ut::Color8* GetDefaultBackColorPointer()
		{
			return &m_BackColor;
		}

		[[nodiscard]] csl::ut::Color8* GetDefaultForeColorPointer()
		{
			return &m_ForeColor;
		}

		[[nodiscard]] csl::ut::Color8* GetSelectCaptionColorL()
		{
			return &m_SelectCaptionColorL;
		}

		[[nodiscard]] csl::ut::Color8* GetSelectCaptionColorR()
		{
			return &m_SelectCaptionColorR;
		}

		[[nodiscard]] csl::ut::Color8* GetUnselectCaptionColor() 
		{
			return &m_UnSelectCaptionColor;
		}

		[[nodiscard]] Control* GetFocusControl()
		{
			return m_pFocusedControl;
		}

		[[nodiscard]] Control* GetMouseOverControl()
		{
			return m_pControlBelowMouse;
		}
		
		void SetFont(size_t in_idx, Font* in_pFont)
		{
			if (in_idx > _countof(m_pFonts))
				return;

			m_pFonts[in_idx] = in_pFont;
			
			if (!m_pDefaultFont)
				m_pDefaultFont = in_pFont;
		}

		void SetDefaultFontIndex(size_t in_idx)
		{
			if (in_idx > _countof(m_pFonts))
				return;

			m_pDefaultFont = m_pFonts[in_idx];
		}
		
		void SetGraphics(Graphics* in_pGraphics)
		{
			m_pGraphics = in_pGraphics;
		}

		void SetMouse(Mouse* in_pMouse)
		{
			m_pMouse = in_pMouse;
		}

		void SetFocusControl(Control* in_pControl)
		{
			m_pFocusedControl = in_pControl;
		}

		void Execute(float in_delta)
		{
			m_TimeElapsed += in_delta;
		}
	};
}