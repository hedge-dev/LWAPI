#include "SnowBall.h"
#pragma once

namespace app::Player
{
	inline void CSnowBall::SetMovableGroundLock(bool in_lockAbility)
	{
		if (in_lockAbility)
		{
			if (Unk60)
				return;

			Unk60 = true;
			if (!HaveOwner())
				return;

			StateUtil::SetRCLockHoverAbility(*GetOwner()->GetStateGOC(), true);
		}
		else if (Unk60)
		{
			Unk60 = false;
			if (HaveOwner())
				return;

			StateUtil::SetRCLockHoverAbility(*GetOwner()->GetStateGOC(), false);
		}
	}

	inline void CSnowBall::ResetPathMode()
	{
		if (!Path.Component.IsValid())
			return;

		Path.Reset();
		if (!HaveOwner())
			return;

		StateUtil::SetRCLockHoverAbility(*GetOwner()->GetStateGOC(), false);
	}
}