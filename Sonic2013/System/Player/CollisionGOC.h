#pragma once

namespace app::Player
{
	class CPlayer;

	struct SSurfaceInfo
	{
		INSERT_PADDING(48);
	};

	struct STriggerCollisionData
	{
		INSERT_PADDING(8);
		csl::ut::Bitset<byte> Flags{};
		INSERT_PADDING(3);

		bool ForAttack() const
		{
			return Flags.test(0);
		}

		bool ForDefence() const
		{
			return Flags.test(1);
		}
	};

	class CCollision
	{
	private:
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpRaycast, ASLR(0x00861FC0), CCollision*, const csl::math::Vector3&, const csl::math::Vector3&, uint, game::PhysicsRaycastOutput*);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpCheckOnGroundByHitInfo, ASLR(0x008623D0), CCollision*, SGroundInfo*, const csl::math::Vector3&, bool, float);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpSweepCapsule, ASLR(0x00864130), CCollision*, csl::math::Vector3&, const csl::math::Vector3&, const csl::math::Vector3&, const csl::math::Quaternion&, uint, bool, bool);

	public:
		void* Unk1{};
		csl::math::Vector3 Position{};
		csl::math::Vector3 Velocity{};
		csl::math::Vector3 Unk4{};
		csl::math::Vector3 Unk5{};
		float OffsetLength{};
		csl::math::Quaternion Rotation{};
		float MaxSlopeAngle{};
		csl::ut::InplaceMoveArrayAligned16<SSurfaceInfo, 32> SurfaceInfos;
		float Unk9{ 0.001f };
		float Radius{};
		float Height{};
		float SkinWidth{};
		csl::ut::Bitset<byte> Unk13{};
		int CollisionFilter{ 0xC9D6 };
		int Unk14{};

		CCollision(csl::fnd::IAllocator* in_pAllocator) : SurfaceInfos(in_pAllocator)
		{

		}

		csl::math::Quaternion GetRotation() const
		{
			return Rotation;
		}

		void SetRotation(const csl::math::Quaternion& in_rRotation, bool in_unk)
		{
			Rotation = in_rRotation;
		}

		void SetFilterEnale(uint in_filter, bool in_enable)
		{
			if (in_enable)
			{
				CollisionFilter |= in_filter;
			}
			else
			{
				CollisionFilter &= ~in_filter;
			}
		}

		bool Raycast(const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo, uint in_filter, game::PhysicsRaycastOutput* out_pOutput)
		{
			return ms_fpRaycast(this, in_rFrom, in_rTo, in_filter, out_pOutput);
		}

		bool SweepCapsule(csl::math::Vector3& out_rPosition, const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo, const csl::math::Quaternion& in_rRotation, uint in_filter, bool in_unk1, bool in_unk2)
		{
			return ms_fpSweepCapsule(this, out_rPosition, in_rFrom, in_rTo, in_rRotation, in_filter, in_unk1, in_unk2);
		}

		bool CheckOnGroundByHitInfo(SGroundInfo* out_pGroundInfo, const csl::math::Vector3 in_rUpDirection, bool in_unk1, float in_unk2)
		{
			return ms_fpCheckOnGroundByHitInfo(this, out_pGroundInfo, in_rUpDirection, in_unk1, in_unk2);
		}
	};

	class CCollisionGOC : public CGOComponent
	{
	private:
		inline static FUNCTION_PTR(STriggerCollisionData*, __thiscall, ms_fpGetShapeData, ASLR(0x00864AA0), const CCollisionGOC*, const game::ColliShape*);

		inline static const char* ms_pStaticId = (char*)ASLR(0x00DF7E14);

	public:
		int Unk1{};
		int Unk2{};
		CPlayer* pPlayer{};
		csl::ut::Bitset<uint> Unk3{};
		CCollision Collision{ GetAllocator() };
		int Unk4{};
		ut::RefPtr<game::PhysicsRaycastJob> rpPhysicsRaycastJob{};
		INSERT_PADDING(16); //csl::ut::MoveArray<PhysicsRaycastQueue> Queues{ GetAllocator() };
		INSERT_PADDING(16); //csl::ut::MoveArray<STriggerCollisionData> CollisionData{ GetAllocator() };
		int Unk5{};
		int Unk6{ -1 };
		int Unk7{};

		static const char* staticID()
		{
			return ms_pStaticId;
		}

		STriggerCollisionData* GetShapeData(const game::ColliShape* in_pShape) const
		{
			return ms_fpGetShapeData(this, in_pShape);
		}
	};
}
