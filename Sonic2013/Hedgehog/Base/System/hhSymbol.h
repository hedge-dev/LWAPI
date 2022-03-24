#pragma once

namespace hh::base
{
	struct SSymbolNode
	{
		SSymbolNode* m_pPrevNode{};
		SSymbolNode* m_pNextNode{};
		size_t m_Hash{};
		char m_Buffer[0x10000]{};

		[[nodiscard]] const char* c_str() const
		{
			return m_Buffer;
		}
	};

	inline static FUNCTION_PTR(SSymbolNode*, __cdecl, fpMakeStringSymbol, ASLR(0x00C22820), const char*);

	inline static SSymbolNode* MakeStringSymbol(const char* in_pStr)
	{
		return fpMakeStringSymbol(in_pStr);
	}

	class CStringSymbol
	{
	public:
		SSymbolNode* m_pNode{};

		CStringSymbol(const char* in_pStr) : m_pNode(MakeStringSymbol(in_pStr))
		{

		}

		CStringSymbol(const CSharedString& in_str) : m_pNode(MakeStringSymbol(in_str.c_str()))
		{

		}

		[[nodiscard]] const char* c_str() const
		{
			return m_pNode->c_str();
		}

		[[nodiscard]] CSharedString DebugGetKey() const
		{
			return c_str();
		}
	};
}