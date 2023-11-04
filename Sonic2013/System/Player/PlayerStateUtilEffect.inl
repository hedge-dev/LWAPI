#pragma once

namespace app::Player
{
	typedef int NodeID;
}

namespace app::Player::StateUtil
{
	inline void SetPauseItemEffect(CStateGOC& in_rStateGoc, bool in_pause)
	{
		FUNCTION_PTR(void, __cdecl, fpSetPauseItemEffect, ASLR(0x008DB920), CStateGOC&, bool);
		fpSetPauseItemEffect(in_rStateGoc, in_pause);
	}

	inline void RetireHomingEffect(CStateGOC& in_rStateGoc)
	{
		FUNCTION_PTR(void, __cdecl, fpRetireHomingEffect, ASLR(0x008DB8A0), CStateGOC&);
		fpRetireHomingEffect(in_rStateGoc);
	}

	inline hh::eff::CInstanceHandle<hh::eff::CEffectInstance>& CreateFollowEffect(hh::eff::CInstanceHandle<hh::eff::CEffectInstance>* out_pEffect, CStateGOC& in_rStateGoc, const char* in_pBoneName, const char* in_pEffectName, bool in_unk)
	{
		FUNCTION_PTR(hh::eff::CInstanceHandle<hh::eff::CEffectInstance>&, __cdecl, fpCreateFollowEffect, ASLR(0x008DB000), hh::eff::CInstanceHandle<hh::eff::CEffectInstance>*, CStateGOC&, const char*, const char*, bool);
		return fpCreateFollowEffect(out_pEffect, in_rStateGoc, in_pBoneName, in_pEffectName, in_unk);
	}

	inline GOCReferenceHolderUnit& GetCurrentGOCUnit(CStateGOC& in_rStateGoc)
	{
		return in_rStateGoc.pPlayer->GetComponent<GOCCollector>()->GetCurrentHolder().GetUnit(0);
	}

	inline hh::eff::CInstanceHandle<hh::eff::CEffectInstance> CreateEffectOffset(CStateGOC& in_rStateGoc, const char* in_pEffectName, NodeID in_nodeId, const csl::math::Matrix34& in_rOffset)
	{
		if (in_rStateGoc.Unk7)
			return { nullptr };
		
		auto& unit = GetCurrentGOCUnit(in_rStateGoc);
		in_rStateGoc.GetVisualGoc()->GetHumanVisual();

		csl::math::Matrix34 rotationMatrix = in_rOffset;
		rotationMatrix.SetTransVector({ 0.0f, 0.0f, 0.0f });

		game::EffectCreateInfo createInfo{};
		createInfo.pName = in_pEffectName;
		createInfo.Position = in_rOffset.GetTransVector();
		createInfo.Rotation = { rotationMatrix };
		createInfo.Unk1 = 1.0f;
		createInfo.Unk2 = 1;
		createInfo.Unk3 = true;
		createInfo.pVisual = unit.rpModel.get();
		createInfo.pBoneName = GetVisualHumanNodeName(in_nodeId);

		return unit.CreateEffect(createInfo);
	}

	inline hh::eff::CInstanceHandle<hh::eff::CEffectInstance> CreateEffectOffset(CStateGOC& in_rStateGoc, const char* in_pEffectName, NodeID in_nodeId, const csl::math::Vector3& in_rOffset)
	{
		if (in_rStateGoc.Unk7)
			return { nullptr };

		csl::math::Matrix34 offsetMtx{};
		offsetMtx.SetColumn(3, in_rOffset);
		
		return CreateEffectOffset(in_rStateGoc, in_pEffectName, in_nodeId, offsetMtx);
	}

	inline app::Effect::CEffectHandle<>* CreateFollowEffect(app::Effect::CEffectHandle<>* out_pEffect, CStateGOC& in_rStateGoc, const char* in_pEffectName, NodeID in_nodeId, const csl::math::Vector3& in_rOffset, bool in_unk)
	{
		FUNCTION_PTR(app::Effect::CEffectHandle<>*, __cdecl, fpCreateFollowEffect, ASLR(0x008DBAA0), app::Effect::CEffectHandle<>*, CStateGOC&, const char*, NodeID, const csl::math::Vector3&, bool);
		return fpCreateFollowEffect(out_pEffect, in_rStateGoc, in_pEffectName, in_nodeId, in_rOffset, in_unk);
	}

	inline void StopFollowEffect(CStateGOC& in_rStateGoc, app::Effect::CEffectHandle<> in_rEffect, bool in_unk)
	{
		FUNCTION_PTR(void, __cdecl, fpStopFollowEffect, ASLR(0x008DAA10), CStateGOC&, app::Effect::CEffectHandle<>, bool);
		fpStopFollowEffect(in_rStateGoc, in_rEffect, in_unk);
	}
}