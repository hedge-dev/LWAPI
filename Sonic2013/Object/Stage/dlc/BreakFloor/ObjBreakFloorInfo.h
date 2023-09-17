#pragma once

namespace app
{
	class ObjBreakFloorInfo : public CObjInfo
	{
	private:
		inline static const char* ms_pModelName = "zdlc03_obj_breakfloor";
		inline static const char* ms_pCollisionName = "zdlc03_obj_breakfloor";
		inline static const char* ms_pDebrisModelName = "zdlc03_obj_breakfloor_brk";

	public:
		inline static const char* ms_pName = "ObjBreakFloorInfo";

		hh::gfx::res::ResModel Model{};
		hh::gfx::res::ResSkeleton Skeleton{};
		ResPhysicsMesh Collision{};
		debris::ResRandomSpaceDebris Debris{};

		ObjBreakFloorInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));
			Model = ObjUtil::GetModelResource(ms_pModelName, packFile);

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