#pragma once

namespace gindows::device
{
	class RenderState : Object
	{
		virtual void BeginDraw() = 0;
		virtual void EndDraw() = 0;
	};
}