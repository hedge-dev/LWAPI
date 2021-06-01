#pragma once

namespace csl::ut
{
	template<class T>
	class LinkList : public detail::LinkListImpl, NonCopyable
	{
	public:
		template<class T>
		class iterator
		{
			friend LinkList;
			
		protected:
			LinkListNode* m_pCurNode{};
			size_t m_NodeOffset;

		public:
			iterator(LinkListNode* pNode, size_t nodeOffset) : m_pCurNode(pNode), m_NodeOffset(nodeOffset)
			{
				
			}
			
			T* operator->() const
			{
				return reinterpret_cast<T*>(reinterpret_cast<size_t>(m_pCurNode) - m_NodeOffset);
			}

			T& operator*() const
			{
				return *operator->();
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
				m_pCurNode = m_pCurNode->m_pPrev;
				return *this;
			}

			iterator& operator--()
			{
				m_pCurNode = m_pCurNode->m_pNext;
				return *this;
			}

			operator T* () const
			{
				return operator->();
			}
		};

		template<class T>
		class const_iterator
		{
			friend LinkList;

		protected:
			const LinkListNode* m_pCurNode{};
			size_t m_NodeOffset;

		public:
			const_iterator(const LinkListNode* pNode, size_t nodeOffset) : m_pCurNode(pNode), m_NodeOffset(nodeOffset)
			{

			}

			T* operator->() const
			{
				return reinterpret_cast<T*>(reinterpret_cast<size_t>(m_pCurNode) - m_NodeOffset);
			}

			T& operator*() const
			{
				return *operator->();
			}

			friend bool operator==(const const_iterator& lhs, const const_iterator& rhs)
			{
				return lhs.m_pCurNode == rhs.m_pCurNode;
			}

			friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs)
			{
				return lhs.m_pCurNode != rhs.m_pCurNode;
			}

			const_iterator& operator++()
			{
				m_pCurNode = m_pCurNode->m_pPrev;
				return *this;
			}

			const_iterator& operator--()
			{
				m_pCurNode = m_pCurNode->m_pNext;
				return *this;
			}

			operator T*() const
			{
				return operator->();
			}
		};

		void init(LinkListNode(T::* nodeOffset))
		{
			m_NodeOffset = reinterpret_cast<size_t>(*reinterpret_cast<size_t**>(&nodeOffset));
		}
		
		LinkList()
		{
			
		}

		LinkList(size_t nodeOffset)
		{
			m_NodeOffset = nodeOffset;
		}

		LinkList(LinkListNode(T::*nodeOffset))
		{
			init(nodeOffset);
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

		~LinkList()
		{
			clear();
		}
		
		[[nodiscard]] iterator<T> begin() { return iterator<T>(m_pEnd, m_NodeOffset); }
		[[nodiscard]] iterator<T> end()
		{
			return iterator<T>(reinterpret_cast<LinkListNode*>(&m_pEnd), m_NodeOffset);
		}
		[[nodiscard]] const_iterator<T> begin() const { return const_iterator<T>(m_pEnd, m_NodeOffset); }
		[[nodiscard]] const_iterator<T> end() const
		{
			return const_iterator<T>(const_cast<LinkListNode*>(reinterpret_cast<const LinkListNode*>(&m_pEnd)), m_NodeOffset);
		}
		
		[[nodiscard]] size_t size() const { return m_Count; }

		[[nodiscard]] T* front() const
		{
			if (!size())
				return nullptr;
			
			return begin();
		}
	};
}