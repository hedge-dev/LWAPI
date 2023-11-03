#pragma once

namespace app::animation
{
	class AnimationComplex;
	
	class ComplexImpl : public fnd::ReferencedObject, public AnimationNode
	{
	public:
		AnimationComplex* pParent{};

		ComplexImpl()
		{

		}

		virtual void Setup() = 0;
		virtual void Cleanup() = 0;
		virtual AnimationClip* GetCurrentClip() = 0;
	};
}