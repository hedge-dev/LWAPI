#pragma once

namespace csl::ut
{
	template <typename T>
	class ObjectMoveArray : public MoveArray<T>
	{
	public:
		ObjectMoveArray(fnd::IAllocator* allocator_) : MoveArray<T>(allocator_)
		{
			
		}
	};
}