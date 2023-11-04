#pragma once

namespace app::fnd
{
	struct ResourceArgsData;
	class ResourceManager;

	class IResourceCustomLoader : public BaseObject
	{
	public:
		virtual void Setup(ResourceManager* in_pManager, ResourceArgsData& in_rArgs) = 0;
		virtual void Cleanup()
		{

		};
	};

	typedef IResourceCustomLoader* LoaderInitializer();

	struct ResourceCustomInfo
	{
		const char* ResExtension;
		LoaderInitializer* fpLoaderInitializer;
	};

	class ResourceManager : public ReferencedObject, csl::fnd::SingletonPointer<ResourceManager>
	{
	private:
		inline static FUNCTION_PTR(void*, __thiscall, ms_fpGetResource, ASLR(0x004A0C60), void*, const char*, size_t);
		inline static FUNCTION_PTR(void*, __thiscall, ms_fpRegisterList, ASLR(0x004A07C0), void*, const ResourceCustomInfo**);

	public:
		INSERT_PADDING(140) {};

		void* GetResource(const char* in_pName, size_t in_containerSize)
		{
			return ms_fpGetResource(this, in_pName, in_containerSize);
		}

		template<typename T>
		hh::ut::ResCommon<T> Get(const char* in_pName)
		{
			return hh::ut::ResCommon<T>(reinterpret_cast<T*>(GetResource(in_pName, sizeof(T))));
		}

		void RegisterList(const ResourceCustomInfo** in_ppList)
		{
			ms_fpRegisterList(this, in_ppList);
		}
	};
}

DEFINE_SINGLETONPTR(app::fnd::ResourceManager, ASLR(0x0FD3F88));