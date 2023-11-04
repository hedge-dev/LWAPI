#pragma once

namespace csl::ut
{
	class VariableString
	{
	protected:
		inline static const char* ms_Empty = "";
		
		char* m_pStr{};
		fnd::IAllocator* m_pAllocator{};

		inline bool isFree() const
		{
			return reinterpret_cast<size_t>(m_pStr) & 1;
		}
		
		void assign(fnd::IAllocator* in_pAllocator, const char* in_pStr)
		{
			if (c_str() == in_pStr)
				return;

			if (isFree() && m_pAllocator)
				m_pAllocator->Free(reinterpret_cast<char*>(reinterpret_cast<size_t>(m_pStr) - 1));

			m_pAllocator = in_pAllocator;
			if (!pStr)
			{
				m_pStr = nullptr;
				return;
			}

			size_t bufSize = strlen(in_pStr) + 1;
			char* pBuffer = reinterpret_cast<char*>(m_pAllocator->Alloc(bufSize, 16));
			for (size_t i = 0; in_pStr[i]; i++)
				pBuffer[i] = in_pStr[i];

			pBuffer[bufSize - 1] = '\0';
			m_pStr = pBuffer + 1;
		}
		
	public:
		VariableString(const char* in_pStr, csl::fnd::IAllocator* in_pAllocator)
		{
			assign(in_pAllocator, in_pStr);
		}

		VariableString(csl::fnd::IAllocator* in_pAllocator)
		{
			m_pAllocator = in_pAllocator;
		}
		
		~VariableString()
		{
			assign(nullptr, nullptr);
		}

		csl::fnd::IAllocator* GetAllocator() const
		{
			return m_pAllocator;
		}
		
		void Set(const char* in_pStr, csl::fnd::IAllocator* in_pAllocator)
		{
			assign(in_pAllocator, in_pStr);
		}

		void Set(const char* in_pStr)
		{
			Set(in_pStr, GetAllocator());
		}
		
		const char* c_str() const
		{
			if (m_pStr)
				return reinterpret_cast<const char*>(reinterpret_cast<size_t>(m_pStr) & ~1);

			return ms_Empty;
		}

		char* c_str()
		{
			if (m_pStr)
				return reinterpret_cast<char*>(reinterpret_cast<size_t>(m_pStr) & ~1);

			return m_pStr;
		}

		bool Compare(const char* in_pStr) const
		{
			return strcmp(c_str(), in_pStr);
		}
		
		operator const char*() const
		{
			return c_str();
		}

		operator char* ()
		{
			return c_str();
		}
		
		VariableString& operator=(const char* in_pStr)
		{
			Set(in_pStr);
			return *this;
		}

		friend bool operator==(const VariableString& in_rLhs, const VariableString& in_rRhs)
		{
			return in_rLhs.Compare(in_rRhs.c_str());
		}

		friend bool operator==(const VariableString& in_rLhs, const char* in_pRhs)
		{
			return in_rLhs.Compare(in_pRhs);
		}
	};
}