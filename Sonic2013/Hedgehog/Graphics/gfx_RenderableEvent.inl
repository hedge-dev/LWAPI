#pragma once

namespace app::gfx
{
	inline void RenderableEvent::Invoke(const hh::gfx::RenderEventParam& in_rParam)
	{
		pOwner->Render(in_rParam);
	}
}