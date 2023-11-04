#pragma once

namespace csl::ut
{
	template<typename T>
	class Array
	{
	public:
		T* pBuffer{};
		size_t Length{};
		size_t Capacity{};

		T* get(size_t i) const
		{
			if (!this->pBuffer)
				return nullptr;

			return &this->pBuffer[i];
		}

		[[nodiscard]] T* begin() const { return get(0); }

		[[nodiscard]] T* end() const { return get(this->Length); }

		[[nodiscard]] T front() const { return *get(0); }
		
		[[nodiscard]] size_t size() const
		{
			return this->Length;
		}

		[[nodiscard]] size_t capacity() const
		{
			return this->Capacity & ~csl::ut::SIGN_BIT;
		}

		bool empty() const
		{
			return this->Length == 0;
		}
	};
}