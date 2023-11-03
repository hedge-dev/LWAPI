#pragma once

namespace app::animation
{
	class TransitionArray;

	class AnimationTransition
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x00413A30), AnimationTransition*, float);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetAnimation, ASLR(0x00413750), AnimationTransition*, AnimationClip*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpChangeAnimation, ASLR(0x00413800), AnimationTransition*, AnimationClip*);

	public:
		enum EStatus
		{
			eStatus_Stopped,
			eStatus_Changing,
			eStatus_Playing
		};
		
		AnimationClip* pCurClip{};
		AnimationClip* pLastClip{};
		EStatus Status{};
		csl::ut::Bitset<uint> PlaybackFlags{};
		AnimationNodeManager* pManager{};
		const TransitionArray* pTransitions{};
		float InterpolateWeight{};
		void* pUnk1{};

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
			pManager = in_pManager;
			pTransitions = in_pTransitions;
		}

		void ClearAll()
		{
			if (pLastClip)
			{
				RemoveAnimation(*pLastClip);
				pLastClip->State = 0;
				pLastClip = nullptr;
			}

			if (pCurClip)
			{
				RemoveAnimation(*pCurClip);
				pCurClip->State = 0;
				pCurClip = nullptr;
			}

			ResetInterpolateInfo();
			ChangeStatus(eStatus_Stopped);
		}

		void Cleanup()
		{
			ClearAll();
			pManager = nullptr;
			pTransitions = nullptr;
		}

		void ResetInterpolateInfo()
		{
			InterpolateWeight = 0;
			pUnk1 = nullptr;
		}

		void RemoveAnimation(AnimationClip& in_rClip)
		{
			in_rClip.ProcEvent(AnimationNode::eEvent_Detach);
		}

		void ChangeStatus(EStatus in_status)
		{
			bool playing = PlaybackFlags.test(eStatus_Playing);
			PlaybackFlags.reset();
			PlaybackFlags.set(eStatus_Playing, playing);

			Status = in_status;
		}

		AnimationClip* GetClip(bool in_last = false) const
		{
			if (in_last)
				return pLastClip;

			return pCurClip;
		}

		bool IsInterpolate() const
		{
			return Status == 2;
		}

		bool IsFinished() const
		{
			return PlaybackFlags.test(1);
		}

		bool IsFinishedEdge() const
		{
			return PlaybackFlags.test(2);
		}

		void ExitLoop()
		{
			PlaybackFlags.set(0);
		}
	};
}