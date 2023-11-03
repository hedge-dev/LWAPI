#pragma once
#pragma push_macro("GetObject")
#undef GetObject

namespace app::game
{	
	class GravityManager;

	class GravityMotionType
	{
	public:
		enum MotionType;
	};

	class GravityPhantom
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x004DCE930), GravityPhantom*);

	public:
		GravityManager* pGravityManager{};
		csl::ut::Bitset<byte> Unk2{};
		csl::ut::Enum<GravityMotionType::MotionType, byte> Type{};
		int Unk8{};
		int Unk9{};
		int Unk3{};
		int Unk4{};
		GravityEffect* pGravityEffect{};
		fnd::Handle<GravityField> GravityObject{};
		csl::math::Vector3 Position{};
		csl::math::Vector3 GravityDirection{};
		float Unk6{ 0.1f };
		int Unk7{};

		GravityField* GetObject() const
		{
			return GravityObject.Get();
		}

		csl::math::Vector3 GetPosition() const
		{
			return Position;
		}

		void SetPosition(const csl::math::Vector3& in_rVector)
		{
			Position = in_rVector;

			Unk2.set(0);
			Unk2.set(0);
		}

		void Update()
		{
			ms_fpUpdate(this);
		}
	};

	class GOCGravity : public fnd::GOComponent
	{
	public:
		typedef size_t MotionType;

		class Description
		{
		public:
			MotionType Type{};
			float Unk2{ 0.1f };
			int Unk3{};
			bool Unk4{};
			csl::math::Vector3 Unk5{ 0.0f, -1.0f, 0.0f };
		};
		
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x004BF2C0), GOCGravity*, const Description&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSimpleSetup, ASLR(0x004BF5C0), GameObject*, MotionType);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD76D8));
		
		public:
		int Unk1{};
		csl::math::Vector3 GravityDirection{};
		GravityPhantom Phantom{};
		int Unk3{};
		bool Unk4{};
		int Unk5{};
		int Unk6{};

		void Setup(const Description& in_rDescription)
		{
			ms_fpSetup(this, in_rDescription);
		}
		
		static void SimpleSetup(GameObject* in_pObject, MotionType in_type)
		{
			if (!in_pObject)
				return;

			auto* pGravity = in_pObject->GetComponent<GOCGravity>();
			if (!pGravity)
				return;

			game::GOCGravity::Description description{};
			description.Type = in_type;

			pGravity->Setup(description);
		}

		csl::math::Vector3 GetGravityDirection() const
		{
			if (Unk4)
				return Phantom.GravityDirection;
		
			return GravityDirection;
		}

		bool GetGravityDirection(const csl::math::Vector3& in_rVector, csl::math::Vector3* out_pDirection) const
		{
			auto* pGravityField = GetGravityField();
			if (!pGravityField)
				return false;

			return pGravityField->GetDirection(in_rVector, out_pDirection);
		}

		GravityField* GetGravityField() const
		{
			if (Unk4)
			{
				return Phantom.GetObject();
			}

			return { nullptr };
		}

		GravityPhantom* GetGravityPhantom()
		{
			return &Phantom;
		}

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}
	};
}

#pragma pop_macro("GetObject")