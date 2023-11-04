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
			csl::math::Vector2 Position{ 0, 0 };
			uint Color{ (uint)-1 };
			csl::math::Vector2 Size{ 0, 0 };
			char* pText{};
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
			csl::fnd::MutexGuard lock(m_Lock);
			for (auto& param : m_Params)
			{
				m_Params.get_allocator()->Free(param.pText);
			}
		}
		
	public:
		FontText(Font* in_pFont, csl::fnd::IAllocator* in_pAllocator) : m_pFont(in_pFont)
		{
			m_Params.change_allocator(in_pAllocator);
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

		void SetFont(Font* in_pFont)
		{
			m_pFont = in_pFont;
		}
		
		void SetBasePos(const csl::math::Vector2& in_rPos)
		{
			m_BasePos = in_rPos;
		}

		void SetSize(const csl::math::Vector2& in_rSize)
		{
			m_Size = in_rSize;
		}

		void SetColor(uint in_color)
		{
			m_Color = in_color;
		}

		void SetColorAll(uint in_color)
		{
			csl::fnd::MutexGuard lock(m_Lock);

			m_Color = in_color;
			for (auto& param : m_Params)
			{
				param.Color = in_color;
			}
		}
		
		void SetEnable(bool in_enable)
		{
			m_Enabled = in_enable;
		}

		void AddString(const csl::math::Vector2& in_rPos, const char* in_pText)
		{
			csl::fnd::MutexGuard lock(m_Lock);
			auto textSize = strlen(in_pText) + 1;
			auto* pTexCpy = (char*)m_Params.get_allocator()->Alloc(textSize, alignof(char));

			strcpy_s(pTexCpy, textSize, in_pText);
			TextParam param{ in_rPos, m_Color, m_Size, pTexCpy };
			m_Params.push_back(param);
		}

		void AddStringFormat(const csl::math::Vector2& in_rPos, const char* in_pText, ...)
		{
			va_list args;
			va_start(args, in_pText);

			char textBuf[256];
			vsnprintf(textBuf, sizeof(textBuf), in_pText, args);
			AddString(in_rPos, textBuf);
			
			va_end(args);
		}
		
		void Draw(Font* in_pFont)
		{
			if (in_pFont && m_Enabled && in_pFont->IsInit())
			{
				if (m_AutoFlush)
					in_pFont->Begin();
				
				csl::fnd::MutexGuard lock(m_Lock);
				
				for (auto& param : m_Params)
				{
					csl::math::Vector2 drawPos = param.Position;
					drawPos += GetBasePos();

					in_pFont->SetTextColor(param.Color);
					in_pFont->SetTextSize(param.Size);
					in_pFont->DrawText(drawPos, param.pText);
				}

				if (m_AutoFlush)
					in_pFont->End();
			}
		}

		void Draw()
		{
			Draw(m_pFont);
		}
	};
}

#pragma pop_macro("DrawText")