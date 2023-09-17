#pragma once

namespace app
{
	class ObjOccludeStoneInfo : public CObjInfo
	{
	private:
		inline static const char* ms_pModelName = "zdlc03_obj_breakwall";
		inline static const char* ms_pDebrisModelName = "zdlc03_obj_breakwall_brk";
		inline static const char* ms_pShadowModelName = "zdlc03_obj_breakwall_shadow";
		inline static const char* ms_pCollisionName = "zdlc03_obj_breakwall";

	public:
		inline static const char* ms_pName = "ObjOccludeStoneInfo";

		hh::gfx::res::ResModel Model{};
		hh::gfx::res::ResModel ShadowModel{};
		ResPhysicsMesh Collision{};
		debris::ResRandomSpaceDebris Debris{};

		ObjOccludeStoneInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));
			Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
			ShadowModel = ObjUtil::GetModelResource(ms_pShadowModelName, packFile);

			Collision = ObjUtil::GetPhysicsMeshResource(ms_pCollisionName, packFile);

			debris::ResRandomSpaceDebris::SDesc debrisDescription{ ms_pDebrisModelName, &packFile };
			Debris.Build(debrisDescription);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}