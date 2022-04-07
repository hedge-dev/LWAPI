#pragma once

namespace app::fnd
{
	class WireGeometry;
}

namespace app::dbg
{
	class GraphicsGeometry : public fnd::ReferencedObject
	{
	public:
		virtual void Initialize(DrawContext* in_pContext, const fnd::Geometry& in_geometry, const csl::math::Matrix34& in_transform) = 0;
		virtual void InitializeEdge(DrawContext* in_pContext, const fnd::Geometry& in_geometry, const csl::math::Matrix34& in_transform) = 0;
		virtual void InitializeWire(DrawContext* in_pContext, const fnd::WireGeometry& in_geometry, const csl::math::Matrix34& in_transform) = 0;
		virtual void InitializeByCopying(DrawContext* in_pContext, const GraphicsGeometry* in_pGeometry, const csl::math::Matrix34& in_transform) = 0;
		virtual void SetColor(const csl::ut::Color8& in_color) = 0;
		virtual void SetTransform(const csl::math::Matrix34& in_transform) = 0;
		virtual void Render(DrawContext* in_pContext) = 0;
	};
}