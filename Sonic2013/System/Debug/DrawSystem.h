#pragma once

namespace app::dbg
{
	class DrawSystem
	{
	private:
		inline static DrawSystem& ms_rInstance = *reinterpret_cast<DrawSystem*>(ASLR(0x00FD405C));
		
	public:
		typedef DrawContext* CreateDrawContext_t(csl::fnd::IAllocator* in_pAllocator);
		typedef GraphicsGeometry* CreateGraphicsGeometry_t(DrawContext* in_pContext, csl::fnd::IAllocator* in_pAllocator);

		CreateDrawContext_t* fpDrawContextFactory{};
		CreateGraphicsGeometry_t* fpGraphicsGeometryFactory{};

		[[nodiscard]] DrawContext* CreateContext(csl::fnd::IAllocator* in_pAllocator) const
		{
			return fpDrawContextFactory(in_pAllocator);
		}

		[[nodiscard]] GraphicsGeometry* CreateGeometry(DrawContext* in_pContext, csl::fnd::IAllocator* in_pAllocator) const
		{
			return fpGraphicsGeometryFactory(in_pContext, in_pAllocator);
		}

		inline static DrawSystem& GetInstance()
		{
			return ms_rInstance;
		}
	};
}