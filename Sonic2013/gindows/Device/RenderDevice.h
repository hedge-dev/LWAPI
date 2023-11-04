#pragma once

namespace gindows::device
{
	class RenderDevice : Object
	{
		virtual void SetScissorRect(const csl::ut::Rectangle2<int>* in_pRect) = 0;
		virtual void SetScissor(bool in_enabled) = 0;
		virtual void DrawPrimitive(PrimType in_type, const float* in_pA2, const csl::ut::Color8* in_pA3, int in_a4) = 0;
		virtual void DrawPrimitive(PrimType in_type , const float* in_pA2, const csl::ut::Color8* in_pA3, const void* in_pA4, const float* in_pA5, int in_a6) = 0;
		virtual void DrawPrimitive(PrimType in_type, const PrimitiveVertex* in_pA2, int in_a3) = 0;
		virtual void DrawPrimitive(PrimType in_type, const PrimitiveVertex*, const void*, int) = 0;
	};
}