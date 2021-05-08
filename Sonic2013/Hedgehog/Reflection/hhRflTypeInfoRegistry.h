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

		const RflTypeInfo* GetTypeInfo(const char* pName) const
		{
			auto result = m_Types[pName];
			if (result == m_Types.end())
				return nullptr;

			return result;
		}
		
		void RegisterTypeInfo(const RflTypeInfo* pInfo)
		{
			m_Types.insert(pInfo->GetName(), pInfo);
		}

		/// <summary>
		/// Register a list of type information, the list must be null terminated.
		/// </summary>
		/// <param name="pInfoList">Pointer to type info list</param>
		void RegisterList(const RflTypeInfo** pInfoList)
		{
			size_t i = 0;
			while (pInfoList[i])
			{
				RegisterTypeInfo(pInfoList[i]);
				i++;
			}
		}

		void* ConstructObject(csl::fnd::IAllocator* pAllocator, const char* pName) const
		{
			auto pTypeInfo = GetTypeInfo(pName);
			if (!pTypeInfo || !pAllocator)
				return nullptr;

			auto* pInstance = pAllocator->Alloc(pTypeInfo->GetSize(), 16);
			pTypeInfo->ConstructObject(pInstance, pAllocator);
			return pInstance;
		}

		void FinishLoadedObject(void* pInstance, const char* pName) const
		{
			auto* pTypeInfo = GetTypeInfo(pName);
			if (!pTypeInfo)
				return;

			pTypeInfo->FinishLoadedObject(pInstance);
		}

		void CleanupLoadedObject(void* pInstance, const char* pName) const
		{
			auto* pTypeInfo = GetTypeInfo(pName);
			if (!pTypeInfo)
				return;

			pTypeInfo->CleanupLoadedObject(pInstance);
		}
	};
}

DEFINE_SINGLETONPTR(app::fnd::RflTypeInfoRegistry, ASLR(0x00FD4310));