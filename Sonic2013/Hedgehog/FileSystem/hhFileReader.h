#pragma once

namespace app::fnd
{
	class FileReader : public ReferencedObject, csl::fnd::SingletonPointer<FileReader>
	{
	public:
		virtual void Update() {}
		virtual csl::fnd::com_ptr<FileHandleObj> GetFileHandle(const char* pPath) { return nullptr; }
		virtual bool IsFileExist(const char* pName, FileBinder* pBinder) { return false; }
		virtual size_t GetFileSize(const char* pName, FileBinder* pBinder) { return 0; }
		virtual csl::fnd::com_ptr<FileHandleObj> LoadFile(const char* pPath, const char* pName, 
			csl::fnd::IAllocator* pBufAloc, void* pBuf, size_t bufSize, FileBinder* pBinder) { return nullptr; }
		virtual void StopFile(csl::fnd::com_ptr<FileHandleObj> pHandle) {}
		virtual void StopFileAll() {}
		virtual bool UnloadFile(csl::fnd::com_ptr<FileHandleObj> pHandle) { return false; }
		virtual bool IsSyncComplete(csl::fnd::com_ptr<FileHandleObj> pHandle) { return true; }
		virtual bool IsSyncCompleteAll() { return true; }
		virtual void WaitSync(csl::fnd::com_ptr<FileHandleObj> pHandle) {}
		virtual void WaitSyncAll() {}
		virtual bool DbgGet(csl::ut::MoveArray<app::dbg::FileInfo::Data>& rData, bool a2) { return false; }
		virtual csl::fnd::com_ptr<FileHandleObj> CreateHandle(const char* pPath, const char* pName,
			csl::fnd::IAllocator* pBufAloc, void* pBuf, size_t bufSize, FileBinder* pBinder) { return nullptr; }
		virtual void AddRequest(const csl::fnd::com_ptr<FileHandleObj>& rpHandle, void* pBuf, size_t bufSize) {}
		virtual void AddRequest(const csl::fnd::com_ptr<FileHandleObj>& rpHandle) {}
	};
}

DEFINE_SINGLETONPTR(app::fnd::FileReader, ASLR(0x00FD42F0));