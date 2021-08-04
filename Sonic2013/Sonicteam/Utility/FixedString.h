#pragma once

namespace csl::ut
{
	template<size_t Len>
	class FixedString
	{
		char m_Buffer[Len]{};

	public:
		void set(const char* pStr)
		{
			csl::fnd::StrLcpy(m_Buffer, pStr, Len);
		}

		FixedString()
		{
			set("");
		}

		FixedString(const char* pStr)
		{
			set(pStr);
		}
		
		const char* c_str() const
		{
			return m_Buffer;
		}

		void operator=(const char* pStr)
		{
			set(pStr);
		}
		
		operator const char* () const
		{
			return m_Buffer;
		}

		operator char* ()
		{
			return m_Buffer;
		}
		
		friend bool operator==(const FixedString<Len>& lhs, const char* rhs)
		{
			return !strcmp(lhs.c_str(), rhs);
		}

		friend bool operator!=(const FixedString<Len>& lhs, const char* rhs)
		{
			return strcmp(lhs.c_str(), rhs);
		}

		friend bool operator==(const char* lhs, const FixedString<Len>& rhs)
		{
			return !strcmp(lhs, rhs.c_str());
		}

		friend bool operator!=(const char* lhs, const FixedString<Len>& rhs)
		{
			return strcmp(lhs, rhs.c_str());
		}
	};
}