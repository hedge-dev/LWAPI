#pragma once

namespace app::game
{
	class GOCHudCollider : public fnd::GOComponent
	{
		struct Pane;

	public:
		INSERT_PADDING(3);
		bool m_Unk1{ true };
		INSERT_PADDING(16); //csl::ut::ObjectMoveArray<GOCHudCollider::Pane>
		INSERT_PADDING(4);

	public:
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD772C));
		inline static const char* ms_pGOCHudFamilyID = (const char*)ASLR(0x00D6433C);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x004B1D60), GOCHudCollider*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDtor, ASLR(0x004C0780), GOCHudCollider*);

		GOCHudCollider() : fnd::GOComponent(true)
		{
			ms_fpCtor(this);
		}

		~GOCHudCollider() override
		{
			ms_fpDtor(this);
		}

		const char* GetFamilyID() const override
		{
			return ms_pGOCHudFamilyID;
		}

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		inline static GOComponent* Initialize(csl::fnd::IAllocator* allocator)
		{
			return new(allocator) GOCHudCollider();
		}
	};
}