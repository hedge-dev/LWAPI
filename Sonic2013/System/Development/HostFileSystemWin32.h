#pragma once

namespace app::dev
{
	class HostFileSystemWin32 : public HostFileSystem, csl::fnd::SingletonPointer<HostFileSystemWin32>
	{
	public:
		DirectoryList Root{ GetAllocator() };
	};
}

DEFINE_SINGLETONPTR(app::dev::HostFileSystemWin32, ASLR(0x00FD4080));