#pragma once

namespace app::animation
{
	class CharactorAnimationMultiLayer : public CharactorAnimation
	{
	protected:
		csl::ut::InplaceObjectMoveArray<AnimationTransition, 1> m_Layers{ nullptr };
		
	public:
		CharactorAnimationMultiLayer()
		{
			m_Layers[0] = AnimationTransition();
		}

		AnimationClip* GetCurrentAnimationClip(size_t layer, bool last) const
		{
			return m_Layers[layer].GetClip(last);
		}

		AnimationClip* GetCurrentAnimationClip(size_t layer) const
		{
			return GetCurrentAnimationClip(layer, false);
		}
		
		float GetFrame(size_t layer) const
		{
			auto* pClip = GetCurrentAnimationClip(layer);
			if (!pClip)
				return 0;

			return pClip->GetValue(AnimationNode::eGetEvent_Frame);
		}

		float GetEndFrame(size_t layer) const
		{
			auto* pClip = GetCurrentAnimationClip(layer);
			if (!pClip)
				return 0;

			return pClip->GetValue(AnimationNode::eGetEvent_EndFrame);
		}

		float GetSpeed(size_t layer) const
		{
			auto* pClip = GetCurrentAnimationClip(layer);
			if (!pClip)
				return 0;

			return pClip->GetValue(AnimationNode::eGetEvent_Speed);
		}

		void SetFrame(float frame, size_t layer)
		{
			auto* pClip = GetCurrentAnimationClip(layer);
			if (!pClip)
				return;

			pClip->SetValue(AnimationNode::eSetEvent_Frame, frame);
		}

		void SetSpeed(float speed, size_t layer)
		{
			auto* pClip = GetCurrentAnimationClip(layer);
			if (!pClip)
				return;

			pClip->SetValue(AnimationNode::eSetEvent_Speed, speed);
		}

		void ExitLoop(size_t layer)
		{
			m_Layers[layer].ExitLoop();
		}
		
		const char* GetCurrentAnimationName(size_t layer) const
		{
			auto* pClip = GetCurrentAnimationClip(layer);
			if (!pClip)
				return "";

			return pClip->GetAnimationDef()->m_pName;
		}

		const char* GetPrevAnimationName(size_t layer) const
		{
			auto* pClip = GetCurrentAnimationClip(layer, true);
			if (!pClip)
				return "";

			return pClip->GetAnimationDef()->m_pName;
		}

		bool IsCurrentAnimation(const char* pName, size_t layer) const
		{
			return !strcmp(GetCurrentAnimationName(layer), pName);
		}
	};
}