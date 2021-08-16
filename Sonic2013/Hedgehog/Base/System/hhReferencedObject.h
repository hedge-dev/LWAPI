#pragma once

namespace app::fnd
{
	class ReferencedObject : public BaseObject
	{
	protected:
		unsigned short m_ObjectSize;
		unsigned short m_RefCount;
		csl::fnd::IAllocator* m_pAllocator;
		
		size_t GetSize()
		{
			return m_ObjectSize;
		}
		
	public:
		ReferencedObject()
		{
			
		}
		
		void* operator new (size_t size, csl::fnd::IAllocator* allocator)
		{
			auto* object = static_cast<ReferencedObject*>(allocator->Alloc(size, 32));

			if (object)
			{
				object->m_pAllocator = allocator;
				object->m_ObjectSize = size;
				object->m_RefCount = 0;
			}

			return object;
		}

		void* operator new (size_t size, csl::fnd::IAllocator& allocator)
		{
			return operator new(size, &allocator);
		}
		
		void* operator new(size_t size, void* placement)
		{
			return placement;
		}
		
		void operator delete(void* loc)
		{
			auto* object = static_cast<ReferencedObject*>(loc);

			if (object->m_pAllocator)
				object->m_pAllocator->Free(object);
		}

		void AddRef()
		{
			if (m_ObjectSize)
				++m_RefCount;
		}

		void Release()
		{
			if (m_ObjectSize)
			{
				if (m_RefCount-- == 1)
				{
					delete this;
				}
			}
		}

		csl::fnd::IAllocator* GetAllocator() const
		{
			return m_pAllocator;
		}
	};
}
