#pragma once

namespace app::game
{
	class GOCCollider;
	class GOCPhysics;
	struct PhysicsContactPoint;
	struct PhysicsOverlapOutput;

	class ColliShapeBase : public fnd::RefByHandleObject, fnd::HFrameListener
	{
	public:
		GOCCollider* m_pOwner;
		GOCPhysics* m_pPhysicsOwner;
		fnd::HFrame* m_pFrame{};
		csl::math::Matrix34 m_UnkMtx{};
		csl::math::Matrix34 m_Transform{};
		void* m_Unk1{};
		void* m_Unk2{};
		size_t m_Unk3{}; // Unk3 from CollisionObjCinfo
		size_t m_ID{};
		csl::ut::Enum<CollisionShapeType::ShapeType, char> m_Type{};
		char m_MotionType{ 2 };
		csl::ut::Bitset<char> m_Status{};

	public:
		typedef size_t ShapeEventType;

		ColliShapeBase()
		{
			ASSERT_OFFSETOF(ColliShapeBase, m_Unk1, 176);
			ASSERT_OFFSETOF(ColliShapeBase, m_Unk2, 180);
			ASSERT_OFFSETOF(ColliShapeBase, m_Unk3, 184);
		}

		virtual bool GetClosestPoint(const ColliShapeBase& rShape, PhysicsContactPoint* pOutPoint) const = 0;
		virtual bool GetClosestPointSphere(const void* rSphere, PhysicsContactPoint* pOutPoint) const { return false; }
		virtual bool TestOverlap(const ColliShapeBase& rShape, csl::ut::MoveArray<PhysicsOverlapOutput>* pOut) { return false; }
		virtual bool InitPlatformInstance(GOCCollider& collider) { return false; }
		virtual bool InitPlatformInstancePhysics(GOCPhysics& physics) { return false; }
		virtual void DestroyPlatformInstance() { }
		virtual void OnShapeEvent(ShapeEventType event) { }

		GameObject* GetGameObject() const;
		size_t GetID() const
		{
			return m_ID;
		}

		void SetEnable(bool enable)
		{
			m_Status.set(0, enable);
			OnShapeEvent(0);
		}

		bool IsEnable() const
		{
			return m_Status.test(0);
		}
	};
}
