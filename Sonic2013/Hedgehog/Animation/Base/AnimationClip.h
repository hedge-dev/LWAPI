#pragma once
namespace app::animation
{
	struct AnimationDef;
	struct InterpolateArray;
	
	class AnimationClip : public AnimationNode
	{
	public:
		csl::ut::LinkListNode m_ListNode{};
		AnimationClip* m_pParent{};
		uint m_State{};

		AnimationClip()
		{

		}
		
		DEFINE_RTTI_PTR(ASLR(0x00F61114))

		virtual const AnimationDef* GetAnimationDef() const = 0;
		virtual const InterpolateArray* GetInterpolateArray() const = 0;
	};
}