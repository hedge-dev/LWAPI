#pragma once

namespace app
{
	class ObjRedRingInfo : public CObjInfo
	{
	private:
		inline static const char* ms_pPackFileName = "CommonObject.pac";
		inline static const char* ms_pModelName = "cmn_obj_redring";
		inline static const char* ms_pHideModelName = "cmn_obj_redring_hide";

	public:
		hh::gfx::res::ResModel Model{};
		hh::gfx::res::ResModel HideModel{};

		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ms_pPackFileName);
			Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
			HideModel = ObjUtil::GetModelResource(ms_pHideModelName, packFile);
		}

		const char* GetInfoName() override
		{
			return "ObjRedRingInfo";
		}
	};
}