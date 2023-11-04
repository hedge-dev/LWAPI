#pragma once

namespace csl::ut
{
	template<typename T>
	struct Rectangle2
	{
		T X;
		T Y;
		T Width;
		T Height;

	public:
		T GetLeft() const
		{
			return X;
		}

		T GetTop() const
		{
			return Y;
		}

		T GetRight() const
		{
			return X + Width;
		}

		T GetBottom() const
		{
			return Y + Height;
		}

		T GetWidth() const
		{
			return Width;
		}

		T GetHeight() const
		{
			return Height;
		}
	};
}