#pragma once

namespace app
{
	template <typename T, const size_t Bsz, class TAllocator>
	class TInplaceArray : public TArray<T, TAllocator>
	{
	protected:
		char m_reserved[sizeof(T) * Bsz]{};

	public:
		constexpr TInplaceArray(uint in_length) : TArray<T, TAllocator>()
		{
			this->m_Capacity = Bsz;
			this->m_Capacity |= csl::ut::SIGN_BIT;
			this->m_Length = in_length;
			this->m_pBuffer = (T*)m_reserved;
		}

		void push_back_unchecked(const T& in_rItem)
		{
			this->m_Length++;
			this->m_pBuffer[this->m_Length - 1] = in_rItem;
		}
	};
}