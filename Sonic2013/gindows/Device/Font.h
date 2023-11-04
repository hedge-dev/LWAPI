#pragma once

namespace gindows::device
{
	class Font : public RenderBase
	{
	public:
		Font(RenderState* in_pRenderState) : RenderBase(in_pRenderState)
		{
			
		}
		
		[[nodiscard]] virtual csl::ut::Size2<int> GetSize() const = 0;
	};
}