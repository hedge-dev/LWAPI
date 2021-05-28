#pragma once

namespace gindows::device
{
	class Graphics : public RenderBase
	{
	public:
		Graphics(RenderState* pRenderState) : RenderBase(pRenderState)
		{
			
		}

		virtual void DrawMouseCursor(const csl::ut::Point2<int>& point, const csl::ut::Color8& color, MouseCursorType type) = 0;
		virtual void SetScreenBounds(const csl::ut::Rectangle2<int>& bound) = 0;
		virtual void DrawIcon(const csl::ut::Point2<int>& point, const csl::ut::Color8& color, IconKind icon) = 0;
		[[nodiscard]] virtual csl::ut::Size2<int> GetIconSize(IconKind kind) const = 0;
		virtual void DrawBorderFixed3D(const csl::ut::Rectangle2<int>& rect, const csl::ut::Color8& color, int a3) = 0;
		virtual void DrawRectangle(const csl::ut::Rectangle2<int>& rect, csl::ut::Color8& color) = 0;
		virtual void DrawRectangle(const csl::ut::Rectangle2<int>& rect, csl::ut::Color8& color1, csl::ut::Color8& color2, csl::ut::Color8& color3, csl::ut::Color8& color4) = 0;
		virtual void DrawLine(const csl::ut::Point2<int>& from, const csl::ut::Point2<int>& to, const csl::ut::Color8& color) = 0;
		virtual csl::ut::Point2<int> DrawString(const Font* font, const csl::ut::Rectangle2<int>& rect,
			const csl::ut::Point2<int>& p1, const csl::ut::Point2<int>& p2, const csl::ut::Color8& color, const char* text) = 0;

		virtual void DrawPrimitive(PrimType type, const PrimitiveVertex* a2, int a3)
		{
			
		}

		virtual void FlushVertex() = 0;
		virtual void BeginDraw()
		{
			
		}

		virtual void EndDraw()
		{
			
		}
	};
}