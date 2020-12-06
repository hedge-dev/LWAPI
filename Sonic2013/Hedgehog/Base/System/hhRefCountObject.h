#pragma once

namespace hh::base
{
	class CRefCountObject
	{
	private:
		size_t refCount{};

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