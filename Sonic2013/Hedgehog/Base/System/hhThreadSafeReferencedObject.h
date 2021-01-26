#pragma once

namespace app::fnd
{
	class ThreadSafeReferencedObject : public ReferencedObject
	{
	protected:
		size_t m_SafeRefCount;

	public:
		void AddRef()
		{
			if (m_ObjectSize)
				InterlockedIncrement(&m_SafeRefCount);
		}

		void Release()
		{
			if (m_ObjectSize)
			{
				if (!InterlockedDecrement(&m_SafeRefCount))
				{
					delete this;
				}
			}
		}
	};
}