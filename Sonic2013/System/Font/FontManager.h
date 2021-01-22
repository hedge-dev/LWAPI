#pragma once

namespace app::font
{
	class Font;
	class FontText;

	class FontManager : public fnd::ReferencedObject, csl::fnd::SingletonPointer<FontManager>
	{
	protected:
		csl::ut::InplaceMoveArray<Font*, 2> m_DebugFonts{ nullptr };
		csl::ut::MoveArray<Font*> m_Fonts{ nullptr };
		app::ut::ScopedPtr<FontText> m_DbgText{};
		csl::fnd::Mutex m_Lock{};

	public:
		void SetDbgFont(Font* pFont)
		{
			m_DebugFonts[0] = pFont;
		}

		Font* GetDbgFont()
		{
			return m_DebugFonts[0];
		}
	};
}

DEFINE_SINGLETONPTR(app::font::FontManager, ASLR(0x0FD4058));