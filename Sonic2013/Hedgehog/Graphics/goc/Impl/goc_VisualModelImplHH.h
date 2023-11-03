#pragma once

namespace hh::gfx
{
	class AnimMorphTargetControl;
}

namespace app::game
{
	class GOCAnimationSingle;
}

namespace app::animation
{
	class SkeletonBase;
	class Pose;
}

namespace app::fnd
{
	class GOCVisualModel;
	
	class GOCVisualModelImpl
	{
	public:
		class Description; // Compiler workaround

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x00497A40), GOCVisualModelImpl*, GOCVisualModel&, const Description&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCleanup, ASLR(0x00498060), GOCVisualModelImpl*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetMaterialColor, ASLR(0x00497530), GOCVisualModelImpl*, const float*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpGetMatrix, ASLR(0x00498100), const GOCVisualModelImpl*, csl::math::Matrix34*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetPoseUpdateFlag, ASLR(0x00497990), GOCVisualModelImpl*, app::fnd::GOCVisualModel&, bool);

	public:
		hh::gfx::ModelNode* pModelNode{};
		game::GOCAnimationSingle* pAnimation{};
		animation::SkeletonBase* pSkeleton{};
		app::animation::Pose* pPose{};
		csl::fnd::IAllocator* pAllocator{};
		uint Flags{ 0x10000 };
		INSERT_PADDING(8) {};
		csl::math::Matrix34 Transform{};

		GOCVisualModelImpl(csl::fnd::IAllocator* in_pAllocator) : pAllocator(in_pAllocator)
		{

		}

		void GetMatrix(csl::math::Matrix34* out_pMatrix) const
		{
			ms_fpGetMatrix(this, out_pMatrix);
		}

		const csl::math::Aabb& GetBounds() const
		{
			return pModelNode->GetBounds();
		}

		void SetBounds(const csl::math::Aabb& in_rBounds)
		{
			pModelNode->SetBounds(in_rBounds);
		}

		void ChangeModel(GOCVisualModel& in_rModel, const Description& in_rDescription);
		void Setup(GOCVisualModel& in_rModel, const Description& in_rDescription)
		{
			ms_fpSetup(this, in_rModel, in_rDescription);
		}

		void SetPoseUpdateFlag(app::fnd::GOCVisualModel& in_rModel, bool in_update)
		{
			ms_fpSetPoseUpdateFlag(this, in_rModel, in_update);
		}

		void Cleanup()
		{
			ms_fpCleanup(this);
		}

		void SetMaterialColor(const float* in_pColor)
		{
			ms_fpSetMaterialColor(this, in_pColor);
		}

		void DetachAnimation(game::GOCAnimationSingle* in_pAnimation);
		void AttachAnimation(GOCVisualModel* in_pModel, game::GOCAnimationSingle* in_pAnimation);
		hh::gfx::AnimMorphTargetControl* SetMorphAnimation(GOCVisualModel* in_pModel , hh::gfx::res::ResAnimMorphTarget in_resource);

		void DetachAnimation()
		{
			DetachAnimation(pAnimation);
		}

		hh::gfx::res::ResModel GetModelResource()
		{
			if (pModelNode)
			{
				return { &pModelNode->pInstance->Model.ref() };
			}
			else
			{
				return { nullptr };
			}
		}

		hh::gfx::res::ResSkeleton GetSkeletonResource();
	};
}