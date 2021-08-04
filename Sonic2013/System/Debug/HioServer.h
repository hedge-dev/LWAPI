#pragma once

#ifndef S13_DEBUG_SERVER_PORT
#define S13_DEBUG_SERVER_PORT 10000
#endif

namespace app::dbg
{
	class HioServer : public fnd::ReferencedObject, public csl::hio::HioServer, public csl::fnd::SingletonPointer<HioServer>
	{
	public:
		HioServer() : csl::hio::HioServer(GetAllocator())
		{
			
		}

		bool Setup()
		{
			return Startup("none", S13_DEBUG_SERVER_PORT);
		}
	};
}

DEFINE_SINGLETONPTR(app::dbg::HioServer, ASLR(0x00FD409C));