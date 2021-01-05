#pragma once

namespace csl::ut
{
	template <typename T>
	class ObjectMoveArray : public MoveArray<const T*>
	{
	public:
		ObjectMoveArray(fnd::IAllocator* allocator_) : MoveArray<const T*>(allocator_)
		{
			
		}
	};
}