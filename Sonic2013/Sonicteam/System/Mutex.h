#pragma once
#include "synchapi.h"

namespace csl::fnd
{
	class Mutex
	{
		CRITICAL_SECTION m_CriticalSection;

	public:
		Mutex()
		{
			InitializeCriticalSection(&m_CriticalSection);
		}

		~Mutex()
		{
			DeleteCriticalSection(&m_CriticalSection);
		}
		
		void Lock()
		{
			EnterCriticalSection(&m_CriticalSection);
		}

		void Unlock()
		{
			LeaveCriticalSection(&m_CriticalSection);
		}
	};
}