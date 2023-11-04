#pragma once

namespace csl::hio
{
	// This doesn't actually exist anywhere, it's made so the library can actually be used
	class HioClient : public HioServer
	{
	public:
		HioClient(fnd::IAllocator* in_pAlloc) : HioServer(in_pAlloc)
		{
			SetServer(false);
		}

		~HioClient()
		{
			Cleanup();
		}
	};
}