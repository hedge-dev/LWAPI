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
			this->m_capacity = Bsz;
			this->m_capacity |= SIGN_BIT;
			this->p_buffer = (T*)reserved;
		}
	};
}