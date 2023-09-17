#pragma once

namespace csl::ut
{
	template<typename T>
	class Array
	{
	public:
		T* p_buffer{};
		size_t m_length{};
		size_t m_capacity{};

		T* get(size_t i) const
		{
			if (!this->p_buffer)
				return nullptr;

			return &this->p_buffer[i];
		}

		[[nodiscard]] T* begin() const { return get(0); }

		[[nodiscard]] T* end() const { return get(this->m_length); }

		[[nodiscard]] T front() const { return *get(0); }
		
		[[nodiscard]] size_t size() const
		{
			return this->m_length;
		}

		[[nodiscard]] size_t capacity() const
		{
			return this->m_capacity & ~csl::ut::SIGN_BIT;
		}

		bool empty() const
		{
			return this->m_length == 0;
		}
	};
}