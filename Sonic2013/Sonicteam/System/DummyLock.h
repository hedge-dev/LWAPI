#pragma once

namespace csl::fnd
{
	class DummyLock
	{
	public:
		void Lock() {}
		void Unlock() {}
	};
}