#pragma once

namespace app::dbg
{
	class Menu;
	struct MenuEventArgs
	{
		bool Handled;
	};
	
	class MenuItem : public Object
	{
	public:
		csl::fnd::Delegate<void(Object*, MenuEventArgs& args), csl::fnd::DelegateAllocator> OnDecide;
		csl::fnd::Delegate<void(Object*, MenuEventArgs& args), csl::fnd::DelegateAllocator> OnCancel;

	protected:
		csl::ut::Bitset<uint> m_Flags;
		csl::math::Vector2 m_DisplayPos;
		size_t m_Unk1;
		app::font::FontText m_Text{ nullptr, nullptr };
		void* m_Unk2;
		Menu* m_pOwner;
		Menu* m_pParent;
		Menu* m_pSubMenu;
		
	public:
		virtual float GetHeight() const
		{
			return m_Text.GetSize().GetY();
		}

		virtual void OnDecide()
		{
			MenuEventArgs args{};
			OnDecide(this, args);
		}
		
		virtual void OnCancel()
		{
			MenuEventArgs args{};
			OnCancel(this, args);
		}

		void Draw()
		{
			m_Text.Draw();
		}

		void Draw(app::font::Font* in_pFont)
		{
			m_Text.Draw(in_pFont);
		}
	};
}