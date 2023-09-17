#include "PathComponent.h"
#pragma once

namespace app::game
{
	inline void PathComponent::Cleanup()
	{
		if (!pManager)
			return;

		pManager->RemoveObject(this);
		pManager = nullptr;
	}
}