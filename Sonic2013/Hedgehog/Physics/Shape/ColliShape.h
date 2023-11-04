#pragma once

namespace app::game
{
	class GOCCollider;
	class GOCPhysics;
	struct PhysicsContactPoint;
	struct PhysicsOverlapOutput;

	class ColliShapeBase : public fnd::RefByHandleObject, public fnd::HFrameListener
	{
	public:
		GOCCollider* pOwner;
		GOCPhysics* pPhysicsOwner;
		fnd::HFrame* pFrame{};
		csl::math::Matrix34 Transform{};
		csl::math::Matrix34 UnkMtx{};
		void* pUnk1{};
		void* pUnk2{};
		size_t Unk3{}; // Unk3 from CollisionObjCinfo
		size_t ID{};
		csl::ut::Enum<CollisionShapeType::ShapeType, char> Type{};
		char MotionType{ 2 };
		csl::ut::Bitset<char> Status{};

	public:
		typedef size_t ShapeEventType;

		ColliShapeBase()
		{
			ASSERT_OFFSETOF(ColliShapeBase, pUnk1, 176);
			ASSERT_OFFSETOF(ColliShapeBase, pUnk2, 180);
			ASSERT_OFFSETOF(ColliShapeBase, Unk3, 184);
		}

		virtual bool GetClosestPoint(const ColliShapeBase& in_rShape, PhysicsContactPoint* out_pOutPoint) const = 0;
		virtual bool GetClosestPointSphere(const void* in_rSphere, PhysicsContactPoint* out_pOutPoint) const { return false; }
		virtual bool TestOverlap(const ColliShapeBase& in_rShape, csl::ut::MoveArray<PhysicsOverlapOutput>* out_pOut) { return false; }
		virtual bool InitPlatformInstance(GOCCollider& in_rCollider) { return false; }
		virtual bool InitPlatformInstancePhysics(GOCPhysics& in_rPhysics) { return false; }
		virtual void DestroyPlatformInstance() { }
		virtual void OnShapeEvent(ShapeEventType in_event) { }

		GameObject* GetGameObject() const;
		size_t GetID() const
		{
			return ID;
		}

		void SetEnable(bool in_enable)
		{
			if (in_enable == IsEnable())
				return;

			Status.set(0, in_enable);
			OnShapeEvent(0);
		}

		bool IsEnable() const
		{
			return Status.test(0);
		}

		void MarkUpdate()
		{
			if (pFrame)
				pFrame->MarkUpdate();

			Status.set(2);
		}

		void SetLocalTranslation(const csl::math::Vector3& in_rTranslation)
		{
			UnkMtx.SetTransVector(in_rTranslation);
			MarkUpdate();
		}

		void SetLocalRotation(const csl::math::Quaternion& in_rRotation)
		{
			csl::math::Matrix34 mtx{};
			
			Eigen::Matrix3f rotMtx = in_rRotation.toRotationMatrix();
			mtx.SetColumn(0, (csl::math::Vector3)rotMtx.col(0));
			mtx.SetColumn(1, (csl::math::Vector3)rotMtx.col(1));
			mtx.SetColumn(2, (csl::math::Vector3)rotMtx.col(2));
			
			mtx.SetTransVector(UnkMtx.GetTransVector());
			UnkMtx = mtx;
			
			MarkUpdate();
		}
	};
}
