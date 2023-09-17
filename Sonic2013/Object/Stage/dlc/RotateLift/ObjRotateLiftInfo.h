#pragma once

namespace app
{
	class ObjRotateLiftInfo : public CObjInfo
	{
	private:
		inline static const char* ms_pModelNames[] = { "zdlc02_obj_rollinglift_step", "zdlc02_obj_rollinglift" };

	public:
		inline static const char* ms_pName = "ObjRotateLiftInfo";

		inline static const size_t ms_ModelCount = ARRAYSIZE(ms_pModelNames);

		ObjUtil::ResModelFixedContainer<ms_ModelCount> ModelContainer{};

		ObjRotateLiftInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));
			for (size_t i = 0; i < ModelContainer.Models.size(); i++)
				ModelContainer.Models[i] = ObjUtil::GetModelResource(ms_pModelNames[i], packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}