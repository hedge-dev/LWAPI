#pragma once
#pragma push_macro(RegisterClass)
#undef RegisterClass

namespace app
{
	class CSetObjectFactory
	{
	public:
		app::TArray<const CSetObjClass*, std::dummy::allocator<const CSetObjClass*>> m_Classes{};

		void BeginRegistration() {  }
		void RegisterClass(const CSetObjClass* pClass)
		{
			m_Classes.push_back(pClass);
		}

		void EndRegistration()
		{
			std::sort(m_Classes.begin(), m_Classes.end(), [](const CSetObjClass* c1, const CSetObjClass* c2) -> bool
			{
				return strcmp(c1->m_pName, c2->m_pName) >> 31;
			});
		}

		void CreateParamMap(app::ut::RefPtr<SetEd::CClassProject>& rClassProject)
		{
			for (const auto& pClass : m_Classes)
			{
				auto resCls = rClassProject->AddClass(pClass->m_pName, pClass->m_pType, pClass->m_DefaultRangeIn, pClass->m_DefaultRangeOut, nullptr, 0);
				pClass->SetupParamMap(resCls);
			}
		}

		void RegisterContainer(app::GameDocument& rDocument)
		{
			auto* pContainer = rDocument.GetService<CObjInfoContainer>();
			if (!pContainer)
				return;

			for (const auto& pClass : m_Classes)
			{
				CObjInfo* pInfo = pClass->CreateInfo(rDocument.GetAllocator());
				if (!pInfo)
					continue;

				pContainer->Register(pInfo->GetInfoName(), pInfo);
			}
		}

		void RegisterContainer(app::GameDocument& rDocument, std::dummy::vector<const char*>& objects)
		{
			auto* pContainer = rDocument.GetService<CObjInfoContainer>();
			if (!pContainer)
				return;

			auto* pAllocator = rDocument.GetAllocator();
			csl::ut::StringMap<const CSetObjClass*> objectLookup{ pAllocator };
			for (const auto& pClass : m_Classes)
				objectLookup.insert(pClass->m_pName, pClass);

			for (auto& pName : objects)
			{
				auto pClass = objectLookup.find(pName);
				if (pClass == objectLookup.end())
					continue;

				CObjInfo* pInfo = pClass->CreateInfo(pAllocator);
				if (!pInfo)
					continue;

				pContainer->Register(pInfo->GetInfoName(), pInfo);
			}
		}
	};
}

#pragma pop_macro(RegisterClass)