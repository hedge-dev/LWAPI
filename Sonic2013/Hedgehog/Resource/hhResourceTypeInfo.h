#pragma once

namespace hh::ut
{
	struct SLoadedResourceParameter;
	class IResourceLoader
	{
		virtual ~IResourceLoader() = default;
		virtual void PrepareReplaceLoadedResource(void*, uint*, SLoadedResourceParameter*){}
		virtual void ReplaceLoadedResource(const char*, void*, uint*, csl::fnd::IAllocator*){}
		virtual void FinishLoadedResource(void*, uint, csl::fnd::IAllocator*){}
		virtual void BindLoadedResource(void*, csl::fnd::IAllocator*, PackFile){}
		virtual void CleanupLoadedResource(void*, uint){}
		virtual void PrepareLoadedResource(void*, uint*, SLoadedResourceParameter*){}
	};

	typedef IResourceLoader* LoaderInitializer();
	class ResourceTypeInfo
	{
		const char* m_pName{};
		LoaderInitializer* m_pLoaderInit{};
		INSERT_PADDING(8){};

	public:
		ResourceTypeInfo(const char* pName) : m_pName(pName)
		{
			
		}
		
		ResourceTypeInfo(const char* pName, LoaderInitializer& pInitializer) : m_pName(pName), m_pLoaderInit(&pInitializer)
		{
			
		}

		const char* GetName() const
		{
			return m_pName;
		}
	};
}