#pragma once

namespace app::fnd
{
	class FileReader : public ReferencedObject, public csl::fnd::SingletonPointer<FileReader>
	{
	public:
		virtual void Update() {}
		virtual csl::fnd::com_ptr<FileHandleObj> GetFileHandle(const char* in_pPath) { return nullptr; }
		virtual bool IsFileExist(const char* in_pName, FileBinder* in_pBinder) { return false; }
		virtual size_t GetFileSize(const char* in_pName, FileBinder* in_pBinder) { return 0; }
		virtual csl::fnd::com_ptr<FileHandleObj> LoadFile(const char* in_pPath, const char* in_pName, 
			csl::fnd::IAllocator* in_pBufAloc, void* in_pBuf, size_t in_bufSize, FileBinder* in_pBinder) { return nullptr; }
		virtual void StopFile(csl::fnd::com_ptr<FileHandleObj> in_pHandle) {}
		virtual void StopFileAll() {}
		virtual bool UnloadFile(csl::fnd::com_ptr<FileHandleObj> in_pHandle) { return false; }
		virtual bool IsSyncComplete(csl::fnd::com_ptr<FileHandleObj> in_pHandle) { return true; }
		virtual bool IsSyncCompleteAll() { return true; }
		virtual void WaitSync(csl::fnd::com_ptr<FileHandleObj> in_pHandle) {}
		virtual void WaitSyncAll() {}
		virtual bool DbgGet(csl::ut::MoveArray<app::dbg::FileInfo::Data>& in_rData, bool in_a2) { return false; }
		virtual csl::fnd::com_ptr<FileHandleObj> CreateHandle(const char* in_pPath, const char* in_pName,
			csl::fnd::IAllocator* in_pBufAloc, void* in_pBuf, size_t in_bufSize, FileBinder* in_pBinder) { return nullptr; }
		virtual void AddRequest(const csl::fnd::com_ptr<FileHandleObj>& in_pHandle, void* in_pBuf, size_t in_bufSize) {}
		virtual void AddRequest(const csl::fnd::com_ptr<FileHandleObj>& in_pHandle) {}
	};
}

DEFINE_SINGLETONPTR(app::fnd::FileReader, ASLR(0x00FD42F0));