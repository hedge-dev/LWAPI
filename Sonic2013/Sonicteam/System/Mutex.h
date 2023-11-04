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

	class MutexGuard
	{
		Mutex* m_pMutex;

	public:
		MutexGuard(Mutex& in_rMutex) : m_pMutex(&in_rMutex)
		{
			m_pMutex->Lock();
		}

		~MutexGuard()
		{
			m_pMutex->Unlock();
		}
	};
}