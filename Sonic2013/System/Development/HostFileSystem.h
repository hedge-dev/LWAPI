#pragma once
#pragma push_macro(CreateFile)
#undef CreateFile

namespace app::dev
{
	class HostFileSystem : public fnd::ReferencedObject, csl::fnd::SingletonPointer<HostFileSystem>
	{
	public:
		struct FileEntry
		{
			char* m_pName;
			size_t m_Flags;
		};

		class DirectoryList
		{
		protected:
			csl::ut::InplaceMoveArray<FileEntry, 32> m_Entries;

		public:
			DirectoryList(csl::fnd::IAllocator* pAllocator) : m_Entries(pAllocator)
			{
				
			}

			~DirectoryList()
			{
				Clear();
			}
			
			FileEntry* begin() const { return m_Entries.begin(); }
			FileEntry* end() const { return m_Entries.end(); }
			size_t size() const { return m_Entries.size(); }

			void Clear()
			{
				auto* pAllocator = m_Entries.get_allocator();
				if (!pAllocator)
					return;
				
				for (auto& entry : m_Entries)
				{
					pAllocator->Free(entry.m_pName);
				}

				m_Entries.clear();
			}
		};
		
	public:
		virtual fnd::IOStream* OpenFile(const char* pPath) = 0;
		virtual fnd::IOStream* CreateFile(const char* pPath) = 0;
		virtual bool EnumerateDirectory(const char* pPath, DirectoryList& list) = 0;
	};
}

#pragma pop_macro("CreateFile")
DEFINE_SINGLETONPTR(app::dev::HostFileSystem, ASLR(0x00FD4080));