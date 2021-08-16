#pragma once

namespace app::Player
{
	class CPlayerVisual;

	enum BodyMode : size_t
	{
		Human = 0,
		Spin = 1,
		SuperSonic = 2,
		PhantomSpin = 3,
		PhantomLaser = 4,
		PhantomRocket = 5,
		PhantomAsteroid = 6,
		PhantomEagle = 7,
		PhantomRhythm = 9,
		PhantomBomb = 10,
		PhantomHover = 11,
		PhantomQuake = 12
	};

	struct SVisualCinfo
	{
		float m_Unk1{};
		INSERT_PADDING(76) {};
		size_t m_PlayerNum{ 0 };
	};

	class CVisualGOC;
	class CVisualLocater;

	class CVisualLocaterManager : public fnd::ReferencedObject
	{
	public:
		CVisualGOC* m_pVisual{};
		CVisualLocater* m_pLocater{};
		INSERT_PADDING(0x14C) {};
		csl::math::Matrix34 m_Transform{};
		INSERT_PADDING(16) {};

		CVisualLocaterManager()
		{

		}
	};

	class CVisualGOC : public CGOComponent
	{
		inline static const char* ms_pStaticId = (char*)ASLR(0x00E01360);
	
	public:

		typedef void __fastcall ChangeFunc(CVisualGOC*);
		template<BodyMode Mode>
		struct ChangeFuncHelper
		{
		public:
			static ChangeFunc* ms_fpChangeVisualFunc;
		};

		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x008EF8E0), CVisualGOC*, GameObject3D*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDtor, ASLR(0x008EFA90), CVisualGOC*, size_t);
		inline static FUNCTION_PTR(game::GOCAnimationScript*, __thiscall, ms_fpGetHumanAnimationPtr, ASLR(0x008EF640), const CVisualGOC*);

		INSERT_PADDING(24) {};
		csl::ut::ObjectMoveArray<ut::RefPtr<CPlayerVisual>> m_Visuals{ GetAllocator() };
		ut::RefPtr<CPlayerVisual> m_rpCurrentVisual{};
		ut::RefPtr<CPlayerVisual> m_rpHumanVisual{};
		ut::RefPtr<CVisualLocaterManager> m_rpLocatorManager{};
		INSERT_PADDING(8) {};

		static const char* staticID()
		{
			return ms_pStaticId;
		}

		CVisualGOC(GameObject3D* pObj)
		{
			ms_fpCtor(this, pObj);
		}

		~CVisualGOC()
		{
			ms_fpDtor(this, 0);
		}

		virtual void Initialize(const SVisualCinfo& rInfo) {};
		virtual void Finalize() {};

		template<BodyMode Mode>
		void ChangeVisual()
		{
			ChangeFuncHelper<Mode>::ms_fpChangeVisualFunc(this);
		}

		game::GOCAnimationScript* GetHumanAnimationPtr() const
		{
			if (!m_rpHumanVisual && !m_rpHumanVisual->m_pGOCHolder)
				return nullptr;

			return m_rpHumanVisual->m_pGOCHolder->GetUnit(0).m_rpAnimScript.get();
		}

		void ChangeAnimation(const char* pName)
		{
			auto* pAnim = GetHumanAnimationPtr();
			if (pAnim)
				pAnim->ChangeAnimation(pName);
		}
		
		CPlayerVisual* GetCurrentVisual() const
		{
			return m_rpCurrentVisual.get();
		}

		void SetHumanVisual(CPlayerVisual* pVisual)
		{
			m_rpHumanVisual = pVisual;
		}

		void ChangeVisual(BodyMode mode)
		{
#define MODE_CASE(MODE) case MODE: ChangeVisual<MODE>(); break;
			switch (mode)
			{
			case Human:
			{
				ChangeVisual<Human>();
				SetHumanVisual(GetCurrentVisual());
				break;
			}
			MODE_CASE(Spin)
				MODE_CASE(SuperSonic)
				MODE_CASE(PhantomSpin)
				MODE_CASE(PhantomLaser)
				MODE_CASE(PhantomRocket)
				MODE_CASE(PhantomAsteroid)
				MODE_CASE(PhantomEagle)
				MODE_CASE(PhantomRhythm)
				MODE_CASE(PhantomBomb)
				MODE_CASE(PhantomHover)
				MODE_CASE(PhantomQuake)

			default:
				break;
			}
#undef MODE_CASE
		}
	};

#define DEFINE_CHANGE_FUNC(BODY_MODE, ADDRESS) inline CVisualGOC::ChangeFunc* CVisualGOC::ChangeFuncHelper<BODY_MODE>::ms_fpChangeVisualFunc = reinterpret_cast<ChangeFunc*>(ADDRESS);

	DEFINE_CHANGE_FUNC(Human, ASLR(0x0085BDF0))
		DEFINE_CHANGE_FUNC(Spin, ASLR(0x0085BE20))
		DEFINE_CHANGE_FUNC(SuperSonic, ASLR(0x0085C000))
		DEFINE_CHANGE_FUNC(PhantomSpin, ASLR(0x0085BEE0))
		DEFINE_CHANGE_FUNC(PhantomLaser, ASLR(0x0085BE50))
		DEFINE_CHANGE_FUNC(PhantomRocket, ASLR(0x0085BEB0))
		DEFINE_CHANGE_FUNC(PhantomAsteroid, ASLR(0x0085BE80))
		DEFINE_CHANGE_FUNC(PhantomEagle, ASLR(0x0085BF10))
		DEFINE_CHANGE_FUNC(PhantomRhythm, ASLR(0x0085BF40))
		DEFINE_CHANGE_FUNC(PhantomBomb, ASLR(0x0085BF70))
		DEFINE_CHANGE_FUNC(PhantomHover, ASLR(0x0085BFA0))
		DEFINE_CHANGE_FUNC(PhantomQuake, ASLR(0x0085BFD0))

#undef DEFINE_CHANGE_FUNC

		class CEffectGOC : public CGOComponent
	{
	public:
		INSERT_PADDING(64);

		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x008EE920), CEffectGOC*, GameObject3D*, CVisualGOC*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDtor, ASLR(0x008EEEE0), CEffectGOC*, size_t);

		CEffectGOC(GameObject3D* pObj, CVisualGOC* pVisual)
		{
			ms_fpCtor(this, pObj, pVisual);
		}

		~CEffectGOC()
		{
			ms_fpDtor(this, 0);
		}

		void Initialize()
		{
			FUNCTION_PTR(void, __thiscall, fp_Initialize, ASLR(0x008EE6D0), CEffectGOC*, void*);
			fp_Initialize(this, nullptr);
		}
	};
}
