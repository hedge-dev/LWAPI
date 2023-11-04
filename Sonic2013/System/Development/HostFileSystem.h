#pragma once
#pragma push_macro(CreateFile)
#undef CreateFile

namespace app::dev
{
	class HostFileSystem : public fnd::ReferencedObject, public csl::fnd::SingletonPointer<HostFileSystem>
	{
	public:
		struct FileEntry
		{
			char* pName;
			size_t Flags;
		};

		class DirectoryList
		{
		protected:
			csl::ut::InplaceMoveArray<FileEntry, 32> m_Entries;

		public:
			DirectoryList(csl::fnd::IAllocator* in_pAllocator) : m_Entries(in_pAllocator)
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
					pAllocator->Free(entry.pName);
				}

				m_Entries.clear();
			}
		};
		
	public:
		virtual fnd::IOStream* OpenFile(const char* in_pPath) = 0;
		virtual fnd::IOStream* CreateFile(const char* in_pPath) = 0;
		virtual bool EnumerateDirectory(const char* in_pPath, DirectoryList& in_rList) = 0;
	};
}

#pragma pop_macro("CreateFile")
DEFINE_SINGLETONPTR(app::dev::HostFileSystem, ASLR(0x00FD4080));