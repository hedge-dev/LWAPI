#pragma once

namespace gindows
{
	class ManagerImpl : Object
	{
	protected:
		device::Font* m_pDefaultFont{};
		csl::ut::Color8 m_BackColor{ 0xFF, 0x64, 0x64, 0x64 };
		csl::ut::Color8 m_ForeColor{ 0xFF, 0xFF, 0xFF, 0xFF };
		csl::ut::Color8 m_SelectCaptionColorL{ 0xFF, 0xB4, 0x64, 0x50 };
		csl::ut::Color8 m_SelectCaptionColorR{ 0xFF, 0xC8, 0xA0, 0xA0 };
		csl::ut::Color8 m_UnSelectCaptionColor{ 0xFF, 0x50, 0x50, 0x50 };
		device::DeviceMouse* m_pMouse{};
		device::Graphics* m_pGraphics{};
		Desktop* m_pDesktop{};
		device::Font* m_pFonts[16]{};
		Control* m_pFocusedControl{};
		Control* m_pControlBelowMouse{}; // Maybe
		INSERT_PADDING(16){}; // One day
		float m_MouseClickInterval{};

	public:
		[[nodiscard]] device::Font* GetDefaultFontPointer() const
		{
			return m_pDefaultFont;
		}

		[[nodiscard]] device::Graphics* GetGraphicsPointer() const
		{
			return m_pGraphics;
		}

		[[nodiscard]] device::DeviceMouse* GetMousePointer() const
		{
			return m_pMouse;
		}
		
		[[nodiscard]] const csl::ut::Color8* GetDefaultBackColorPointer() const
		{
			return &m_BackColor;
		}

		[[nodiscard]] const csl::ut::Color8* GetDefaultForeColorPointer() const
		{
			return &m_ForeColor;
		}

		[[nodiscard]] const csl::ut::Color8* GetSelectCaptionColorL() const
		{
			return &m_SelectCaptionColorL;
		}

		[[nodiscard]] const csl::ut::Color8* GetSelectCaptionColorR() const
		{
			return &m_SelectCaptionColorR;
		}

		[[nodiscard]] const csl::ut::Color8* GetUnselectCaptionColor() const
		{
			return &m_UnSelectCaptionColor;
		}
		
		void SetFont(size_t idx, device::Font* pFont)
		{
			if (idx > _countof(m_pFonts))
				return;

			m_pFonts[idx] = pFont;
			
			if (!m_pDefaultFont)
				m_pDefaultFont = pFont;
		}

		void SetDefaultFontIndex(size_t idx)
		{
			if (idx > _countof(m_pFonts))
				return;

			m_pDefaultFont = m_pFonts[idx];
		}
		
		void SetGraphics(device::Graphics* pGraphics)
		{
			m_pGraphics = pGraphics;
		}

		void SetMouse(device::DeviceMouse* pMouse)
		{
			m_pMouse = pMouse;
		}
	};
}