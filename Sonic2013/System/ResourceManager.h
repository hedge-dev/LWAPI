#pragma once

namespace app::fnd
{
	class ResRawData
	{
		const char* m_pName{};
		void* m_pData{};
		void* m_pAddress{};
		size_t m_DataSize{};
		size_t m_pUnk1{}; // Alignment?

	public:
		const char* GetName() const
		{
			return m_pName;
		}

		void* GetData()
		{
			return m_pData;
		}

		const void* GetAddress() const
		{
			return m_pAddress;
		}

		size_t GetSize() const
		{
			return m_DataSize;
		}
	};

	template<typename T>
	class CResCommon
	{
	protected:
		T* m_pRes{};

	public:
		ResCommon(T* pRes) : m_pRes(pRes)
		{

		}

		bool IsValid() const
		{
			return m_pRes != nullptr;
		}

		T* operator->()
		{
			return m_pRes;
		}
	};

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
		CResCommon<T> Get(const char* pName)
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