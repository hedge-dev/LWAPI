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
	
	class FileLoader : public ReferencedObject, csl::fnd::SingletonPointer<FileLoader>
	{
		INSERT_PADDING(92);

	public:
		inline static FUNCTION_PTR(csl::fnd::com_ptr<FileHandleObj>, __thiscall, ms_fpLoadFile, ASLR(0x00490C80), void* This, const char* pName, const char* a3, FileLoaderParam& params);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpPreLoadFile, ASLR(0x00491880), void* This, const char* pName, int priority);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x00491CC0), void* This);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpWaitSync, ASLR(0x00491F00), void* This, csl::fnd::com_ptr<FileHandleObj>& pHandle);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpWaitSyncAll, ASLR(0x00491FB0), void* This);
		
		bool PreLoadFile(const char* pName, int priority)
		{
			return ms_fpPreLoadFile(this, pName, priority);
		}
		
		csl::fnd::com_ptr<FileHandleObj> LoadFile(const char* pName, const char* a3, FileLoaderParam& params)
		{
			return ms_fpLoadFile(this, pName, a3, params);
		}

		csl::fnd::com_ptr<FileHandleObj> LoadFile(const char* pName, FileLoaderParam& params)
		{
			return LoadFile(pName, nullptr, params);
		}

		void WaitSync(csl::fnd::com_ptr<FileHandleObj>& rHandle)
		{
			ms_fpWaitSync(this, rHandle);
		}

		void WaitSyncAll()
		{
			ms_fpWaitSyncAll(this);
		}

		void Update()
		{
			ms_fpUpdate(this);
		}
	};
}

DEFINE_SINGLETONPTR(app::fnd::FileLoader, ASLR(0x0FD40A4));