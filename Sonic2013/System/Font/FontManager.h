#pragma once

namespace app::font
{
	class Font;
	class FontText;

	class FontManager : public fnd::ReferencedObject, csl::fnd::SingletonPointer<FontManager>
	{
	protected:
		csl::ut::InplaceMoveArray<Font*, 2> m_DebugFonts{ GetAllocator() };
		csl::ut::MoveArray<FontText*> m_DbgTexts{ GetAllocator() };
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

		void DbgAddFontText(FontText* pText)
		{
			csl::fnd::MutexLock lock(m_Lock);
			if (!m_DbgTexts.get_allocator())
				m_DbgTexts.change_allocator(GetAllocator());

			m_DbgTexts.push_back(pText);
		}

		void DbgRemoveFontText(FontText* pText)
		{
			csl::fnd::MutexLock lock(m_Lock);
			auto idx = m_DbgTexts.find(pText);
			if (idx == -1)
				return;

			m_DbgTexts.remove(idx);
		}
		
		void DbgDraw()
		{
			csl::fnd::MutexLock lock(m_Lock);
			for (auto& pText : m_DbgTexts)
			{
				if (pText)
					pText->Draw();
			}
		}
	};
}

DEFINE_SINGLETONPTR(app::font::FontManager, ASLR(0x0FD4058));