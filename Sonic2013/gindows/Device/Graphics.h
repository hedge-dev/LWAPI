#pragma once

namespace gindows::device
{
	class Graphics : public RenderBase
	{
	public:
		Graphics(RenderState* in_pRenderState) : RenderBase(in_pRenderState)
		{
			
		}

		virtual void DrawMouseCursor(const csl::ut::Point2<int>& in_rPoint, const csl::ut::Color8& in_rColor, MouseCursorType in_type) = 0;
		virtual void SetScreenBounds(const csl::ut::Rectangle2<int>& in_rBound) = 0;
		virtual void DrawIcon(const csl::ut::Point2<int>& in_rPoint, const csl::ut::Color8& in_rColor, IconKind in_icon) = 0;
		[[nodiscard]] virtual csl::ut::Size2<int> GetIconSize(IconKind in_kind) const = 0;
		virtual void DrawBorderFixed3D(const csl::ut::Rectangle2<int>& in_rRect, const csl::ut::Color8& in_rColor, int in_a3) = 0;
		virtual void DrawRectangle(const csl::ut::Rectangle2<int>& in_rRect, csl::ut::Color8& in_rColor) = 0;
		virtual void DrawRectangle(const csl::ut::Rectangle2<int>& in_rRect, csl::ut::Color8& in_rColor1, csl::ut::Color8& in_rColor2, csl::ut::Color8& in_rColor3, csl::ut::Color8& in_rColor4) = 0;
		virtual void DrawLine(const csl::ut::Point2<int>& in_From, const csl::ut::Point2<int>& in_rTo, const csl::ut::Color8& in_rColor) = 0;
		virtual csl::ut::Point2<int> DrawString(const Font* in_pFont, const csl::ut::Rectangle2<int>& in_rRect,
			const csl::ut::Point2<int>& in_rP1, const csl::ut::Point2<int>& in_rP2, const csl::ut::Color8& in_rColor, const char* in_pText) = 0;

		virtual void DrawPrimitive(PrimType in_type, const PrimitiveVertex* in_pA2, int in_a3)
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