#pragma once

namespace csl::ut
{
	template<typename T>
	struct Point2
	{
		T x;
		T y;

	public:
		T GetX() const
		{
			return x;
		}

		T GetY() const
		{
			return y;
		}

		Point2<T> operator +(const Point2<T>& point2) const
		{
			return Point2<T> { GetX() + point2.GetX(), GetY() + point2.GetY() };
		}
		
		Point2<T> operator -(const Point2<T>& point2) const
		{
			return Point2<T> { GetX() - point2.GetX(), GetY() - point2.GetY() };
		}
	};
}