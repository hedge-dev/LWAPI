#pragma once
#pragma once
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
			const char* m_pText{};
		};
		
	protected:
		Font* m_pFont{};
		csl::math::Vector2 m_BasePos{ 0, 0 };
		uint m_Color{ (uint)-1 };
		csl::math::Vector2 m_Size{ 0, 0 };
		bool m_Enabled{ true };
		bool m_AutoFlush{ true };
		csl::ut::MoveArray<TextParam> m_Params{ nullptr };
		csl::fnd::Mutex m_Lock{};
		
	public:
		FontText(Font* pFont, csl::fnd::IAllocator* pAllocator) : m_pFont(pFont)
		{
			m_Params.change_allocator(pAllocator);
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
		
		void SetBasePos(csl::math::Vector2& pos)
		{
			m_BasePos = pos;
		}

		void SetEnable(bool enable)
		{
			m_Enabled = enable;
		}

		void Draw(Font* pFont)
		{
			if (pFont && m_Enabled && pFont->IsInit())
			{
				if (m_AutoFlush)
					pFont->Begin();
				
				m_Lock.Lock();
				
				for (auto& param : m_Params)
				{
					csl::math::Vector2 drawPos = param.m_Position;
					drawPos = drawPos + GetBasePos();

					pFont->SetTextColor(param.m_Color);
					pFont->SetTextSize(param.m_Size);
					pFont->DrawText(drawPos, param.m_pText);
				}
				
				m_Lock.Unlock();

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