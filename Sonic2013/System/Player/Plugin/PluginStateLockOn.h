#pragma once

namespace app::Player
{
	class CPluginStateLockOn : public CStatePlugin
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00E00820);

	protected:
		csl::ut::Bitset<uint> Unk1{};
		int Unk2{};
		int Unk3{};

	public:
		CPluginStateLockOn() : CStatePlugin(ms_pName)
		{

		}

		void SetDisable(bool in_disable)
		{
			Unk1.set(5, in_disable);
		}

		CHomingTargetService* GetTargetService(CStateGOC& in_rStateGoc)
		{
			return in_rStateGoc.pPlayer->spHomingService.get();
		}

		void HitCheckTargetCollision(CStateGOC& in_rStateGoc, xgame::MsgHitTriggerBase& in_rMessage)
		{
			GetTargetService(in_rStateGoc)->HitCollision(in_rMessage.pSelf, in_rMessage.pOther);
		}
	};
}