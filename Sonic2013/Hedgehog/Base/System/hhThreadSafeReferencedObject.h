#pragma once

namespace app::fnd
{
	class ThreadSafeReferencedObject : public ReferencedObject
	{
	protected:
		size_t m_SafeRefCount;

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