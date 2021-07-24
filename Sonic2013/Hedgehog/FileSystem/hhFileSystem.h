#pragma once

namespace app::fnd
{
	class FileBinder;
	class FileCache;
	class FileSystem : public ReferencedObject, csl::fnd::SingletonPointer<FileSystem>
	{
	protected:
		csl::ut::FixedString<256> m_RootDir{};
		FileCache* m_pCache{};
		csl::ut::Bitset<size_t> m_LoadFlags{ 3 };
	
	public:
		virtual void Update() {};
		virtual FileBinder* GetDefaultBinder()
		{
			return nullptr;
		};

		static const char* GetFileName(const char* pName)
		{
			const char* pEnd = strchr(pName, 0);
			if (pEnd < pName)
				return pName;

			while (*pEnd != '\\' && *pEnd != '/')
			{
				if (--pEnd < pName)
					return pName;
			}

			return pEnd + 1;
		}
	};
}

DEFINE_SINGLETONPTR(app::fnd::FileSystem, ASLR(0x00FD42F4));