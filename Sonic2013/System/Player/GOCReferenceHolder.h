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
		INSERT_PADDING(20) {};
		csl::fnd::IAllocator* m_pAllocator{};
		INSERT_PADDING(24) {};

		void SetOwner(GOCReferenceHolder* pOwner)
		{
			FUNCTION_PTR(void, __thiscall, fp_SetOwner, ASLR(0x008F3FA0), GOCReferenceHolderUnit*, GOCReferenceHolder*);
			fp_SetOwner(this, pOwner);
		}
	};

	class GOCReferenceHolder
	{
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
			FUNCTION_PTR(void, __thiscall, fp_Setup, ASLR(0x008F3460), GOCReferenceHolder*, GameObject*, csl::fnd::IAllocator*);
			fp_Setup(this, pOwner, pAlloc);
		}

		void SetupUnitNum(size_t num)
		{
			FUNCTION_PTR(void, __thiscall, fp_SetupUnitNum, ASLR(0x008F37A0), GOCReferenceHolder*, size_t);
			fp_SetupUnitNum(this, num);
		}

		GOCReferenceHolderUnit& GetUnit(size_t num)
		{
			return m_Units[num];
		}
	};
}