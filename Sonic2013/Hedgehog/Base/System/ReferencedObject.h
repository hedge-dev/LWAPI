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

			void* operator new (size_t in_size, csl::fnd::IAllocator* in_pAllocator)
			{
				auto* pObject = static_cast<ReferencedObject*>(in_pAllocator->Alloc(in_size, 32));

				if (pObject)
				{
					pObject->m_pAllocator = in_pAllocator;
					pObject->m_ObjectSize = in_size;
					pObject->m_RefCount = 0;
				}

				return pObject;
			}

			void* operator new (size_t in_size, csl::fnd::IAllocator& in_rAllocator)
			{
				return operator new(in_size, &in_rAllocator);
			}

			void* operator new(size_t in_size, void* in_pPlacement)
			{
				auto* pObject = static_cast<ReferencedObject*>(in_pPlacement);
				pObject->m_pAllocator = nullptr;
				pObject->m_ObjectSize = 0;
				pObject->m_RefCount = 0;
				return in_pPlacement;
			}

			void operator delete(void* in_pLoc)
			{
				auto* pObject = static_cast<ReferencedObject*>(in_pLoc);

				if (pObject->m_pAllocator)
					pObject->m_pAllocator->Free(pObject);
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

		class ThreadSafeReferencedObject : public ReferencedObject
		{
		protected:
			size_t m_SafeRefCount{};

		public:
			ThreadSafeReferencedObject()
			{

			}

			void AddRef()
			{
				if (GetSize())
					InterlockedIncrement(&m_SafeRefCount);
			}

			void Release()
			{
				if (GetSize())
				{
					if (!InterlockedDecrement(&m_SafeRefCount))
					{
						delete this;
					}
				}
			}
		};
	}
}
