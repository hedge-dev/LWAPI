#pragma once

namespace app::fnd
{
	class ReferencedObject : BaseObject
	{
	protected:
		unsigned short objectSize;
		unsigned short refCount;
		csl::fnd::IAllocator* allocator;

	public:
		~ReferencedObject() override = default;

		void* operator new (size_t size, csl::fnd::IAllocator* allocator) {
			auto* object = static_cast<ReferencedObject*>(allocator->Alloc(size, 32));

			if (object)
			{
				object->allocator = allocator;
				object->objectSize = size;
				object->refCount = 0;
			}

			return object;
		}

		void operator delete(void* loc)
		{
			auto* object = static_cast<ReferencedObject*>(loc);

			if (object->allocator)
				object->allocator->Free(object);
		}

		void AddRef()
		{
			if (objectSize)
				++refCount;
		}

		void Release()
		{
			if (objectSize)
			{
				if (refCount-- == 1)
				{
					delete this;
				}
			}
		}
	};
}
