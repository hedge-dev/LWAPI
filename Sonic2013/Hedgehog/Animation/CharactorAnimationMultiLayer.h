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

		AnimationClip* GetCurrentAnimationClip(size_t in_layer, bool in_last) const
		{
			return m_Layers[in_layer].GetClip(in_last);
		}

		AnimationClip* GetCurrentAnimationClip(size_t in_layer) const
		{
			return GetCurrentAnimationClip(in_layer, false);
		}
		
		float GetFrame(size_t in_layer) const
		{
			auto* pClip = GetCurrentAnimationClip(in_layer);
			if (!pClip)
				return 0;

			return pClip->GetValue(AnimationNode::eGetEvent_Frame);
		}

		float GetEndFrame(size_t in_layer) const
		{
			auto* pClip = GetCurrentAnimationClip(in_layer);
			if (!pClip)
				return 0;

			return pClip->GetValue(AnimationNode::eGetEvent_EndFrame);
		}

		float GetSpeed(size_t in_layer) const
		{
			auto* pClip = GetCurrentAnimationClip(in_layer);
			if (!pClip)
				return 0;

			return pClip->GetValue(AnimationNode::eGetEvent_Speed);
		}

		void SetFrame(float in_frame, size_t in_layer)
		{
			auto* pClip = GetCurrentAnimationClip(in_layer);
			if (!pClip)
				return;

			pClip->SetValue(AnimationNode::eSetEvent_Frame, in_frame);
		}

		void SetSpeed(float in_speed, size_t in_layer)
		{
			auto* pClip = GetCurrentAnimationClip(layer);
			if (!pClip)
				return;

			pClip->SetValue(AnimationNode::eSetEvent_Speed, in_speed);
		}

		void ExitLoop(size_t in_layer)
		{
			m_Layers[in_layer].ExitLoop();
		}
		
		const char* GetCurrentAnimationName(size_t in_layer) const
		{
			auto* pClip = GetCurrentAnimationClip(in_layer);
			if (!pClip)
				return "";

			return pClip->GetAnimationDef()->pName;
		}

		const char* GetPrevAnimationName(size_t in_layer) const
		{
			auto* pClip = GetCurrentAnimationClip(in_layer, true);
			if (!pClip)
				return "";

			return pClip->GetAnimationDef()->pName;
		}

		bool IsCurrentAnimation(const char* in_pName, size_t in_layer) const
		{
			return !strcmp(GetCurrentAnimationName(in_layer), in_pName);
		}
	};
}