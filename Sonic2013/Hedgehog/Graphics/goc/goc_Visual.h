#pragma once

namespace app::fnd
{
	class GOCVisual : public GOComponent
	{
		typedef char Flag;
		typedef char VisualType;
		
	protected:
		//Flag m_Flags{};
		csl::ut::Bitset<Flag> m_Flags;
		VisualType visualType;
		
		GOCVisual(VisualType type) : GOComponent(), visualType(type)
		{
			ASSERT_OFFSETOF(GOCVisual, m_Flags, 0x3C);
			ASSERT_OFFSETOF(GOCVisual, visualType, 0x3D);
		}

		virtual void OnGOCVisualEvent(int, uint, void*) = 0;
		
	public:
		bool IsVisible() const
		{
			return m_Flags.test(0);
		}

		void SetVisibility(bool visibility)
		{
			m_Flags.set(0, visibility);
			OnGOCVisualEvent(0, 0, nullptr);
		}
	};
}