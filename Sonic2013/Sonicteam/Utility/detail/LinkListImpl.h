#pragma once

namespace csl::ut
{
	class LinkListNode
	{
	public:
		LinkListNode* pPrev{};
		LinkListNode* pNext{};
	};

	namespace detail
	{
		class LinkListImpl
		{
		public:
			struct iterator
			{
				LinkListNode* pCurNode{};
				size_t NodeOffset{};
			};

		protected:
			size_t m_Count;
			size_t m_NodeOffset;
			LinkListNode* m_pEnd{ reinterpret_cast<LinkListNode*>(&m_pEnd) };
			LinkListNode* m_pRoot{ reinterpret_cast<LinkListNode*>(&m_pEnd) };

			void Initialize()
			{
				m_Count = 0;
				m_pEnd = reinterpret_cast<LinkListNode*>(m_pEnd);
				m_pRoot = reinterpret_cast<LinkListNode*>(m_pEnd);
			}

			LinkListImpl()
			{
				Initialize();
			}

			void insert(iterator in_iter, LinkListNode* in_pNode)
			{
				LinkListNode* oldNext;

				++m_Count;
				oldNext = in_iter.pCurNode->pNext;
				in_pNode->pPrev = iter.pCurNode;
				in_pNode->pNext = oldNext;
				iter.pCurNode->pNext = in_pNode;
				oldNext->pPrev = in_pNode;
			}

			LinkListNode* erase(LinkListNode* in_pNode)
			{
				LinkListNode* pResult = in_pNode->pPrev;
				m_Count--;
				in_pNode->pPrev->pNext = in_pNode->pNext;
				in_pNode->pNext->pPrev = in_pNode->pPrev;
				in_pNode->pNext = nullptr;
				in_pNode->pPrev = nullptr;
				return pResult;
			}
		};
	}
}