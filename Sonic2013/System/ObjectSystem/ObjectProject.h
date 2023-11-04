#pragma once

namespace app::SetEd
{
	class CObjectProject : public fnd::ReferencedObject, public CResCommon<SResObjectProjectData>
	{
		inline static FUNCTION_PTR(SResObjectData*, __thiscall, ms_fpCreateObject, ASLR(0x004635D0), CObjectProject*, CResClass);

	public:
		SResObjectData* CreateObject(CResClass in_class)
		{
			return ms_fpCreateObject(this, in_class);
		}

		CResObject AddObject(CResClass in_class)
		{
			auto* pObj = CreateObject(in_class);

			if (pObj)
				ref().Objects.push_back(pObj);

			return { pObj };
		}

		CResObject GetObjectByID(CSetObjectID in_id)
		{
			for (size_t i = 0; i < ref().Objects.size(); i++)
			{
				SetEd::CResObject resObj{ ref().Objects[i] };
				if (resObj.IsValid() && in_id.Value == resObj.GetUID())
					return resObj;
			}

			return { nullptr };
		}
	};
}