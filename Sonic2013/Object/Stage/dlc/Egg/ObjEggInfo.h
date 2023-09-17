#pragma once

namespace app
{
	class ObjEggInfo : public CObjInfo
	{
	private:
		inline static const char* ms_ModelNames[] = { "zdlc02_obj_yoshiegg_green", "zdlc02_obj_yoshiegg_blue", "zdlc02_obj_yoshiegg_red", "zdlc02_obj_yoshiegg_yellow" };

	public:
		inline static const char* ms_pName = "ObjEggInfo";

		inline static const size_t ms_ModelCount = ARRAYSIZE(ms_ModelNames);

		ObjUtil::ResModelFixedContainer<ms_ModelCount> ModelContainer{};

		ObjEggInfo() { }

		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));
			for (size_t i = 0; i < ModelContainer.Models.size(); i++)
				ModelContainer.Models[i] = ObjUtil::GetModelResource(ms_ModelNames[i], packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}