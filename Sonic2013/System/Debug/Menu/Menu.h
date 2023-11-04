#pragma once

namespace app::dbg
{
	class Menu : public Object
	{
	protected:
		csl::ut::Bitset<uint> m_Flags;
		std::dummy::vector<MenuItem*> m_Items;
		uint m_Cursor;
		uint m_Unk1;
		uint m_SelectedIndex;
		uint m_DisplayCount;
		csl::math::Vector2 m_Pos;
		csl::math::Vector2 m_BasePos;
		uint m_SelectionDelay;
		Menu* m_pParent;

	public:
		void Draw()
		{
			for (auto& item : m_Items)
			{
				item->Draw();
			}
		}

		void Draw(app::font::Font* in_pFont)
		{
			for (auto& item : m_Items)
			{
				item->Draw(in_pFont);
			}
		}
	};
}