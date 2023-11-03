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
	protected:
		const char* m_pName{};
		LoaderInitializer* m_pLoaderInit{};
		IResourceLoader* m_pLoader{};
		size_t m_Hash{};

	public:
		ResourceTypeInfo(const char* in_pName) : m_pName(in_pName)
		{
			
		}
		
		ResourceTypeInfo(const char* in_pName, LoaderInitializer& in_rInitializer) : m_pName(in_pName), m_pLoaderInit(&in_rInitializer)
		{
			
		}

		[[nodiscard]] const char* GetName() const
		{
			return m_pName;
		}

		[[nodiscard]] IResourceLoader* GetLoader() const
		{
			return m_pLoader;
		}
	};
}