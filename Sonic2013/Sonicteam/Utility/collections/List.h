#pragma once

namespace csl::ut
{
	struct List
	{
		struct Node
		{
			void* pFirst{};
			void* pLast{};
		};

		Node Root{};
		ushort Length{};
		ushort NodeOffset{};
	};

	inline static void SetFirstObject(List* in_pList, void* in_pObj)
	{
		auto* pOtherNode = reinterpret_cast<List::Node*>(reinterpret_cast<char*>(in_pObj) + in_pList->m_NodeOffset);
		pOtherNode->pFirst = nullptr;
		pOtherNode->pLast = nullptr;

		in_pList->Root.pFirst = in_pObj;
		in_pList->Root.pLast = in_pObj;

		++in_pList->Length;
	}

	inline static void List_Init(List* in_pList, ushort in_nodeOffset)
	{
		in_pList->Root.pFirst = nullptr;
		in_pList->Root.pLast = nullptr;

		in_pList->Length = 0;
		in_pList->NodeOffset = in_nodeOffset;
	}

	inline static void List_Append(List* in_pList, void* in_pObj)
	{
		if (!in_pList->Root.pFirst)
		{
			SetFirstObject(in_pList, in_pObj);
			return;
		}

		void* prevObj = in_pList->Root.pLast;
		int nodeOffset = nodeOffset = in_pList->NodeOffset;
		++in_pList->Length;

		auto* pOtherNode = reinterpret_cast<List::Node*>(reinterpret_cast<char*>(in_pObj) + nodeOffset);
		pOtherNode->pLast = nullptr;
		pOtherNode->pFirst = prevObj;
		reinterpret_cast<List::Node*>(reinterpret_cast<char*>(prevObj) + nodeOffset)->pLast = in_pObj;
		in_pList->Root.m_pLast = in_pObj;
	}

	inline static void List_Prepend(List* in_pList, void* in_pObj)
	{
		if (!in_pList->Root.pFirst)
		{
			SetFirstObject(in_pList, in_pObj);
			return;
		}

		void* firstObj = in_pList->Root.pFirst;
		int nodeOffset = nodeOffset = in_pList->NodeOffset;
		++in_pList->Length;

		auto* pOtherNode = reinterpret_cast<List::Node*>(reinterpret_cast<char*>(in_pObj) + nodeOffset);
		pOtherNode->pFirst = nullptr;
		pOtherNode->pLast = firstObj;

		reinterpret_cast<List::Node*>(reinterpret_cast<char*>(firstObj) + nodeOffset)->pFirst = in_pObj;
		in_pList->Root.pFirst = in_pObj;
	}

	inline static void* List_GetNext(const List* in_pList, const void* in_pObj)
	{
		if (in_pObj)
		{
			return reinterpret_cast<const List*>(reinterpret_cast<const char*>(in_pObj) + in_pList->NodeOffset)->Root.pLast;
		}
		else
			return in_pList->Root.pFirst;
	}

	inline static void* List_GetPrev(const List* in_pList, const void* in_pObj)
	{
		if (in_pObj)
		{
			return reinterpret_cast<const List*>(reinterpret_cast<const char*>(in_pObj) + in_pList->NodeOffset)->Root.pFirst;
		}
		else
			return in_pList->Root.pLast;
	}

	inline static void* List_GetNth(const List* in_pList, ushort in_n)
	{
		int counter = 0;
		for (auto* it = List_GetNext(in_pList, nullptr); it; it = List_GetNext(in_pList, it))
		{
			if (counter == in_n)
				return it;

			counter++;
		}
		return nullptr;
	}
}