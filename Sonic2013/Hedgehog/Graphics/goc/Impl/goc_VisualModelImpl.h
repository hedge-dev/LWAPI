#pragma once

namespace app::game
{
	class GOCAnimationSingle;
}

namespace app::fnd
{
	class GOCVisualModel;
	class GOCVisualModelImpl
	{
	public:
		class Description; // Compiler workaround

		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x00497A40), GOCVisualModelImpl*, GOCVisualModel&, const Description&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCleanup, ASLR(0x00498060), GOCVisualModelImpl*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetMaterialColor, ASLR(0x00497530), GOCVisualModelImpl*, const float*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpGetMatrix, ASLR(0x00498100), const GOCVisualModelImpl*, csl::math::Matrix34*);

		hh::gfx::ModelNode* m_pModelNode{};
		game::GOCAnimationSingle* m_pAnimation{};
		INSERT_PADDING(8) {};
		csl::fnd::IAllocator* m_pAllocator{};
		uint m_Flags{ 0x10000 };
		INSERT_PADDING(8) {};
		csl::math::Matrix34 m_Transform{};

		GOCVisualModelImpl(csl::fnd::IAllocator* in_pAllocator) : m_pAllocator(in_pAllocator)
		{

		}

		void GetMatrix(csl::math::Matrix34* out_matrix) const
		{
			ms_fpGetMatrix(this, out_matrix);
		}

		const csl::math::Aabb& GetBounds() const
		{
			return m_pModelNode->GetBounds();
		}

		void SetBounds(const csl::math::Aabb& in_bounds)
		{
			m_pModelNode->SetBounds(in_bounds);
		}

		void ChangeModel(GOCVisualModel& in_model, const Description& in_description);
		void Setup(GOCVisualModel& in_model, const Description& in_description)
		{
			ms_fpSetup(this, in_model, in_description);
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
	};
}