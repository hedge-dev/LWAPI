#pragma once

namespace csl::ut
{
	class LinkListNode
	{
		LinkListNode* next{ reinterpret_cast<LinkListNode*>(&previous) };
		LinkListNode* previous{ reinterpret_cast<LinkListNode*>(&next) };

	public:
		LinkListNode* operator++(int) const
		{
			return next;
		}

		LinkListNode* operator--(int) const
		{
			return previous;
		}
	};
	
	template<typename T>
	class LinkList
	{
		friend LinkListNode;
		class iterator
		{
			friend LinkList;
			LinkListNode* first{ reinterpret_cast<LinkListNode*>(&last) };
			LinkListNode* last { reinterpret_cast<LinkListNode*>(&first) };
		};
		
		size_t count{};
		size_t nodeOffset{};
		iterator root{};

	public:
		LinkList(size_t node_offset) : nodeOffset(node_offset)
		{
			
		}

		[[nodiscard]] LinkListNode* begin() const { return root.first; }
		[[nodiscard]] LinkListNode* end() const { return root.last; }

		[[nodiscard]] size_t size() const { return count; }

		[[nodiscard]]
		T* get(LinkListNode* node) const
		{
			if (!node)
				return nullptr;

			return reinterpret_cast<T*>(reinterpret_cast<char*>(node) - nodeOffset);
		}
	};
}