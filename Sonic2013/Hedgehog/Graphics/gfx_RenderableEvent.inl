#pragma once

namespace app::gfx
{
	inline void RenderableEvent::Invoke(const hh::gfx::RenderEventParam& in_param)
	{
		m_pOwner->Render(in_param);
	}
}