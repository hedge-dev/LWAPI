#pragma once

namespace app::gfx
{
	class Renderable;
	class RenderableEvent : public hh::gfx::RenderEvent
	{
	public:
		uint m_Unk1{ 1 };
		Renderable* m_pOwner{};

		RenderableEvent() = default;
		RenderableEvent(Renderable* in_pOwner) : m_pOwner(in_pOwner)
		{

		}

		void Invoke(const hh::gfx::RenderEventParam& in_param) override;
	};
}