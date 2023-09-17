#pragma once

namespace app::Player
{
	class GOCReferenceHolder;

	class GOCCollector : public fnd::GOComponent
	{
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdateChangeRequest, ASLR(0x008F2E00), GOCCollector*);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FEF324));

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		void Setup(GameObject* pOwner)
		{
			FUNCTION_PTR(void, __thiscall, fp_Setup, ASLR(0x008F2D50), GOCCollector*, GameObject*);
			fp_Setup(this, pOwner);
		}

		GOCReferenceHolder& GetHolder(size_t num)
		{
			FUNCTION_PTR(GOCReferenceHolder&, __thiscall, fp_GetHolder, ASLR(0x008F2E40), GOCCollector*, size_t);
			return fp_GetHolder(this, num);
		}

		GOCReferenceHolder& GetCurrentHolder()
		{
			FUNCTION_PTR(GOCReferenceHolder&, __thiscall, fpGetCurrentHolder, ASLR(0x008F2E60), GOCCollector*);
			return fpGetCurrentHolder(this);
		}

		void UpdateChangeRequest()
		{
			ms_fpUpdateChangeRequest(this);
		}
	};

	class GOCReferenceHolderUnit
	{
	public:
		fnd::HFrame* m_pFrame{};
		ut::RefPtr<fnd::GOCVisualModel> m_rpModel{};
		ut::RefPtr<game::GOCAnimationScript> m_rpAnimScript{};
		INSERT_PADDING(4) {};
		INSERT_PADDING(16) {}; // csl::ut::ObjectMoveArray<Effect::CEffectHandle>
		INSERT_PADDING(16) {}; // csl::ut::MoveArray<game::ShadowShape>
		GOCReferenceHolder* m_pOwner{};
		csl::ut::Bitset<hhUchar, 8> m_Unk1{};

		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddGOCAnimation, ASLR(0x008F41B0), GOCReferenceHolderUnit*, game::GOCAnimationScript*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddGOCModel, ASLR(0x008F40D0), GOCReferenceHolderUnit*, fnd::GOCVisualModel*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetOwner, ASLR(0x008F3FA0), GOCReferenceHolderUnit*, GOCReferenceHolder*);
		inline static FUNCTION_PTR(hh::eff::CInstanceHandle<hh::eff::CEffectInstance>&, __thiscall, ms_fpCreateEffect, ASLR(0x008F3BD0), GOCReferenceHolderUnit*, const game::EffectCreateInfo&);
		inline static FUNCTION_PTR(hh::eff::CInstanceHandle<hh::eff::CEffectInstance>&, __thiscall, ms_fpCreateEffectFollow, ASLR(0x008F4520), GOCReferenceHolderUnit*, hh::eff::CInstanceHandle<hh::eff::CEffectInstance>*, const game::EffectCreateInfo&);

		void SetOwner(GOCReferenceHolder* in_pOwner)
		{
			ms_fpSetOwner(this, in_pOwner);
		}

		void AddGOCAnimation(game::GOCAnimationScript* in_pScript)
		{
			ms_fpAddGOCAnimation(this, in_pScript);
		}

		void AddGOCModel(fnd::GOCVisualModel* in_pModel)
		{
			ms_fpAddGOCModel(this, in_pModel);
		}

		hh::eff::CInstanceHandle<hh::eff::CEffectInstance>& CreateEffect(const game::EffectCreateInfo& in_rCreateInfo)
		{
			return ms_fpCreateEffect(this, in_rCreateInfo);
		}

		hh::eff::CInstanceHandle<hh::eff::CEffectInstance>& CreateEffectFollow(hh::eff::CInstanceHandle<hh::eff::CEffectInstance>* out_pEffect, const game::EffectCreateInfo& in_rCreateInfo)
		{
			return ms_fpCreateEffectFollow(this, out_pEffect, in_rCreateInfo);
		}
	};

	class GOCReferenceHolder
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x008F3460), GOCReferenceHolder*, GameObject*, csl::fnd::IAllocator*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetupUnitNum, ASLR(0x008F37A0), GOCReferenceHolder*, size_t);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetBlinkVisible, ASLR(0x008F3A50), GOCReferenceHolder*, bool);

	public:
		csl::ut::InplaceObjectMoveArray<GOCReferenceHolderUnit, 1> m_Units{ nullptr };
		INSERT_PADDING(8) {};
		bool m_Unk1{ true };
		ushort m_Unk2{};
		uint m_Unk3{};
		csl::fnd::IAllocator* m_pAllocator{};
		INSERT_PADDING(4) {};

		GOCReferenceHolder()
		{

		}

		void Setup(GameObject* pOwner, csl::fnd::IAllocator* pAlloc)
		{
			ms_fpSetup(this, pOwner, pAlloc);
		}

		void SetupUnitNum(size_t num)
		{
			ms_fpSetupUnitNum(this, num);
		}

		void SetBlinkVisible(bool in_isVisible)
		{
			ms_fpSetBlinkVisible(this, in_isVisible);
		}

		GOCReferenceHolderUnit& GetUnit(size_t num)
		{
			return m_Units[num];
		}
	};
}