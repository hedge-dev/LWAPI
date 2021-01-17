#pragma once

namespace gindows::device
{
	class DeviceMouse : RenderBase
	{
	public:
		DeviceMouse(RenderState* pRenderState) : RenderBase(pRenderState)
		{
			
		}

		virtual void Draw() = 0;
		virtual void SetLocation(const csl::ut::Point2<int>& location) = 0;
		[[nodiscard]] virtual csl::ut::Point2<int> GetLocation() const = 0;
		virtual void SetCursorType(MouseCursorType type) = 0;
	};
}