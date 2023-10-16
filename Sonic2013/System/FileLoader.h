#pragma once

namespace app::fnd
{
	struct FileLoaderParam
	{
		csl::fnd::IAllocator* m_pAllocator;
		void* m_Unk2;
		void* m_Unk3;
		uint m_Unk4{ 8192 }; // Buffer Size?
		void* m_Unk5;
		uint m_Attributes;

	public:
		void SetMultiLanguageAttr(bool flag, uint lang)
		{
			m_Attributes = 0;
			if (flag)
			{
				m_Attributes = lang | 1;
			}
		}
	};
	
	class FileLoader : public ReferencedObject, public csl::fnd::SingletonPointer<FileLoader>
	{
	public:
		struct LoadInfo
		{
			csl::fnd::IAllocator* m_pAllocator{};
			csl::fnd::com_ptr<FileHandleObj> m_pHandle{};
			uint32_t m_LoadFlags{};
			uint32_t m_State{};
			size_t m_Unk1{};
			void* m_pLoadBuffer{}; // Owned by FileLoader::LoadBuffer
			size_t m_BufferSize{};
			INSERT_PADDING(8);
		};

		csl::ut::MoveArray<LoadInfo*> m_PendingFiles{};
		csl::ut::MoveArray<LoadInfo*> m_Unk1{};
		csl::ut::MoveArray<LoadInfo*> m_Unk2{};
		INSERT_PADDING(12){};
		bool m_SyncComplete{};
		INSERT_PADDING(31);

	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpResourceJobMTExec, ASLR(0x00491140), FileLoader* This, LoadInfo*);
		inline static FUNCTION_PTR(csl::fnd::com_ptr<FileHandleObj>&, __thiscall, ms_fpLoadFile, ASLR(0x00490C80), FileLoader* This, csl::fnd::com_ptr<FileHandleObj>&  rRet, const char* pName, const char* a3, const FileLoaderParam& params);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpPreLoadFile, ASLR(0x00491880), FileLoader* This, const char* pName, int priority);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x00491CC0), FileLoader* This);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpWaitSync, ASLR(0x00491F00), FileLoader* This, csl::fnd::com_ptr<FileHandleObj> handle);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpWaitSyncAll, ASLR(0x00491FB0), FileLoader* This);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStopFileAll, ASLR(0x00490E60), FileLoader* This);

		void ResourceJobMTExec(LoadInfo* info)
		{
			ms_fpResourceJobMTExec(this, info);
		}

		bool PreLoadFile(const char* pName, int priority)
		{
			return ms_fpPreLoadFile(this, pName, priority);
		}
		
		csl::fnd::com_ptr<FileHandleObj> LoadFile(const char* pName, const char* a3, const FileLoaderParam& params)
		{
			csl::fnd::com_ptr<FileHandleObj> result{};
			ms_fpLoadFile(this, result, pName, a3, params);
			return result;
		}

		csl::fnd::com_ptr<FileHandleObj> LoadFile(const char* pName, const FileLoaderParam& params)
		{
			return LoadFile(pName, nullptr, params);
		}

		bool IsSyncCompleteAll() const
		{
			return m_SyncComplete;
		}

		void WaitSync(csl::fnd::com_ptr<FileHandleObj> handle)
		{
			ms_fpWaitSync(this, handle);
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