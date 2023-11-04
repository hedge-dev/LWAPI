#pragma once

namespace csl::ut
{
	template<size_t Len>
	class FixedString
	{
		char m_Buffer[Len]{};

	public:
		void set(const char* in_pStr)
		{
			csl::fnd::StrLcpy(m_Buffer, in_pStr, Len);
		}

		void setf(const char* in_pFormat, ...)
		{
			va_list args;
			va_start(args, in_pFormat);

			csl::fnd::VSnprintf(m_Buffer, Len, in_pFormat, args);

			va_end(args);
		}

		FixedString()
		{
			set("");
		}

		FixedString(const char* in_pStr)
		{
			set(in_pStr);
		}
		
		const char* c_str() const
		{
			return m_Buffer;
		}

		void operator=(const char* in_pStr)
		{
			set(in_pStr);
		}
		
		operator const char* () const
		{
			return m_Buffer;
		}

		operator char* ()
		{
			return m_Buffer;
		}
		
		friend bool operator==(const FixedString<Len>& in_rLhs, const char* in_pRhs)
		{
			return !strcmp(in_rLhs.c_str(), in_pRhs);
		}

		friend bool operator!=(const FixedString<Len>& lhs, const char* in_pRhs)
		{
			return strcmp(in_rLhs.c_str(), in_pRhs);
		}

		friend bool operator==(const char* in_pLhs, const FixedString<Len>& in_rLhs)
		{
			return !strcmp(in_pLhs, in_rLhs.c_str());
		}

		friend bool operator!=(const char* in_pLhs, const FixedString<Len>& in_rLhs)
		{
			return strcmp(in_pLhs, in_rLhs.c_str());
		}
	};
}