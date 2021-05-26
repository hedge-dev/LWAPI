#pragma once

namespace csl::ut
{
	template<size_t Len>
	class FixedString
	{
		char m_Buffer[Len];

	public:
		void operator=(const char* pStr)
		{
			strcpy_s(m_Buffer, Len, pStr);
		}
		
		const char* c_str() const
		{
			return m_Buffer;
		}

		operator const char*() const
		{
			return m_Buffer;
		}
	};
}