#pragma once

namespace csl::ut
{
	struct List
	{
		struct Node
		{
			void* m_pFirst{};
			void* m_pLast{};
		};

		Node m_Root{};
		ushort m_Length{};
		ushort m_NodeOffset{};
	};

	inline static void SetFirstObject(List* in_pList, void* in_pObj)
	{
		auto* pOtherNode = reinterpret_cast<List::Node*>(reinterpret_cast<char*>(in_pObj) + in_pList->m_NodeOffset);
		pOtherNode->m_pFirst = nullptr;
		pOtherNode->m_pLast = nullptr;

		in_pList->m_Root.m_pFirst = in_pObj;
		in_pList->m_Root.m_pLast = in_pObj;

		++in_pList->m_Length;
	}

	inline static void List_Init(List* in_pList, ushort in_nodeOffset)
	{
		in_pList->m_Root.m_pFirst = nullptr;
		in_pList->m_Root.m_pLast = nullptr;

		in_pList->m_Length = 0;
		in_pList->m_NodeOffset = in_nodeOffset;
	}

	inline static void List_Append(List* in_pList, void* in_pObj)
	{
		if (!in_pList->m_Root.m_pFirst)
		{
			SetFirstObject(in_pList, in_pObj);
			return;
		}

		void* prevObj = in_pList->m_Root.m_pLast;
		int nodeOffset = nodeOffset = in_pList->m_NodeOffset;
		++in_pList->m_Length;

		auto* pOtherNode = reinterpret_cast<List::Node*>(reinterpret_cast<char*>(in_pObj) + nodeOffset);
		pOtherNode->m_pLast = nullptr;
		pOtherNode->m_pFirst = prevObj;
		reinterpret_cast<List::Node*>(reinterpret_cast<char*>(prevObj) + nodeOffset)->m_pLast = in_pObj;
		in_pList->m_Root.m_pLast = in_pObj;
	}

	inline static void List_Prepend(List* in_pList, void* in_pObj)
	{
		if (!in_pList->m_Root.m_pFirst)
		{
			SetFirstObject(in_pList, in_pObj);
			return;
		}

		void* firstObj = in_pList->m_Root.m_pFirst;
		int nodeOffset = nodeOffset = in_pList->m_NodeOffset;
		++in_pList->m_Length;

		auto* pOtherNode = reinterpret_cast<List::Node*>(reinterpret_cast<char*>(in_pObj) + nodeOffset);
		pOtherNode->m_pFirst = nullptr;
		pOtherNode->m_pLast = firstObj;

		reinterpret_cast<List::Node*>(reinterpret_cast<char*>(firstObj) + nodeOffset)->m_pFirst = in_pObj;
		in_pList->m_Root.m_pFirst = in_pObj;
	}

	inline static void* List_GetNext(const List* in_pList, const void* in_pObj)
	{
		if (in_pObj)
		{
			return reinterpret_cast<const List*>(reinterpret_cast<const char*>(in_pObj) + in_pList->m_NodeOffset)->m_Root.m_pLast;
		}
		else
			return in_pList->m_Root.m_pFirst;
	}

	inline static void* List_GetPrev(const List* in_pList, const void* in_pObj)
	{
		if (in_pObj)
		{
			return reinterpret_cast<const List*>(reinterpret_cast<const char*>(in_pObj) + in_pList->m_NodeOffset)->m_Root.m_pFirst;
		}
		else
			return in_pList->m_Root.m_pLast;
	}

	inline static void* List_GetNth(const List* in_pList, ushort n)
	{
		int counter = 0;
		for (auto* it = List_GetNext(in_pList, nullptr); it; it = List_GetNext(in_pList, it))
		{
			if (counter == n)
				return it;

			counter++;
		}
		return nullptr;
	}
}