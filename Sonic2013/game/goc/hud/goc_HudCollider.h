#pragma once

namespace app::game
{
	class GOCHudCollider : public fnd::GOComponent
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x004B1D60), GOCHudCollider*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDtor, ASLR(0x004C0780), GOCHudCollider*);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD772C));
		inline static const char* ms_pGOCHudFamilyID = (const char*)ASLR(0x00D6433C);

		struct Pane;

	public:
		INSERT_PADDING(3);
		bool Unk1{ true };
		INSERT_PADDING(16); //csl::ut::ObjectMoveArray<GOCHudCollider::Pane>
		INSERT_PADDING(4);

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

		inline static GOComponent* Initialize(csl::fnd::IAllocator* in_pAllocator)
		{
			return new(in_pAllocator) GOCHudCollider();
		}
	};
}