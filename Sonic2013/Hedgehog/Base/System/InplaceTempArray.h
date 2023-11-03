#pragma once

namespace app::ut
{
	template <typename T, const size_t Bsz>
	class InplaceTempArray : public csl::ut::InplaceMoveArray<T, Bsz>
	{
	public:
		constexpr InplaceTempArray() : csl::ut::InplaceMoveArray<T, Bsz>(fnd::GetTempAllocator())
		{

		}
	};
}