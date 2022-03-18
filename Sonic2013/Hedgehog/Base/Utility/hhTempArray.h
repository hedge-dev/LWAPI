#pragma once

namespace app::ut
{
	template<typename T>
	class TempArray : public csl::ut::MoveArray<T>
	{
	public:
		TempArray() : csl::ut::MoveArray<T>(fnd::GetTempAllocator())
		{
			
		}
	};
}