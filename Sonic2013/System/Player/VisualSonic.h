#pragma once

namespace app::Player
{
	inline void RegisterBodyModel(GOCReferenceHolderUnit& in_rRefHolderGocUnit, fnd::GOCVisualModel* in_pVisualModelGoc, hh::gfx::res::ResModel in_model, hh::gfx::res::ResSkeleton in_skeleton, uint in_unk)
	{
		fnd::GOCVisualModel::Description description{};
		description.Model = in_model;
		if (in_skeleton.IsValid())
			description.Skeleton = in_skeleton;

		description.Unk1 = in_unk;

		in_pVisualModelGoc->Setup(description);
		in_pVisualModelGoc->SetLocalScale({ 0.9f, 0.9f, 0.9f });
		in_rRefHolderGocUnit.AddGOCModel(in_pVisualModelGoc);
	}

	inline void RegisterSonicIK(CPlayer& in_rPlayer, GOCReferenceHolderUnit& in_rRefHolderGocUnit, hh::gfx::res::ResSkeleton in_skeleton)
	{
		FUNCTION_PTR(void, __cdecl, ms_fpRegisterSonicIK, ASLR(0x008FE080), CPlayer&, GOCReferenceHolderUnit&, hh::gfx::res::ResSkeleton);

		ms_fpRegisterSonicIK(in_rPlayer, in_rRefHolderGocUnit, in_skeleton);
	}

	class CVisualSonic : public CVisualHuman
	{
	public:
		CVisualSonic(CPlayer* in_pPlayer, CVisualGOC* in_pVisualGoc) : CVisualHuman(in_pPlayer, in_pVisualGoc)
		{

		}

		static void RegisterResource(CPlayer& in_rPlayer, GOCReferenceHolder& in_rRefHolderGoc, uint in_unk, bool in_isZelda)
		{
			in_rRefHolderGoc.SetupUnitNum(1);
			auto& refHolderGocUnit = in_rRefHolderGoc.GetUnit(0);

			auto* pSonicInfo = VisualUtil::GetObjectInfo<SonicInfo>(*in_rPlayer.GetDocument());
			if (in_isZelda)
			{
				auto* pZeldaSonicInfo = VisualUtil::GetObjectInfo<SonicZeldaInfo>(*in_rPlayer.GetDocument());

				auto* pVisualModel = fnd::GOComponent::CreateSingle<fnd::GOCVisualModel>(in_rPlayer);
				RegisterBodyModel(refHolderGocUnit, pVisualModel, pZeldaSonicInfo->Model, pSonicInfo->Skeleton, in_unk);
			}
			else
			{
				auto* pVisualModel = fnd::GOComponent::CreateSingle<fnd::GOCVisualModel>(in_rPlayer);
				RegisterBodyModel(refHolderGocUnit, pVisualModel, pSonicInfo->Model, pSonicInfo->Skeleton, in_unk);
			}

			auto* pAnimationScript = fnd::GOComponent::CreateSingle<game::GOCAnimationScript>(in_rPlayer);
			pAnimationScript->Setup({ &pSonicInfo->AnimationContainer });

			refHolderGocUnit.AddGOCAnimation(pAnimationScript);
			RegisterSonicIK(in_rPlayer, refHolderGocUnit, pSonicInfo->Skeleton);
		}
	};
}