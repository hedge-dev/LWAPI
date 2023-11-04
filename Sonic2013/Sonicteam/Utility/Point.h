#pragma once

namespace csl::ut
{
	template<typename T>
	struct Point2
	{
		T X;
		T Y;

	public:
		T GetX() const
		{
			return X;
		}

		T GetY() const
		{
			return Y;
		}

		Point2<T> operator +(const Point2<T>& in_rPoint2) const
		{
			return Point2<T> { GetX() + in_rPoint2.GetX(), GetY() + in_rPoint2.GetY() };
		}
		
		Point2<T> operator -(const Point2<T>& in_rPoint2) const
		{
			return Point2<T> { GetX() - in_rPoint2.GetX(), GetY() - in_rPoint2.GetY() };
		}
	};
}