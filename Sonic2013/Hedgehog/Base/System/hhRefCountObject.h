#pragma once

namespace hh::base
{
	class CRefCountObject
	{
	private:
		size_t refCount{ 1 };

	public:
		virtual ~CRefCountObject() = default;

		void AddRef()
		{
			InterlockedIncrement(&refCount);
		}

		void Release()
		{
			if (!InterlockedDecrement(&refCount))
			{
				delete this;
			}
		}
	};
}