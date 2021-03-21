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
			return m_GlobalWeight;
		}

		void SetWeight(float weight) override
		{
			m_GlobalWeight = weight;
		}

		void Update() override
		{
			if (m_pClip)
				m_pClip->SetValue(AnimationNode::eSetEvent_Weight, m_pBaseBlender->m_GlobalWeight * m_GlobalWeight);
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