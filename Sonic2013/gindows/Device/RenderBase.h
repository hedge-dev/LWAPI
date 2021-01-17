#pragma once

namespace gindows::device
{
	class RenderBase : public Object
	{
	protected:
		RenderState* m_pRenderState{};

	public:
		RenderBase(RenderState* pRenderState) : m_pRenderState(pRenderState)
		{
			
		}
	};
}