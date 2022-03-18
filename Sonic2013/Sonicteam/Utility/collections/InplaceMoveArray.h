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

	template <typename T, const size_t Bsz>
	class alignas(16) InplaceMoveArrayAligned16 : public MoveArray<T>
	{
	protected:
		char alignas(16) reserved[sizeof(T) * Bsz]{};

	public:
		constexpr InplaceMoveArrayAligned16(fnd::IAllocator* allocator_) : MoveArray<T>(allocator_)
		{
			this->m_capacity = Bsz;
			this->m_capacity |= SIGN_BIT;
			this->p_buffer = (T*)reserved;
		}
	};
}