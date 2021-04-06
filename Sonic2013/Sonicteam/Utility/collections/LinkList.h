#pragma once

namespace csl::ut
{
	template<class T>
	class LinkList : detail::LinkListImpl
	{
	public:
		template<class T>
		class iterator
		{
			friend LinkList;
			
		protected:
			const LinkListNode* m_pCurNode{};
			size_t m_NodeOffset;

		public:
			iterator(const LinkListNode* pNode, size_t nodeOffset) : m_pCurNode(pNode), m_NodeOffset(nodeOffset)
			{
				
			}
			
			T* operator->()
			{
				return reinterpret_cast<T*>(reinterpret_cast<size_t>(m_pCurNode) - m_NodeOffset);
			}

			T* operator*()
			{
				return operator->();
			}
			
			friend bool operator==(const iterator& lhs, const iterator& rhs)
			{
				return lhs.m_pCurNode == rhs.m_pCurNode;
			}

			friend bool operator!=(const iterator& lhs, const iterator& rhs)
			{
				return lhs.m_pCurNode != rhs.m_pCurNode;
			}

			iterator& operator++()
			{
				m_pCurNode = m_pCurNode->m_pNext;
				return *this;
			}

			iterator& operator--()
			{
				m_pCurNode = m_pCurNode->m_pPrev;
				return *this;
			}
		};
		
		LinkList()
		{
			
		}

		LinkList(size_t nodeOffset)
		{
			m_NodeOffset = nodeOffset;
		}

		LinkList(LinkListNode(T::*nodeOffset))
		{
			m_NodeOffset = reinterpret_cast<size_t>(*reinterpret_cast<size_t**>(&nodeOffset));
		}

	private:
		LinkListNode* GetNode(T* pItem)
		{
			return reinterpret_cast<LinkListNode*>(reinterpret_cast<size_t>(pItem) + m_NodeOffset);
		}
		
	public:
		void push_back(T* pItem)
		{
			LinkListImpl::insert({ m_pEnd, m_NodeOffset }, GetNode(pItem));
		}

		void erase(T* pItem)
		{
			LinkListImpl::erase(GetNode(pItem));
		}

		void erase(iterator<T> start, iterator<T> finish)
		{
			LinkListNode* pCurNode = start.m_pCurNode;
			while (pCurNode != finish.m_pCurNode)
			{
				pCurNode = LinkListImpl::erase(pCurNode);
			}
		}

		void clear()
		{
			erase(begin(), end());
		}
		
		[[nodiscard]] iterator<T> begin() const { return iterator<T>(m_pEnd, m_NodeOffset); }
		[[nodiscard]] iterator<T> end() const
		{
			return iterator<T>(const_cast<LinkListNode*>(reinterpret_cast<const LinkListNode*>(&m_pEnd)), m_NodeOffset);
		}

		[[nodiscard]] size_t size() const { return m_Count; }
	};
}