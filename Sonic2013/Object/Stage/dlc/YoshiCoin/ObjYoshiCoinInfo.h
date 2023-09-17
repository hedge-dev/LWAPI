#pragma once

namespace app
{
	class ObjYoshiCoinInfo : public CObjInfo
	{
	private:
		inline static const char* ms_ModelName = "zdlc02_obj_yoshicoin";

	public:
		inline static const char* ms_pName = "ObjYoshiCoinInfo";

		hh::gfx::res::ResModel Model{};

		ObjYoshiCoinInfo() { }

	protected:
		void Initialize(GameDocument& in_rDocument) override
		{
			auto packFile = ObjUtil::GetPackFile(ObjUtil::GetStagePackName(in_rDocument));
			Model = ObjUtil::GetModelResource(ms_ModelName, packFile);
		}

		const char* GetInfoName() override
		{
			return ms_pName;
		}
	};
}