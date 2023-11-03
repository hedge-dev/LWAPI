#pragma once

namespace app::animation
{
	class SimpleBlender : public ComplexBlender
	{
	protected:
		AnimationClip* m_pClip{};
		ComplexBlender* m_pBaseBlender{};
		uint m_pUnk1{};

	public:
		SimpleBlender() {}
		
		float GetWeight() const override
		{
			return GlobalWeight;
		}

		void SetWeight(float in_weight) override
		{
			GlobalWeight = in_weight;
		}

		void Update() override
		{
			if (m_pClip)
				m_pClip->SetValue(AnimationNode::eSetEvent_Weight, m_pBaseBlender->GlobalWeight * GlobalWeight);
		}

		SimpleBlender* GetSimpleBlender() override
		{
			return nullptr;
		}

		void ResetParameter() override
		{
			
		}
	};
}