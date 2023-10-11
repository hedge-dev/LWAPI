#pragma once

namespace app::SetEd
{
	class CObjectProject : public fnd::ReferencedObject, public CResCommon<SResObjectProjectData>
	{
		inline static FUNCTION_PTR(SResObjectData*, __thiscall, ms_fpCreateObject, ASLR(0x004635D0), CObjectProject*, CResClass);

	public:
		SResObjectData* CreateObject(CResClass cls)
		{
			return ms_fpCreateObject(this, cls);
		}

		CResObject AddObject(CResClass cls)
		{
			auto* pObj = CreateObject(cls);

			if (pObj)
				ref().m_Objects.push_back(pObj);

			return { pObj };
		}

		CResObject GetObjectByID(CSetObjectID id)
		{
			for (size_t i = 0; i < ref().m_Objects.size(); i++)
			{
				SetEd::CResObject resObj{ ref().m_Objects[i] };
				if (resObj.IsValid() && id.Value == resObj.GetUID())
					return resObj;
			}

			return { nullptr };
		}
	};
}