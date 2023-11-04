#pragma once

namespace app::dbg
{
	class Texture;
	
	enum PrimitiveType
	{
		ePrimitiveType_PointList,
		ePrimitiveType_LineList,
		ePrimitiveType_LineStrip,
		ePrimitiveType_TriangleStrip,
		ePrimitiveType_TriangleFan
	};

	struct DrawVertex
	{
		float X{};
		float Y{};
		float Z{};
		csl::ut::Color8 Color{ 255,255,255,255 };
	};

	using DrawVertexT = DrawVertex;

	class DrawContext : public fnd::ReferencedObject
	{
	public:
		virtual void BeginScene() = 0;
		virtual void EndScene() = 0;
		virtual void BeginDraw() = 0;
		virtual void EndDraw() = 0;
		virtual void BeginDraw2d() = 0;
		virtual void EndDraw2d() = 0;
		virtual void DrawPrimitive(PrimitiveType in_type, const DrawVertex* in_pVertices, const ushort* in_pIndices, int in_count) = 0;
		virtual void DrawPrimitive(PrimitiveType in_type, Texture* in_pTexture, const DrawVertexT* in_pVertices, const ushort* in_pIndices, int in_count) = 0;
		virtual void DrawSphere(const csl::math::Matrix34& in_transform, float in_radius, const csl::ut::Color8& in_color) = 0;
		virtual void DrawCapsule(const csl::math::Matrix34& in_transform, float in_radius, float in_height, const csl::ut::Color8& in_color) = 0;
		virtual void DrawAABB(const csl::math::Vector3& in_min, const csl::math::Vector3& in_max, const csl::ut::Color8& in_color) = 0;
		virtual void DrawOBB(const csl::math::Matrix34& in_transform, const csl::math::Vector3& in_size, const csl::ut::Color8& in_color) = 0;
		virtual void DrawCylinder(const csl::math::Matrix34& in_transform, float in_radius, float in_height, const csl::ut::Color8& in_color) = 0;
		virtual void DrawCircle(const csl::math::Matrix34& in_transform, float in_radius, const csl::ut::Color8& in_color) = 0;
		virtual void DrawPlane(const csl::math::Matrix34& in_transform, float in_width, float in_height, const csl::ut::Color8& in_color) = 0;
		virtual void SetWireframeMode(bool in_enable) = 0;
		virtual void SetZTestEnable(bool in_enable) = 0;
		virtual void SetZWriteEnable(bool in_enable) = 0;
	};
}