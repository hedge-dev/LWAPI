#pragma once

namespace gindows::device
{
	class Font : public RenderBase
	{
	public:
		Font(RenderState* pRenderState) : RenderBase(pRenderState)
		{
			
		}
		
		[[nodiscard]] virtual csl::ut::Size2<int> GetSize() const = 0;
	};
}