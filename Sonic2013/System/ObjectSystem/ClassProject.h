#pragma once

namespace app::SetEd
{
	class CClassProject : public fnd::ReferencedObject, public CResCommon<SResClassProjectData>
	{
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddClass, ASLR(0x004634A0), CClassProject* This, CResClass& pRet,
			const char* name, const char* categoryName, float rangeIn, float rangeOut, const SParamDescData* pParams, uint32 paramCount);

	public:
		CClassProject(void* pData) : CResCommon<app::SetEd::SResClassProjectData>(static_cast<SResClassProjectData*>(pData))
		{
			
		}

		CResClass AddClass(const char* name, const char* categoryName, float rangeIn, float rangeOut, const SParamDescData* pParams, uint32 paramCount)
		{
			CResClass ret{ nullptr };
			ms_fpAddClass(this, ret, name, categoryName, rangeIn, rangeOut, pParams, paramCount);

			return ret;
		}

		CResClass FindClass(const char* pName) const
		{
			if (!ref().m_Classes.size())
				return {};

			auto& classes = ref().m_Classes;

			SResClassData** result = std::find_if(classes.begin(), classes.end(), [pName](SResClassData* lhs) -> bool
				{
					return strcmp(lhs->m_pName, pName) == 0;
				});

			if (result == classes.end())
				return {};

			return { *result };
		}
	};
}