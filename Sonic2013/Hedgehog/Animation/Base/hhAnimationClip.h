#pragma once
namespace app::animation
{
	struct AnimationDef;
	struct InterpolateArray;
	
	class AnimationClip : public AnimationNode
	{
		csl::ut::LinkListNode m_ListNode{};
		INSERT_PADDING(8){};

	public:
		DEFINE_RTTI_PTR(ASLR(0x00F61114))

		virtual const AnimationDef* GetAnimationDef() const = 0;
		virtual const InterpolateArray* GetInterpolateArray() const = 0;
	};
}