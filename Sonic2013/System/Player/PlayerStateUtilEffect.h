#pragma once

namespace app::Player
{
}

namespace app::Player::StateUtil
{
	void SetPauseItemEffect(CStateGOC& in_rStateGoc, bool in_pause);

	void RetireHomingEffect(CStateGOC& in_rStateGoc);

	hh::eff::CInstanceHandle<hh::eff::CEffectInstance>& CreateFollowEffect(hh::eff::CInstanceHandle<hh::eff::CEffectInstance>* out_pEffect, CStateGOC& in_rStateGoc, const char* in_pBoneName, const char* in_pEffectName, bool in_unk);
	
	void CreateSpringFollowEffect(CStateGOC& in_rStateGoc);
	
	GOCReferenceHolderUnit& GetCurrentGOCUnit(CStateGOC& in_rStateGoc);
	
	hh::eff::CInstanceHandle<hh::eff::CEffectInstance> CreateEffectOffset(CStateGOC& in_rStateGoc, const char* in_pEffectName, NodeID in_nodeId, const csl::math::Matrix34& in_rOffset);

	hh::eff::CInstanceHandle<hh::eff::CEffectInstance> CreateEffectOffset(CStateGOC& in_rStateGoc, const char* in_pEffectName, NodeID in_nodeId, const csl::math::Vector3& in_rOffset);

	app::Effect::CEffectHandle<>* CreateFollowEffect(app::Effect::CEffectHandle<>* out_pEffect, CStateGOC& in_rStateGoc, const char* in_pEffectName, NodeID in_nodeId, const csl::math::Vector3& in_rOffset, bool in_unk);

	void StopFollowEffect(CStateGOC& in_rStateGoc, app::Effect::CEffectHandle<> in_rEffect, bool in_unk);

}