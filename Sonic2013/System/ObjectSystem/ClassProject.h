#pragma once

namespace app::SetEd
{
	class CClassProject : public fnd::ReferencedObject, public CResCommon<SResClassProjectData>
	{
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddClass, ASLR(0x004634A0), CClassProject*, CResClass&,
			const char*, const char*, float, float, const SParamDescData*, uint32);

	public:
		CClassProject(void* in_pData) : CResCommon<app::SetEd::SResClassProjectData>(static_cast<SResClassProjectData*>(in_pData))
		{
			
		}

		CResClass AddClass(const char* in_pName, const char* in_pCategoryName, float in_rangeIn, float in_rangeOut, const SParamDescData* in_pParams, uint32 in_paramCount)
		{
			CResClass ret{ nullptr };
			ms_fpAddClass(this, ret, in_pName, in_pCategoryName, in_rangeIn, in_rangeOut, in_pParams, in_paramCount);

			return ret;
		}

		CResClass FindClass(const char* in_pName) const
		{
			if (!ref().Classes.size())
				return {};

			auto& classes = ref().Classes;

			SResClassData** result = std::find_if(classes.begin(), classes.end(), [in_pName](SResClassData* lhs) -> bool
				{
					return strcmp(lhs->pName, in_pName) == 0;
				});

			if (result == classes.end())
				return {};

			return { *result };
		}
	};
}