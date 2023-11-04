#pragma once

namespace csl::ut
{
	template<class T>
	class LinkList : public detail::LinkListImpl
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
			iterator(LinkListNode* in_pNode, size_t in_nodeOffset) : m_pCurNode(in_pNode), m_NodeOffset(in_nodeOffset)
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
			
			friend bool operator==(const iterator& in_rLhs, const iterator& in_rRhs)
			{
				return in_rLhs.m_pCurNode == in_rRhs.m_pCurNode;
			}

			friend bool operator!=(const iterator& in_rLhs, const iterator& in_rRhs)
			{
				return in_rLhs.m_pCurNode != in_rRhs.m_pCurNode;
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
			const_iterator(const LinkListNode* in_pNode, size_t in_nodeOffset) : m_pCurNode(in_pNode), m_NodeOffset(in_nodeOffset)
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

			friend bool operator==(const const_iterator& in_rLhs, const const_iterator& in_rRhs)
			{
				return in_rLhs.m_pCurNode == in_rRhs.m_pCurNode;
			}

			friend bool operator!=(const const_iterator& lhs, const const_iterator& in_rRhs)
			{
				return in_rLhs.m_pCurNode != in_rRhs.m_pCurNode;
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

		void init(LinkListNode(T::* in_pNodeOffset))
		{
			m_NodeOffset = reinterpret_cast<size_t>(*reinterpret_cast<size_t**>(&in_pNodeOffset));
		}
		
		LinkList()
		{
			
		}

		LinkList(size_t in_nodeOffset)
		{
			m_NodeOffset = in_nodeOffset;
		}

		LinkList(LinkListNode(T::*in_pNodeOffset))
		{
			init(in_pNodeOffset);
		}

	private:
		LinkListNode* GetNode(T* in_pItem)
		{
			return reinterpret_cast<LinkListNode*>(reinterpret_cast<size_t>(in_pItem) + m_NodeOffset);
		}
		
	public:
		void push_back(T* in_pItem)
		{
			LinkListImpl::insert({ m_pEnd, m_NodeOffset }, GetNode(in_pItem));
		}

		void erase(T* in_pItem)
		{
			LinkListImpl::erase(GetNode(in_pItem));
		}

		void erase(iterator<T> in_start, iterator<T> in_finish)
		{
			LinkListNode* pCurNode = in_start.m_pCurNode;
			while (pCurNode != in_finish.m_pCurNode)
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