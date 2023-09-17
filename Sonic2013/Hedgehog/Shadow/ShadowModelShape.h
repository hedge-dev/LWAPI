#pragma once

namespace app::game
{
	class ShadowModelShapeCInfo : public ShadowShapeCInfo
	{
	public:
		fnd::GOCVisualModel* pVisualGoc{};
		app::res::ResShadowModel ShadowModel{ nullptr };
		hh::gfx::res::ResModel Model{};
		float Unk7{};

		ShadowModelShapeCInfo(const hh::gfx::res::ResModel& in_rModel) : ShadowShapeCInfo(3), Model(in_rModel)
		{

		}

		ShadowModelShapeCInfo(fnd::GOCVisualModel* in_pVisualGoc, const app::res::ResShadowModel& in_rShadowModel, float in_unk) : ShadowShapeCInfo(3), pVisualGoc(in_pVisualGoc), ShadowModel(in_rShadowModel), Unk7(in_unk)
		{

		}
	};
}