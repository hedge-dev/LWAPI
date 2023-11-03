#pragma once

namespace app::fnd
{
	class FileBinder;
	class FileCache;
	class FileSystem : public ReferencedObject, public csl::fnd::SingletonPointer<FileSystem>
	{
	public:
		csl::ut::FixedString<256> RootDir{};
		FileCache* pCache{};
		csl::ut::Bitset<size_t> LoadFlags{ 3 };
	
		virtual void Update() {};
		virtual FileBinder* GetDefaultBinder()
		{
			return nullptr;
		};

		FileCache* GetCache() const
		{
			return pCache;
		}

		static const char* GetFileName(const char* in_pName)
		{
			const char* pEnd = strchr(in_pName, 0);
			if (pEnd < in_pName)
				return in_pName;

			while (*pEnd != '\\' && *pEnd != '/')
			{
				if (--pEnd < in_pName)
					return in_pName;
			}

			return pEnd + 1;
		}
	};
}

DEFINE_SINGLETONPTR(app::fnd::FileSystem, ASLR(0x00FD42F4));