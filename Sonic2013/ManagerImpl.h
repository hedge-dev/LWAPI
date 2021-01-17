#pragma once

namespace gindows
{
	class ManagerImpl : Object
	{
	protected:
		device::Font** m_ppFonts{};
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
	};
}