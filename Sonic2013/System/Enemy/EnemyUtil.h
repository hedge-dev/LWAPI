#pragma once

namespace app::EnemyUtil
{
	static bool IsDamage(int in_unk1, int in_unk2, uint in_type)
	{
		return AttackType::Any(in_type) && in_unk1 > in_unk2;
	}

	static bool IsFatalDamage(const xgame::MsgDamage& in_rMessage)
	{
		if (AttackType::And(in_rMessage.AttackType, 0x8000) || AttackType::And(in_rMessage.AttackType, 0x400000))
			return true;
	
		return false;
	}
}
