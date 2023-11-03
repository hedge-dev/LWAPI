#pragma once

namespace app::fnd
{
	class GOCVisual : public GOComponent
	{
		typedef char Flag;
		typedef char VisualType;
		
	public:
		//Flag m_Flags{};
		csl::ut::Bitset<Flag> Flags;
		VisualType VisualType;
		
		GOCVisual(VisualType in_type) : GOComponent(), VisualType(in_type)
		{
			ASSERT_OFFSETOF(GOCVisual, Flags, 0x3C);
			ASSERT_OFFSETOF(GOCVisual, VisualType, 0x3D);
		}

		virtual void OnGOCVisualEvent(int, uint, void*) = 0;
		
	public:
		bool IsVisible() const
		{
			return Flags.test(0);
		}

		void SetVisible(bool in_visibility)
		{
			Flags.set(0, in_visibility);
			OnGOCVisualEvent(0, 0, nullptr);
		}
	};
}