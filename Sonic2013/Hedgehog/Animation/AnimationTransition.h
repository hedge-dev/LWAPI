#pragma once

namespace app::animation
{
	class TransitionArray;
	class AnimationTransition
	{
	public:
		enum EStatus
		{
			eStatus_Stopped,
			eStatus_Changing,
			eStatus_Playing
		};
		
		AnimationClip* m_pCurClip{};
		AnimationClip* m_pLastClip{};
		EStatus m_Status{};
		csl::ut::Bitset<uint> m_PlaybackFlags{};
		AnimationNodeManager* m_pManager{};
		const TransitionArray* m_pTransitions{};
		float m_InterpolateWeight{};
		void* m_pUnk1{};

	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x00413A30), AnimationTransition*, float);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetAnimation, ASLR(0x00413750), AnimationTransition*, AnimationClip*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpChangeAnimation, ASLR(0x00413800), AnimationTransition*, AnimationClip*);

		void Update(float in_delta)
		{
			ms_fpUpdate(this, in_delta);
		}

		void SetAnimation(AnimationClip* in_pClip)
		{
			ms_fpSetAnimation(this, in_pClip);
		}

		void ChangeAnimation(AnimationClip* in_pClip)
		{
			ms_fpChangeAnimation(this, in_pClip);
		}

		void Setup(AnimationNodeManager* in_pManager, const TransitionArray* in_pTransitions)
		{
			sizeof(AnimationTransition);
			m_pManager = in_pManager;
			m_pTransitions = in_pTransitions;
		}

		void ClearAll()
		{
			if (m_pLastClip)
			{
				RemoveAnimation(*m_pLastClip);
				m_pLastClip->m_State = 0;
				m_pLastClip = nullptr;
			}

			if (m_pCurClip)
			{
				RemoveAnimation(*m_pCurClip);
				m_pCurClip->m_State = 0;
				m_pCurClip = nullptr;
			}

			ResetInterpolateInfo();
			ChangeStatus(eStatus_Stopped);
		}

		void Cleanup()
		{
			ClearAll();
			m_pManager = nullptr;
			m_pTransitions = nullptr;
		}

		void ResetInterpolateInfo()
		{
			m_InterpolateWeight = 0;
			m_pUnk1 = nullptr;
		}

		void RemoveAnimation(AnimationClip& in_clip)
		{
			in_clip.ProcEvent(AnimationNode::eEvent_Detach);
		}

		void ChangeStatus(EStatus in_status)
		{
			bool playing = m_PlaybackFlags.test(eStatus_Playing);
			m_PlaybackFlags.reset();
			m_PlaybackFlags.set(eStatus_Playing, playing);

			m_Status = in_status;
		}

		AnimationClip* GetClip(bool last = false) const
		{
			if (last)
				return m_pLastClip;

			return m_pCurClip;
		}

		bool IsInterpolate() const
		{
			return m_Status == 2;
		}

		bool IsFinished() const
		{
			return m_PlaybackFlags.test(1);
		}

		bool IsFinishedEdge() const
		{
			return m_PlaybackFlags.test(2);
		}

		void ExitLoop()
		{
			m_PlaybackFlags.set(0);
		}
	};
}