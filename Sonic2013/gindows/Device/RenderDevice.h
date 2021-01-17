#pragma once

namespace gindows::device
{
	class RenderDevice : Object
	{
		virtual void SetScissorRect(const csl::ut::Rectangle2<int>* rect) = 0;
		virtual void SetScissor(bool enabled) = 0;
		virtual void DrawPrimitive(PrimType type, const float* a2, const csl::ut::Color8* a3, int a4) = 0;
		virtual void DrawPrimitive(PrimType type , const float* a2, const csl::ut::Color8* a3, const void* a4, const float* a5, int a6) = 0;
		virtual void DrawPrimitive(PrimType type, const PrimitiveVertex* a2, int a3) = 0;
		virtual void DrawPrimitive(PrimType type, const PrimitiveVertex*, const void*, int) = 0;
	};
}