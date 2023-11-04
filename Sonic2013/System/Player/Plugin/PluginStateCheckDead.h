#pragma once

namespace app::Player
{
	class PluginStateCheckDead : public CStatePlugin
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00E00420);

	protected:
		csl::ut::Bitset<uint> Unk1{};
		float Unk2{ -5000.0f };
		csl::math::Vector3 Unk3{};
		int Unk4{ -1 };

	public:
		PluginStateCheckDead() : CStatePlugin(ms_pName)
		{

		}

		bool HitCheckPressCollision(CStateGOC& in_rStateGoc, xgame::MsgHitTriggerBase& in_rMessage)
		{
			if (!(in_rMessage.pOther->Unk3 & 0x1000))
				return false;

			Unk1.set(2, true);
			return true;
		}
	};
}