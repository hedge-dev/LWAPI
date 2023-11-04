#pragma once
#pragma push_macro(RegisterClass)
#undef RegisterClass

namespace app
{
	class CSetObjectFactory
	{
	public:
		app::TArray<const CSetObjClass*, std::dummy::allocator<const CSetObjClass*>> Classes{};

		void BeginRegistration() {  }
		void RegisterClass(const CSetObjClass* in_pClass)
		{
			Classes.push_back(in_pClass);
		}

		void EndRegistration()
		{
			std::sort(Classes.begin(), Classes.end(), [](const CSetObjClass* c1, const CSetObjClass* c2) -> bool
			{
				return strcmp(c1->pName, c2->pName) >> 31;
			});
		}

		void CreateParamMap(app::ut::RefPtr<SetEd::CClassProject>& in_rClassProject)
		{
			for (const auto& pClass : Classes)
			{
				auto resCls = in_rClassProject->AddClass(pClass->pName, pClass->pType, pClass->DefaultRangeIn, pClass->DefaultRangeOut, nullptr, 0);
				pClass->SetupParamMap(resCls);
			}
		}

		void RegisterContainer(app::GameDocument& in_rDocument)
		{
			auto* pContainer = in_rDocument.GetService<CObjInfoContainer>();
			if (!pContainer)
				return;

			for (const auto& pClass : Classes)
			{
				CObjInfo* pInfo = pClass->CreateInfo(in_rDocument.GetAllocator());
				if (!pInfo)
					continue;

				pContainer->Register(pInfo->GetInfoName(), pInfo);
			}
		}

		void RegisterContainer(app::GameDocument& in_rDocument, std::dummy::vector<const char*>& in_rObjects)
		{
			auto* pContainer = in_rDocument.GetService<CObjInfoContainer>();
			if (!pContainer)
				return;

			auto* pAllocator = in_rDocument.GetAllocator();
			csl::ut::StringMap<const CSetObjClass*> objectLookup{ pAllocator };
			for (const auto& pClass : Classes)
				objectLookup.insert(pClass->pName, pClass);

			for (auto& pName : in_rObjects)
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