#pragma once

namespace csl::ut
{
	template <typename T, const size_t Bsz>
	class InplaceObjectMoveArray : public ObjectMoveArray<T>
	{
	protected:
		char m_reserved[sizeof(T) * Bsz]{};

	public:
		constexpr InplaceObjectMoveArray(size_t in_length) : ObjectMoveArray<T>((void*)m_reserved, in_length, Bsz, nullptr, false)
		{

		}

		constexpr InplaceObjectMoveArray(fnd::IAllocator* in_pAllocator) : ObjectMoveArray<T>(in_pAllocator)
		{
			this->Capacity = Bsz;
			this->Capacity |= 1u << ((sizeof(size_t) * CHAR_BIT) - 1);
			this->pBuffer = (T*)m_reserved;
		}
	};

	template <typename T, const size_t Bsz>
	class InplaceObjectMoveArrayAligned16 : public ObjectMoveArray<T>
	{
	protected:
		alignas(16) char m_reserved[sizeof(T) * Bsz];

	public:
		constexpr InplaceObjectMoveArrayAligned16() : ObjectMoveArray<T>(&m_reserved, Bsz, 8, nullptr, false)
		{

		}
	};
}