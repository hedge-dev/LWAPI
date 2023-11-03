#pragma once

namespace app::gfx
{
	inline Renderable::~Renderable()
	{
		if (pContainer)
			pContainer->RemoveObject(this);
	}
}