#pragma once

namespace app::animation
{
	class SimpleBlender;
	class ComplexBlender : public fnd::ReferencedObject
	{
	public:
		float m_GlobalWeight{};
		
		virtual void SetWeight(float weight) = 0;
		virtual float GetWeight() const = 0;
		virtual void Update() = 0;
		virtual void ResetParameter() = 0;
		virtual SimpleBlender* GetSimpleBlender() = 0;
	};
}