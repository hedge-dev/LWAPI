#pragma once

namespace app::game
{
	class GravityEffect;
	enum GravityType : uint8
	{
		eGravityType_ConcaveBox,
		eGravityType_Constant,
		eGravityType_Sphere,
		eGravityType_Hemisphere,
		eGravityType_OutsideCylinderSpline,
		eGravityType_InsideCylinderSpline,
		eGravityType_OutsidePrismSpline,
		eGravityType_InsidePrismSpline,
		eGravityType_FaceSpline = 11,
		eGravityType_SvSpline = 12,
	};

	class GravityField : public fnd::GOComponent, public fnd::HFrameListener
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpReadSpawner, ASLR(0x004CD480), GravityField*, const void*);

	public:
		csl::ut::Enum<GravityType, uint8> Type;
		csl::ut::Bitset<uint8> Unk1{};
		const char Unk2{};
		csl::ut::Bitset<uint8> Unk3{};
		int Unk4{};
		int Unk5{};
		int Unk6{};
		int Unk7{};
		int Unk8{};
		int Unk9{};
		GravityField* pField{ this };
		fnd::GOCTransform* pTransform{};
		csl::ut::LinkList<GravityEffect> Unk12{};

		GravityField(game::GravityType in_type) : GOComponent()
		{
			Type = in_type;
		}

		const char* GetFamilyID() const override
		{
			return "GravityField";
		}

		virtual const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const
		{
			return nullptr;
		}
		
		virtual bool GetDirection(const csl::math::Vector3& in_rVec, csl::math::Vector3* out_pOutput) const = 0;
		virtual void GetAabb(csl::math::Aabb* out_pOutput) const = 0;
		virtual void IntersectPoint(const csl::math::Vector3& in_rPoint, float in_unk, float* out_pOutput) = 0;
		
		virtual SimpleGravityEffect* CreateGravityEffect(csl::fnd::IAllocator* in_pAllocator)
		{
			auto* pEffect = new (in_pAllocator) SimpleGravityEffect();
			if (!pEffect)
				return { nullptr };
		
			return pEffect;
		}
		
		void ReadSpawner(const void* in_pData)
		{
			ms_fpReadSpawner(this, in_pData);
		}

		GravityType GetType() const
		{
			return Type;
		}
	};
}
