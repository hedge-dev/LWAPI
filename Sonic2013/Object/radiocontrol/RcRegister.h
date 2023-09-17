#pragma once

namespace app
{
	class RcBase;

	template <class T>
	void CreateRcObjInfo(byte in_variant, CObjInfoContainer& in_rContainer, csl::fnd::IAllocator& in_rAllocator)
	{
		T* pInfo = new(in_rAllocator) T(in_variant);
		if (!pInfo)
			return;

		in_rContainer.Register(pInfo->GetInfoName(), pInfo);
	}

	inline void RegisterResourceInfo(GameDocument& in_rDocument, const RcInfo& in_rResourceInfo, csl::fnd::IAllocator& in_rAllocator)
	{
		auto* pInfoContainer = in_rDocument.GetService<CObjInfoContainer>();
		switch (in_rResourceInfo.Type)
		{
		case 0:
			CreateRcObjInfo<RcHelicopterInfo>(in_rResourceInfo.Variant, *pInfoContainer, in_rAllocator);
			break;
		case 1:
			CreateRcObjInfo<RcFighterInfo>(in_rResourceInfo.Variant, *pInfoContainer, in_rAllocator);
			break;
		case 2:
			CreateRcObjInfo<RcStealthInfo>(in_rResourceInfo.Variant, *pInfoContainer, in_rAllocator);
			break;
		case 3:
			CreateRcObjInfo<RcHovercraftInfo>(in_rResourceInfo.Variant, *pInfoContainer, in_rAllocator);
			break;
		case 4:
			CreateRcObjInfo<RcBalloonInfo>(in_rResourceInfo.Variant, *pInfoContainer, in_rAllocator);
			break;
		case 5:
			CreateRcObjInfo<RcUfoInfo>(in_rResourceInfo.Variant, *pInfoContainer, in_rAllocator);
			break;
		case 6:
			CreateRcObjInfo<RcOmochaoInfo>(in_rResourceInfo.Variant, *pInfoContainer, in_rAllocator);
			break;
		default:
			break;
		}
	}

	static RcBase* CreateRCObject(GameDocument& in_rDocument, const RcCreateInfo& in_rCreateInfo, csl::fnd::IAllocator& in_rAllocator)
	{
		FUNCTION_PTR(RcBase*, __cdecl, ms_fpCreateRCObject, ASLR(0x00744D00), GameDocument&, const RcCreateInfo&, csl::fnd::IAllocator&);

		return ms_fpCreateRCObject(in_rDocument, in_rCreateInfo, in_rAllocator);
	}
}