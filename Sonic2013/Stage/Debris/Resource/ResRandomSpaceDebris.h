#pragma once

namespace app::debris
{
	class ResRandomSpaceDebris
	{
	public:
		struct SDesc
		{
			const char* pModelName{};
			hh::ut::PackFile* pPackFile{};
		};

		csl::ut::FixedArray<hh::gfx::res::ResModel, 16> Models{};
		int ModelCount{};

		ResRandomSpaceDebris()
		{

		}

		void Build(SDesc& in_rDescription)
		{
			Models.assign({});
			for (size_t i = 0; i < Models.size(); i++)
			{
				char buffer[64]{};
				csl::fnd::Snprintf(buffer, sizeof(buffer), "%s%02d", in_rDescription.pModelName, i + 1);

				Models[i] = ObjUtil::GetModelResource(buffer, *in_rDescription.pPackFile);
				if (Models[i].IsValid())
					ModelCount = i + 1;
			}
		}
	};
}