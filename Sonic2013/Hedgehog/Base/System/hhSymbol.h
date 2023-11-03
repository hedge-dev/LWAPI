#pragma once

namespace hh::base
{
	struct SSymbolNode
	{
		SSymbolNode* pPrevNode{};
		SSymbolNode* pNextNode{};
		size_t Hash{};
		char Buffer[0x10000]{};

		[[nodiscard]] const char* c_str() const
		{
			return Buffer;
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
		SSymbolNode* pNode{};

		CStringSymbol(const char* in_pStr) : pNode(MakeStringSymbol(in_pStr))
		{

		}

		CStringSymbol(const CSharedString& in_rStr) : pNode(MakeStringSymbol(in_rStr.c_str()))
		{

		}

		[[nodiscard]] const char* c_str() const
		{
			return pNode->c_str();
		}

		[[nodiscard]] CSharedString DebugGetKey() const
		{
			return c_str();
		}
	};
}