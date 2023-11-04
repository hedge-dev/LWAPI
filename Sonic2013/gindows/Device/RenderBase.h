#pragma once

namespace gindows::device
{
	class RenderBase : public Object
	{
	protected:
		RenderState* m_pRenderState{};

	public:
		RenderBase(RenderState* in_pRenderState) : m_pRenderState(in_pRenderState)
		{
			
		}
	};
}