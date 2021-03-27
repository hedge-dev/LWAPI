#pragma once
#include <stdio.h>
#include <stdarg.h>
#pragma push_macro("DrawText")
#undef DrawText

namespace app::font
{
	class FontText
	{
		struct TextParam
		{
			csl::math::Vector2 m_Position{ 0, 0 };
			uint m_Color{ (uint)-1 };
			csl::math::Vector2 m_Size{ 0, 0 };
			char* m_pText{};
		};
		
	protected:
		Font* m_pFont{};
		csl::math::Vector2 m_BasePos{ 0, 0 };
		uint m_Color{ (uint)-1 };
		csl::math::Vector2 m_Size{ 18, 18 };
		bool m_Enabled{ true };
		bool m_AutoFlush{ true };
		csl::ut::MoveArray<TextParam> m_Params{ nullptr };
		csl::fnd::Mutex m_Lock{};

		void Clear()
		{
			csl::fnd::MutexLock lock(m_Lock);
			for (auto& param : m_Params)
			{
				m_Params.get_allocator()->Free(param.m_pText);
			}
		}
		
	public:
		FontText(Font* pFont, csl::fnd::IAllocator* pAllocator) : m_pFont(pFont)
		{
			m_Params.change_allocator(pAllocator);
		}

		~FontText()
		{
			Clear();
		}
		
		[[nodiscard]] uint GetColor() const
		{
			return m_Color;
		}
		
		[[nodiscard]] const csl::math::Vector2& GetBasePos() const
		{
			return m_BasePos;
		}

		[[nodiscard]] const csl::math::Vector2& GetSize() const
		{
			return m_Size;
		}
		
		[[nodiscard]] bool IsEnabled() const
		{
			return m_Enabled;
		}

		void SetFont(Font* pFont)
		{
			m_pFont = pFont;
		}
		
		void SetBasePos(const csl::math::Vector2& pos)
		{
			m_BasePos = pos;
		}

		void SetSize(const csl::math::Vector2& size)
		{
			m_Size = size;
		}

		void SetColor(uint color)
		{
			m_Color = color;
		}

		void SetColorAll(uint color)
		{
			csl::fnd::MutexLock lock(m_Lock);

			m_Color = color;
			for (auto& param : m_Params)
			{
				param.m_Color = color;
			}
		}
		
		void SetEnable(bool enable)
		{
			m_Enabled = enable;
		}

		void AddString(const csl::math::Vector2& pos, const char* pText)
		{
			csl::fnd::MutexLock lock(m_Lock);
			auto textSize = strlen(pText) + 1;
			auto* pTexCpy = (char*)m_Params.get_allocator()->Alloc(textSize, alignof(char));

			strcpy_s(pTexCpy, textSize, pText);
			TextParam param{ pos, m_Color, m_Size, pTexCpy };
			m_Params.push_back(param);
		}

		void AddStringFormat(const csl::math::Vector2& pos, const char* pText, ...)
		{
			va_list args;
			va_start(args, pText);

			char textBuf[256];
			vsnprintf(textBuf, sizeof(textBuf), pText, args);
			AddString(pos, textBuf);
			
			va_end(args);
		}
		
		void Draw(Font* pFont)
		{
			if (pFont && m_Enabled && pFont->IsInit())
			{
				if (m_AutoFlush)
					pFont->Begin();
				
				csl::fnd::MutexLock lock(m_Lock);
				
				for (auto& param : m_Params)
				{
					csl::math::Vector2 drawPos = param.m_Position;
					drawPos += GetBasePos();

					pFont->SetTextColor(param.m_Color);
					pFont->SetTextSize(param.m_Size);
					pFont->DrawText(drawPos, param.m_pText);
				}

				if (m_AutoFlush)
					pFont->End();
			}
		}

		void Draw()
		{
			Draw(m_pFont);
		}
	};
}

#pragma pop_macro("DrawText")