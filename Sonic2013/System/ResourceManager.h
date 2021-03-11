#pragma once

namespace app::fnd
{
	struct ResourceArgsData;
	class ResourceManager;

	class IResourceCustomLoader : public BaseObject
	{
	public:
		virtual void Setup(ResourceManager* pManager, ResourceArgsData& args) = 0;
		virtual void Cleanup()
		{

		};
	};

	typedef IResourceCustomLoader* LoaderInitializer();

	struct ResourceCustomInfo
	{
		const char* m_ResExtension;
		LoaderInitializer* m_fpLoaderInitializer;
	};

	class ResourceManager : public ReferencedObject, csl::fnd::SingletonPointer<ResourceManager>
	{
		INSERT_PADDING(140) {};

	public:
		inline static FUNCTION_PTR(void*, __thiscall, ms_fpGetResource, ASLR(0x004A0C60), void* This, const char* pName, size_t containerSize);
		inline static FUNCTION_PTR(void*, __thiscall, ms_fpRegisterList, ASLR(0x004A07C0), void* This, const ResourceCustomInfo** ppList);

		void* GetResource(const char* pName, size_t containerSize)
		{
			return ms_fpGetResource(this, pName, containerSize);
		}

		template<typename T>
		ResCommon<T> Get(const char* pName)
		{
			return ResCommon<T>(reinterpret_cast<T*>(GetResource(pName, sizeof(T))));
		}

		void RegisterList(const ResourceCustomInfo** ppList)
		{
			ms_fpRegisterList(this, ppList);
		}
	};
}

DEFINE_SINGLETONPTR(app::fnd::ResourceManager, ASLR(0x0FD3F88));