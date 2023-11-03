#pragma once

namespace app::fnd
{
	class RflTypeInfoRegistry : public ReferencedObject, csl::fnd::SingletonPointer<RflTypeInfoRegistry>
	{
	protected:
		csl::ut::StringMap<const RflTypeInfo*> m_Types{ GetAllocator() };

	public:
		RflTypeInfoRegistry()
		{
			
		}

		const RflTypeInfo* GetTypeInfo(const char* in_pName) const
		{
			auto result = m_Types[in_pName];
			if (result == m_Types.end())
				return nullptr;

			return result;
		}
		
		void RegisterTypeInfo(const RflTypeInfo* in_pInfo)
		{
			m_Types.insert(pInfo->GetName(), in_pInfo);
		}

		/// <summary>
		/// Register a list of type information, the list must be null terminated.
		/// </summary>
		/// <param name="pInfoList">Pointer to type info list</param>
		void RegisterList(const RflTypeInfo** in_ppInfoList)
		{
			size_t i = 0;
			while (in_ppInfoList[i])
			{
				RegisterTypeInfo(in_ppInfoList[i]);
				i++;
			}
		}

		void* ConstructObject(csl::fnd::IAllocator* in_pAllocator, const char* in_pName) const
		{
			auto pTypeInfo = GetTypeInfo(in_pName);
			if (!pTypeInfo || !in_pAllocator)
				return nullptr;

			auto* pInstance = in_pAllocator->Alloc(pTypeInfo->GetSize(), 16);
			pTypeInfo->ConstructObject(pInstance, in_pAllocator);
			return pInstance;
		}

		void FinishLoadedObject(void* in_pInstance, const char* in_pName) const
		{
			auto* pTypeInfo = GetTypeInfo(in_pName);
			if (!pTypeInfo)
				return;

			pTypeInfo->FinishLoadedObject(in_pInstance);
		}

		void CleanupLoadedObject(void* in_pInstance, const char* in_pName) const
		{
			auto* pTypeInfo = GetTypeInfo(in_pName);
			if (!pTypeInfo)
				return;

			pTypeInfo->CleanupLoadedObject(in_pInstance);
		}
	};
}

DEFINE_SINGLETONPTR(app::fnd::RflTypeInfoRegistry, ASLR(0x00FD4310));