#pragma once

namespace csl::ut
{
	template <typename T, const size_t Bsz>
	class InplaceObjectMoveArray : public ObjectMoveArray<T>
	{
	protected:
		char reserved[sizeof(T) * Bsz]{};

	public:
		constexpr InplaceObjectMoveArray(fnd::IAllocator* allocator_) : ObjectMoveArray<T>(allocator_)
		{
			this->m_capacity = Bsz;
			this->m_capacity |= 1u << ((sizeof(size_t) * CHAR_BIT) - 1);
			this->p_buffer = (T*)reserved;
		}
	};

	template <typename T, const size_t Bsz>
	class InplaceObjectMoveArrayAligned16 : public ObjectMoveArray<T>
	{
	protected:
		alignas(16) char reserved[sizeof(T) * Bsz]{};

	public:
		constexpr InplaceObjectMoveArrayAligned16(fnd::IAllocator* allocator_) : ObjectMoveArray<T>(allocator_)
		{
			this->m_capacity = Bsz;
			this->m_capacity |= 1u << ((sizeof(size_t) * CHAR_BIT) - 1);
			this->p_buffer = (T*)reserved;
		}
	};
}