#pragma once

namespace hh::base
{
	struct SInitializeHHBaseSetting
	{
		typedef void(InitializeWorkerThread_t)();
		typedef void(FinalizeWorkerThread_t)(void*);

		size_t m_Version{}; // Guessed, always 0x10100
		InitializeWorkerThread_t* m_InitWorkerThreadCallback{};
		FinalizeWorkerThread_t* m_FinalizeWorkerThreadCallback{};
	};

	inline SInitializeHHBaseSetting& ms_Settings = *reinterpret_cast<SInitializeHHBaseSetting*>(ASLR(0x011D701C));

	inline void InitializeWorkerThread()
	{
		ms_Settings.m_InitWorkerThreadCallback();
	}
}