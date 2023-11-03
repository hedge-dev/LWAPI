#pragma once

namespace app::gfx
{
	class Renderable;

	class RenderableEvent : public hh::gfx::RenderEvent
	{
	public:
		uint Unk1{ 1 };
		Renderable* pOwner{};

		RenderableEvent() = default;
		RenderableEvent(Renderable* in_pOwner) : pOwner(in_pOwner)
		{

		}

		void Invoke(const hh::gfx::RenderEventParam& in_rParam) override;
	};
}