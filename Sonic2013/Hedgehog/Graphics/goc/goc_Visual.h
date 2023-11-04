#pragma once

namespace app::fnd
{
	class GOCVisual : public GOComponent
	{
		typedef char Flag;
		typedef char VisualType;
		
	public:
		csl::ut::Bitset<Flag> Flags;
		VisualType Visual;
		
		GOCVisual(VisualType in_type) : GOComponent(), Visual(in_type)
		{
			ASSERT_OFFSETOF(GOCVisual, Flags, 0x3C);
			ASSERT_OFFSETOF(GOCVisual, Visual, 0x3D);
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