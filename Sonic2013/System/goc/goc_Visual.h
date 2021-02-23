#pragma once

namespace app::fnd
{
	class GOCVisual : public GOComponent
	{
		typedef char VisualType;
		
	protected:
		char unk1{};
		VisualType visualType;
		
		GOCVisual(VisualType type) : GOComponent(), visualType(type)
		{
			ASSERT_OFFSETOF(GOCVisual, unk1, 0x3C);
			ASSERT_OFFSETOF(GOCVisual, visualType, 0x3D);
		}
	};
}