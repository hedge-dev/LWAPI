#pragma once
#include "Project.h"

namespace SurfRide
{
	inline const ReferenceCount<Scene> Project::GetScene(const char* in_pSceneName) const
	{
        if (!SceneCount)
            return {};

        for (size_t i = 0; i < SceneCount; i++)
        {
            if (!strcmp(prcScenes[i]->GetName(), in_pSceneName))
                return { prcScenes[i] };
        }

        return {};
	}
}