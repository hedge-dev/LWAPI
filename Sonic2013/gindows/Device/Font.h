#pragma once

namespace gindows::device
{
	class Font : public RenderBase
	{
	public:
		Font(RenderState* pRenderState) : RenderBase(pRenderState)
		{
			
		}
		
		virtual csl::ut::Size2<int> GetSize() = 0;
	};
}