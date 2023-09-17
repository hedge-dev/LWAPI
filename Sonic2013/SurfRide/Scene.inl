#include "Scene.h"
#pragma once

namespace SurfRide
{
	inline const ReferenceCount<Layer>& Scene::GetLayer(const char* in_pLayerName) const
	{
		if (!LayerCount)
			return {};

		for (size_t i = 0; i < LayerCount; i++)
		{
			if (!strcmp(prcLayers[i]->GetName(), in_pLayerName))
				return { prcLayers[i] };
		}

		return {};
	}
}