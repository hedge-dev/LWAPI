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
		
		void assign(fnd::IAllocator* pAllocator, const char* pStr)
		{
			if (c_str() == pStr)
				return;

			if (isFree() && m_pAllocator)
				m_pAllocator->Free(reinterpret_cast<char*>(reinterpret_cast<size_t>(m_pStr) - 1));

			m_pAllocator = pAllocator;
			if (!pStr)
			{
				m_pStr = nullptr;
				return;
			}

			size_t bufSize = strlen(pStr) + 1;
			char* pBuffer = reinterpret_cast<char*>(m_pAllocator->Alloc(bufSize, 16));
			for (size_t i = 0; pStr[i]; i++)
				pBuffer[i] = pStr[i];

			pBuffer[bufSize - 1] = '\0';
			m_pStr = pBuffer + 1;
		}
		
	public:
		VariableString(const char* pStr, csl::fnd::IAllocator* pAlloc)
		{
			assign(pAlloc, pStr);
		}

		VariableString(csl::fnd::IAllocator* pAlloc)
		{
			m_pAllocator = pAlloc;
		}
		
		~VariableString()
		{
			assign(nullptr, nullptr);
		}

		csl::fnd::IAllocator* GetAllocator() const
		{
			return m_pAllocator;
		}
		
		void Set(const char* pStr, csl::fnd::IAllocator* pAlloc)
		{
			assign(pAlloc, pStr);
		}

		void Set(const char* pStr)
		{
			Set(pStr, GetAllocator());
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

		bool Compare(const char* pStr) const
		{
			return strcmp(c_str(), pStr);
		}
		
		operator const char*() const
		{
			return c_str();
		}

		operator char* ()
		{
			return c_str();
		}
		
		VariableString& operator=(const char* pStr)
		{
			Set(pStr);
			return *this;
		}

		friend bool operator==(const VariableString& lhs, const VariableString& rhs)
		{
			return lhs.Compare(rhs.c_str());
		}

		friend bool operator==(const VariableString& lhs, const char* rhs)
		{
			return lhs.Compare(rhs);
		}
	};
}