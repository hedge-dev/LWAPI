#pragma once

namespace app
{
	class EnemyInfo : public CObjInfo
	{
	public:
		const char* pPacfileName{};
		const char* pCueSheetName{};

		void Load(CObjInfoFileLoader& loader) override
		{
			if (pPacfileName)
				loader.Load(pPacfileName, -1);
			
			if (pCueSheetName)
				loader.Load(pCueSheetName, -1);
		}

		hh::ut::PackFile GetEnemyPackfile()
		{
			const auto data = csl::fnd::Singleton<fnd::ResourceManager>::GetInstance()->Get<fnd::ResRawData>(pPacfileName);
			if (!data.IsValid())
				return { nullptr };

			return (data->GetAddress());
		}

		hh::gfx::res::ResModel GetModelResource(const char* in_pName)
		{
			auto packFile = GetEnemyPackfile();
			return ObjUtil::GetModelResource(in_pName, packFile);
		}

		hh::gfx::res::ResSkeleton GetSkeletonResource(const char* in_pName)
		{
			auto packFile = GetEnemyPackfile();
			return ObjUtil::GetSkeletonResource(in_pName, packFile);
		}

		hh::gfx::res::ResAnimSkeleton GetAnimationResource(const char* in_pName)
		{
			auto packFile = GetEnemyPackfile();
			return ObjUtil::GetAnimationResource(in_pName, packFile);
		}

		app::ResCharAnimScript GetAnimationScriptResource(const char* in_pName)
		{
			auto packFile = GetEnemyPackfile();
			return ObjUtil::GetAnimationScriptResource(in_pName, packFile);
		}

		hh::gfx::res::ResAnimTexSrt GetTexSrtAnimationResource(const char* in_pName)
		{
			auto packFile = GetEnemyPackfile();
			return ObjUtil::GetTexSrtAnimationResource(in_pName, packFile);
		}
	};
}