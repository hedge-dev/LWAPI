#pragma once

namespace app
{
	namespace ut
	{
		template<class T>
		class RefPtr;
	}

	namespace fnd
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
				auto* pObj = static_cast<ReferencedObject*>(placement);
				pObj->m_pAllocator = nullptr;
				pObj->m_ObjectSize = 0;
				pObj->m_RefCount = 0;
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
				{
					++m_RefCount;
				}
			}

			void Release()
			{
				if (m_ObjectSize)
				{
					if (--m_RefCount == 0)
					{
						delete this;
					}
				}
			}

			csl::fnd::IAllocator* GetAllocator() const
			{
				return m_pAllocator;
			}

			template<class T, typename... Args>
			HH_FORCE_INLINE ut::RefPtr<T> make_ref(Args&&... args) const
			{
				return new(GetAllocator()) T(std::forward<Args>(args)...);
			}
		};
	}
}
