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

	class MutexLock
	{
		Mutex* m_pMutex;

	public:
		MutexLock(Mutex& rMutex) : m_pMutex(&rMutex)
		{
			m_pMutex->Lock();
		}

		~MutexLock()
		{
			m_pMutex->Unlock();
		}
	};
}