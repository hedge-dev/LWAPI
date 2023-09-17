#pragma once

namespace app
{
	class ObjYoshiGoalInfo : public CObjInfo
	{
	private:
		inline static const char* ms_OffModelNames[] = { "zdlc02_obj_goalA_off", "zdlc02_obj_goalB_off" };
		inline static const char* ms_OnModelNames[] = { "zdlc02_obj_goalA_on", "zdlc02_obj_goalB_on" };

	public:
		inline static const char* ms_pName = "ObjYoshiGoalInfo";

		inline static const size_t ms_OffModelCount = ARRAYSIZE(ms_OffModelNames);
		inline static const size_t ms_OnModelCount = ARRAYSIZE(ms_OnModelNames);

		ObjUtil::ResModelFixedContainer<ms_OffModelCount> OffModelContainer{};
		ObjUtil::ResModelFixedContainer<ms_OnModelCount> OnModelContainer{};
		hh::gfx::res::ResAnimSkeleton Animation{};

		ObjYoshiGoalInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));
			for (size_t i = 0; i < OffModelContainer.Models.size(); i++)
				OffModelContainer.Models[i] = ObjUtil::GetModelResource(ms_OffModelNames[i], packFile);
			
			for (size_t i = 0; i < OnModelContainer.Models.size(); i++)
				OnModelContainer.Models[i] = ObjUtil::GetModelResource(ms_OnModelNames[i], packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}