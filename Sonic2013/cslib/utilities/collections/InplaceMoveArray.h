#pragma once

namespace csl::ut
{
	template <typename T, const size_t Bsz>
	class InplaceMoveArray : public MoveArray<T>
	{
	protected:
		char reserved[sizeof(T) * Bsz]{};

	public:
		constexpr InplaceMoveArray(fnd::IAllocator* allocator_) : MoveArray<T>(allocator_)
		{
			this->maxLength = Bsz;
			this->maxLength |= 1u << ((sizeof(size_t) * CHAR_BIT) - 1);
			this->buffer = (T*)reserved;
		}
	};
}