#pragma once

namespace app::fnd
{
	struct FileLoaderParam
	{
		csl::fnd::IAllocator* pAllocator;
		void* Unk2;
		void* Unk3;
		uint Unk4{ 8192 }; // Buffer Size?
		void* Unk5;
		uint Attributes;

	public:
		void SetMultiLanguageAttr(bool in_flag, uint in_lang)
		{
			Attributes = 0;
			if (in_flag)
			{
				Attributes = in_lang | 1;
			}
		}
	};
	
	class FileLoader : public ReferencedObject, public csl::fnd::SingletonPointer<FileLoader>
	{
	public:
		struct LoadInfo
		{
			csl::fnd::IAllocator* pAllocator{};
			csl::fnd::com_ptr<FileHandleObj> pHandle{};
			uint32_t LoadFlags{};
			uint32_t State{};
			size_t Unk1{};
			void* pLoadBuffer{}; // Owned by FileLoader::LoadBuffer
			size_t BufferSize{};
			INSERT_PADDING(8);
		};
		
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpResourceJobMTExec, ASLR(0x00491140), FileLoader* This, LoadInfo*);
		inline static FUNCTION_PTR(csl::fnd::com_ptr<FileHandleObj>&, __thiscall, ms_fpLoadFile, ASLR(0x00490C80), FileLoader* This, csl::fnd::com_ptr<FileHandleObj>&  rRet, const char* pName, const char* a3, const FileLoaderParam& params);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpPreLoadFile, ASLR(0x00491880), FileLoader* This, const char* pName, int priority);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x00491CC0), FileLoader* This);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpWaitSync, ASLR(0x00491F00), FileLoader* This, csl::fnd::com_ptr<FileHandleObj> handle);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpWaitSyncAll, ASLR(0x00491FB0), FileLoader* This);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStopFileAll, ASLR(0x00490E60), FileLoader* This);

		csl::ut::MoveArray<LoadInfo*> PendingFiles{};
		csl::ut::MoveArray<LoadInfo*> Unk1{};
		csl::ut::MoveArray<LoadInfo*> Unk2{};
		INSERT_PADDING(12){};
		bool SyncComplete{};
		INSERT_PADDING(31);

		void ResourceJobMTExec(LoadInfo* in_pInfo)
		{
			ms_fpResourceJobMTExec(this, in_pInfo);
		}

		bool PreLoadFile(const char* in_pName, int in_priority)
		{
			return ms_fpPreLoadFile(this, in_pName, in_priority);
		}
		
		csl::fnd::com_ptr<FileHandleObj> LoadFile(const char* in_pName, const char* in_pA3, const FileLoaderParam& in_rParams)
		{
			csl::fnd::com_ptr<FileHandleObj> result{};
			ms_fpLoadFile(this, result, in_pName, in_pA3, in_rParams);
			return result;
		}

		csl::fnd::com_ptr<FileHandleObj> LoadFile(const char* in_pName, const FileLoaderParam& in_rParams)
		{
			return LoadFile(in_pName, nullptr, in_rParams);
		}

		bool IsSyncCompleteAll() const
		{
			return m_SyncComplete;
		}

		void WaitSync(csl::fnd::com_ptr<FileHandleObj> in_handle)
		{
			ms_fpWaitSync(this, in_handle);
		}

		void WaitSyncAll()
		{
			ms_fpWaitSyncAll(this);
		}

		void StopFileAll()
		{
			ms_fpStopFileAll(this);
		}

		void Update()
		{
			ms_fpUpdate(this);
		}
	};
}

DEFINE_SINGLETONPTR(app::fnd::FileLoader, ASLR(0x0FD40A4));