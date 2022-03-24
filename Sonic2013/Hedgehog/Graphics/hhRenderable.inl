#pragma once

namespace app::gfx
{
	inline Renderable::~Renderable()
	{
		if (m_pContainer)
			m_pContainer->RemoveObject(this);
	}
}