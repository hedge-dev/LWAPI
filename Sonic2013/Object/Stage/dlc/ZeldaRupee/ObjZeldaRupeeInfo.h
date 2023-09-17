#pragma once

namespace app
{
	class ObjZeldaRupeeInfo : public CObjInfo
	{
	private:
		inline static const char* ms_pModelNames[] = {"zdlc03_obj_rupee_green01", "zdlc03_obj_rupee_blue01", "zdlc03_obj_rupee_red01", "zdlc03_obj_rupee_purple01", "zdlc03_obj_rupee_gold01"};

	public:
		inline static const char* ms_pName = "ObjZeldaRupeeInfo";

		inline static const size_t ms_ModelCount = ARRAYSIZE(ms_pModelNames);

		hh::gfx::res::ResModel Models[ms_ModelCount]{};

		ObjZeldaRupeeInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));

			for (size_t i = 0; i < ms_ModelCount; i++)
				Models[i] = ObjUtil::GetModelResource(ms_pModelNames[i], packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}