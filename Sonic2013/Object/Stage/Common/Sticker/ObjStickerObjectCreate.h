#pragma once

namespace app
{
	class ObjStickerObject;

	struct StickerObjectCInfoBase
	{
		char Type{};
		INSERT_PADDING(3){};
		GameObject* pParentObject{};
		csl::math::Matrix34 Unk1{};
		csl::math::Matrix34 Unk2{};
		int Unk3{};
		int Unk4{};
		float Unk5{};
	};
}

namespace app::obj_sticker
{
	inline static FUNCTION_PTR(ObjStickerObject*, __cdecl, ms_fpCreateStickerObject, ASLR(0x00669210), csl::fnd::IAllocator*, GameDocument&, StickerObjectCInfoBase&);
	
	inline ObjStickerObject* CreateStickerObject(csl::fnd::IAllocator* pAllocator, GameDocument& in_rDocument, StickerObjectCInfoBase& in_rCreateInfo)
	{
		return ms_fpCreateStickerObject(pAllocator, in_rDocument, in_rCreateInfo);
	}
}