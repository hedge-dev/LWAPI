#pragma once

namespace app::dbg
{
	class DrawSystem
	{
	public:
		inline static DrawSystem& ms_rInstance = *reinterpret_cast<DrawSystem*>(ASLR(0x00FD405C));
		typedef DrawContext* CreateDrawContext_t(csl::fnd::IAllocator* in_pAllocator);
		typedef GraphicsGeometry* CreateGraphicsGeometry_t(csl::fnd::IAllocator* in_pAllocator);

		CreateDrawContext_t* m_fpDrawContextFactory{};
		CreateGraphicsGeometry_t* m_fpGraphicsGeometryFactory{};

		[[nodiscard]] DrawContext* CreateContext(csl::fnd::IAllocator* in_pAllocator) const
		{
			return m_fpDrawContextFactory(in_pAllocator);
		}

		[[nodiscard]] GraphicsGeometry* CreateGeometry(csl::fnd::IAllocator* in_pAllocator) const
		{
			return m_fpGraphicsGeometryFactory(in_pAllocator);
		}

		inline static DrawSystem& GetInstance()
		{
			return ms_rInstance;
		}
	};
}