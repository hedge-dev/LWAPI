#pragma once

namespace csl::ut
{
	template <typename T, const size_t Bsz>
	class InplaceMoveArray : public MoveArray<T>
	{
	protected:
		char m_reserved[sizeof(T) * Bsz]{};

	public:
		constexpr InplaceMoveArray(fnd::IAllocator* in_pAllocator) : MoveArray<T>(in_pAllocator)
		{
			this->Capacity = Bsz;
			this->Capacity |= SIGN_BIT;
			this->pBuffer = (T*)m_reserved;
		}
	};

	template <typename T, const size_t Bsz>
	class alignas(16) InplaceMoveArrayAligned16 : public MoveArray<T>
	{
	protected:
		char alignas(16) reserved[sizeof(T) * Bsz]{};

	public:
		constexpr InplaceMoveArrayAligned16(fnd::IAllocator* in_pAllocator) : MoveArray<T>(in_pAllocator)
		{
			this->Capacity = Bsz;
			this->Capacity |= SIGN_BIT;
			this->pBuffer = (T*)reserved;
		}
	};
}