#pragma once

namespace std::dummy
{
	template<typename T>
	class vector
	{
	protected:
		T* first{};
		T* last{};
		T* capacityLast{};
		void* pad{};

	public:
		T* begin() const
		{
			return first;
		}

		T* end() const
		{
			return last;
		}

		size_t size() const
		{
			return (reinterpret_cast<const size_t>(last) - reinterpret_cast<const size_t>(first)) / sizeof(T);
		}

		size_t capacity() const
		{
			return (reinterpret_cast<const size_t>(capacityLast) - reinterpret_cast<const size_t>(first)) / sizeof(T);
		}
	};
}