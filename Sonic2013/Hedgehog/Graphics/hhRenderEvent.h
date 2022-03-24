#pragma once

namespace hh::mr
{
	class CRenderingInfrastructure;
	class CRenderingDevice;
}

namespace hh::gfx
{
	class RenderContext;
	struct RenderEventParam
	{
		struct
		{
			mr::CRenderingDevice* m_pDevice{};
			mr::CRenderingInfrastructure* m_pInfrastructure{};
			RenderContext* m_pContext{};
		} *RenderParams;

		INSERT_PADDING(12){};
	};

	class RenderEvent
	{
	public:
		virtual void Invoke(const RenderEventParam& in_param) = 0;
	};
}