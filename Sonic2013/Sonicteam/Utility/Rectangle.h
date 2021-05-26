#pragma once

namespace csl::ut
{
	template<typename T>
	struct Rectangle2
	{
		T x;
		T y;
		T width;
		T height;

	public:
		T GetLeft() const
		{
			return x;
		}

		T GetTop() const
		{
			return y;
		}

		T GetRight() const
		{
			return x + width;
		}

		T GetBottom() const
		{
			return y + height;
		}

		T GetWidth() const
		{
			return width;
		}

		T GetHeight() const
		{
			return height;
		}
	};
}