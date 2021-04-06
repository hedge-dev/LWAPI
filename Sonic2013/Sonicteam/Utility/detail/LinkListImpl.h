#pragma once

namespace csl::ut
{
	class LinkListNode
	{
	public:
		LinkListNode* m_pPrev{};
		LinkListNode* m_pNext{};
	};

	namespace detail
	{
		class LinkListImpl
		{
		public:
			struct iterator
			{
				LinkListNode* m_pCurNode{};
				size_t m_NodeOffset{};
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

			void insert(iterator iter, LinkListNode* pNode)
			{
				LinkListNode* oldNext;

				++m_Count;
				oldNext = iter.m_pCurNode->m_pNext;
				pNode->m_pPrev = iter.m_pCurNode;
				pNode->m_pNext = oldNext;
				iter.m_pCurNode->m_pNext = pNode;
				oldNext->m_pPrev = pNode;
			}

			LinkListNode* erase(LinkListNode* pNode)
			{
				LinkListNode* pResult = pNode->m_pPrev;
				m_Count--;
				pNode->m_pPrev->m_pNext = pNode->m_pNext;
				pNode->m_pNext->m_pPrev = pNode->m_pPrev;
				pNode->m_pNext = nullptr;
				pNode->m_pPrev = nullptr;
				return pResult;
			}
		};
	}
}