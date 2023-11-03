#pragma once

namespace app::HUD::SRUtility
{
	inline static FUNCTION_PTR(bool, __cdecl, ms_fpSetAnimation, ASLR(0x00525070), const SurfRide::ReferenceCount<SurfRide::Layer>&, const char*, bool, float, bool, bool);
	inline static FUNCTION_PTR(bool, __cdecl, ms_fpSetAnimationID, ASLR(0x00525100), const SurfRide::ReferenceCount<SurfRide::Layer>&, int, bool, float, bool, bool, bool);
	inline static FUNCTION_PTR(void, __cdecl, ms_fpSetCastPatternIndex, ASLR(0x00525800), const SurfRide::ReferenceCount<SurfRide::Layer>&, const char*, int);
	inline static FUNCTION_PTR(void, __cdecl, ms_fpAllLayerHide, ASLR(0x00526290), SurfRide::ReferenceCount<SurfRide::Scene>&);
	inline static FUNCTION_PTR(void, __cdecl, ms_fpSetCastText, ASLR(0x005255C0), const SurfRide::ReferenceCount<SurfRide::Layer>&, const char*, const char*);

	inline bool SetAnimationID(const SurfRide::ReferenceCount<SurfRide::Layer>& in_rrcLayer, int in_animationId, bool in_isLooping, float in_frame, bool in_unk2, bool in_isHide, bool in_unk4)
	{
		return ms_fpSetAnimationID(in_rrcLayer, in_animationId, in_isLooping, in_frame, in_unk2, in_isHide, in_unk4);
	}

	inline bool SetAnimation(const SurfRide::ReferenceCount<SurfRide::Layer>& in_rrcLayer, const char* in_pAnimationName, bool in_isLooping, float in_frame, bool in_unk1, bool in_unk2)
	{
		return ms_fpSetAnimation(in_rrcLayer, in_pAnimationName, in_isLooping, in_frame, in_unk1, in_unk2);
	}

	inline void SetCastPatternIndex(const SurfRide::ReferenceCount<SurfRide::Layer>& in_rrcLayer, const char* in_pCastName, int in_index)
	{
		ms_fpSetCastPatternIndex(in_rrcLayer, in_pCastName, in_index);
	}

	inline void AllLayerHide(SurfRide::ReferenceCount<SurfRide::Scene>& in_rrcScene)
	{
		ms_fpAllLayerHide(in_rrcScene);
	}

	inline void SetCastText(const SurfRide::ReferenceCount<SurfRide::Layer>& in_rrcLayer, const char* in_pCastName, const char* in_pText)
	{
		ms_fpSetCastText(in_rrcLayer, in_pCastName, in_pText);
	}
}

namespace app::game
{
	enum HudPlayPolicy
	{
		eHudPlayPolicy_Once,
		eHudPlayPolicy_Loop
	};

	class HudLayerController : public fnd::ReferencedObject
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpPlayAnimation, ASLR(0x004C0F50), HudLayerController*, const char*, bool, int);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetVisible, ASLR(0x004C0E60), HudLayerController*, bool);

	public:
		struct PlayInfo
		{
			const char* pAnimationName{};
			int AnimationID{ -1 };
			HudPlayPolicy PlayPolicy{};
			float Frame{ -1.0f };
			bool Unk2{};
		};

		struct alignas(4) AnimationInfo
		{
			int AnimationID{};
			csl::ut::Enum<HudPlayPolicy, byte> PlayPolicy{};
			bool Unk1{};
		};

	public:
		SurfRide::ReferenceCount<SurfRide::Layer> rcLayer{};
		byte ControllerNo{};
		char Unk2{ -1 };
		INSERT_PADDING(2) {};
		csl::ut::MoveArray<AnimationInfo> AnimationInfo{};
		csl::ut::Bitset<char> Unk3{};

		HudLayerController(csl::fnd::IAllocator* in_pAllocator, SurfRide::ReferenceCount<SurfRide::Layer> in_rcLayer, byte in_controllerNo)
			: rcLayer(in_rcLayer)
			, ControllerNo(in_controllerNo)
			, m_AnimationInfo(in_pAllocator)
		{

		}

		bool PlayAnimation(const PlayInfo& in_rPlayInfo)
		{
			int animationID = in_rPlayInfo.AnimationID;
			if (animationID < 0 && (animationID = rcLayer->GetAnimationID(in_rPlayInfo.pAnimationName)) < 0)
				return false;

			return HUD::SRUtility::SetAnimationID(rcLayer, animationID, in_rPlayInfo.PlayPolicy, in_rPlayInfo.Frame, in_rPlayInfo.Unk2, false, false);
		}

		bool PlayAnimation(int in_animationId, HudPlayPolicy in_playPolicy, bool in_unk)
		{
			if (in_animationId < 0)
				return false;

			PlayInfo playInfo{};
			playInfo.AnimationID = in_animationId;
			playInfo.PlayPolicy = in_playPolicy;
			playInfo.Unk2 = in_unk;
			return PlayAnimation(playInfo);
		}

		bool PlayAnimation(const char* in_animationName, HudPlayPolicy in_playPolicy, bool in_unk)
		{
			int animID = rcLayer->GetAnimationID(in_animationName);
			if (animID < 0)
				return false;
			
			return PlayAnimation(animID, in_playPolicy, in_unk);
		}
		
		void SetVisible(bool in_isVisible)
		{
			rcLayer->SetHideFlag(!in_isVisible);
		}

		bool IsCurrentAnimation(const char* in_pAnimationName) const
		{
			return rcLayer->GetAnimationID() == rcLayer->GetAnimationID(in_pAnimationName);
		}

		void ReserveAnimation(const char* in_pAnimationName, HudPlayPolicy in_playPolicy, bool in_unk)
		{
			AnimationInfo.push_back({ rcLayer->GetAnimationID(in_pAnimationName), in_playPolicy, in_unk });
		}

		void PlayReservedAnimation()
		{
			if (m_AnimationInfo.empty())
				return;
		
			Unk2 = 0;
			PlayAnimation(AnimationInfo[0].AnimationID, AnimationInfo[0].PlayPolicy, AnimationInfo[0].Unk1);
		}

		bool IsEndAnimation()
		{
			return rcLayer->IsAnimationEnd;
		}

		bool IsEndReservedAnimation()
		{
			return m_Unk2 < 0;
		}

		void ClearReservedAnimation()
		{
			if (rcLayer->Unk3)
				rcLayer->SetRepeatFlag(false);
			
			AnimationInfo.clear();
			Unk2 = -1;
			Unk3.reset(0);
		}

		void Reset()
		{
			ClearReservedAnimation();
			rcLayer->Unk2 = true;
		}
	};
}