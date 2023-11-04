#pragma once

namespace gindows::device
{
	class Mouse : public Object
	{
	public:
		Mouse()
		{
			
		}

		virtual void Draw() = 0;
		virtual void SetLocation(const csl::ut::Point2<int>& in_rLocation) = 0;
		[[nodiscard]] virtual csl::ut::Point2<int> GetLocation() const = 0;
		virtual void SetCursorType(MouseCursorType in_type) = 0;
	};
}