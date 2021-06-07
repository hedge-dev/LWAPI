#pragma once

namespace app
{
	class ResPhysicsMesh;
}

namespace app::game
{
	class CollisionShapeType
	{
	public:
		enum class ShapeType : char
		{
			TYPE_SPHERE,
			TYPE_BOX,
			TYPE_CAPSULE,
			TYPE_CYLINDER,
			TYPE_MESH,
			TYPE_RIGIDBODY,
			TYPE_INVALID
		};
	};
	
	class CollisionObjCinfo
	{
	public:
		ushort m_Unk1{};
		ushort m_Flags{};
		uint m_Unk2{};
		uint m_Unk3{};
		uint m_ShapeID{};
		fnd::HFrame* m_pParent{};
		uint m_Unk4{};
		uint m_Unk5{};
		uint m_Unk6{};
		csl::math::Vector3 m_Position{ 0,0,0 };
		csl::math::Quaternion m_Rotation{ 0,0,0,1 };

	public:
		void SetLocalPosition(const csl::math::Vector3& rPos)
		{
			m_Position = rPos;
			m_Unk1 |= 1;
		}

		void SetLocalRotation(const csl::math::Quaternion& rRot)
		{
			m_Rotation = rRot;
			m_Unk1 |= 2;
		}
	};

	class ColliShapeCInfo : public CollisionObjCinfo
	{
	protected:
		csl::ut::Enum<CollisionShapeType::ShapeType, char> m_Type{ CollisionShapeType::ShapeType::TYPE_INVALID };

	public:
		char m_MotionType{};
		size_t m_Unk7{};
		size_t m_Unk8{};
	};

	class ColliSphereShapeCInfo : public ColliShapeCInfo
	{
	public:
		float m_Radius{};
		size_t m_Unk9{};

		ColliSphereShapeCInfo()
		{
			m_Type = CollisionShapeType::ShapeType::TYPE_SPHERE;
		}
	};

	class ColliBoxShapeCInfo : public ColliShapeCInfo
	{
	public:
		csl::math::Vector3 m_Size{ 0,0,0 };
		
		ColliBoxShapeCInfo()
		{
			m_Type = CollisionShapeType::ShapeType::TYPE_BOX;
		}
	};

	class ColliCapsuleShapeCInfo : public ColliShapeCInfo
	{
	public:
		float m_Radius{};
		float m_Height{};

		ColliCapsuleShapeCInfo()
		{
			m_Type = CollisionShapeType::ShapeType::TYPE_CAPSULE;
		}
	};

	class ColliCylinderShapeCInfo : public ColliShapeCInfo
	{
	public:
		float m_Radius{};
		float m_Height{};

		ColliCylinderShapeCInfo()
		{
			m_Type = CollisionShapeType::ShapeType::TYPE_CYLINDER;
		}
	};

	class ColliMeshShapeCInfo : public ColliShapeCInfo
	{
	public:
		ResPhysicsMesh* m_pMesh{};

		ColliMeshShapeCInfo()
		{
			m_Type = CollisionShapeType::ShapeType::TYPE_MESH;
		}
	};

	class alignas(16) CharacterRigidBodyCinfo : public CollisionObjCinfo
	{
	public:
		float m_Unk7{};
		float m_Unk8{};
		float m_Unk9{ 0.78539819f };
		float m_Unk10{ 1000.0f };
		float m_Unk11{ 1 };
	};
	
	class GOCColliderListener
	{
	public:
		virtual ~GOCColliderListener() = default;
		virtual void OnEnter(void* rHitEventCollision) {}
		virtual void OnStay(void* rStayTrigger) {}
		virtual void OnLeave(void* rLeaveEventCollision) {}
	};

	class GOCCollider;
	class GOCPhysics;
	class PhysicsWorld;
	struct PhysicsContactPoint;
	struct PhysicsOverlapOutput;
	
	class ColliShapeBase : public fnd::RefByHandleObject, fnd::HFrameListener
	{
	protected:
		GOCCollider* m_pOwner;
		GameObject* m_pObj;
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
		
		virtual bool GetClosestPoint(const ColliShapeBase& rShape, PhysicsContactPoint* pOutPoint) const = 0;
		virtual bool GetClosestPointSphere(const void* rSphere, PhysicsContactPoint* pOutPoint) const
		{
			ASSERT_OFFSETOF(ColliShapeBase, m_Unk1, 176);
			ASSERT_OFFSETOF(ColliShapeBase, m_Unk2, 180);
			ASSERT_OFFSETOF(ColliShapeBase, m_Unk3, 184);
			return false;
		}

		virtual bool TestOverlap(const ColliShapeBase& rShape, csl::ut::MoveArray<PhysicsOverlapOutput>* pOut)
		{
			return false;
		}

		bool InitPlatformInstance(GOCCollider& collider)
		{
			return false;
		}

		bool InitPlatformInstancePhysics(GOCPhysics& physics)
		{
			return false;
		}

		void DestroyPlatformInstance()
		{
			
		}

		void OnShapeEvent(ShapeEventType event)
		{
			
		}

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

	class ColliShape : public ColliShapeBase {};
	
	class GOCCollider : public fnd::GOComponent
	{
	public:
		struct Description
		{
			size_t m_ShapeCount;
		};
		
	protected:
		// app::game::ColliShape
		csl::ut::MoveArray<ColliShape*> m_Shapes{GetAllocator()};
		csl::ut::MoveArray<GOCColliderListener*> m_Listeners{GetAllocator()};
		fnd::HFrame* m_pFrame{};
		PhysicsWorld* m_pPhysicsWorld{};

	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateShape, ASLR(0x004B6C50), GOCCollider* pThis, const ColliShapeCInfo& rInfo);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateCharacterRigidBody, ASLR(0x004B6490), GOCCollider* pThis, const CharacterRigidBodyCinfo& rInfo);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD75A4));

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		void Setup(const Description& rDesc)
		{
			m_Shapes.change_allocator(GetAllocator());
			m_Shapes.clear();
			m_Shapes.reserve(rDesc.m_ShapeCount);
		}

		void CreateShape(const ColliShapeCInfo& rInfo)
		{
			ms_fpCreateShape(this, rInfo);
		}

		void CreateCharacterRigidBody(const CharacterRigidBodyCinfo& rInfo)
		{
			ms_fpCreateCharacterRigidBody(this, rInfo);
		}

		ColliShape* GetShape() const
		{
			return m_Shapes.front();
		}

		ColliShape* FindColliShape(size_t id) const
		{
			for (auto& shape : m_Shapes)
			{
				if (shape->GetID() == id)
					return shape;
			}

			return nullptr;
		}

		void SetEnable(bool enable)
		{
			for (auto& shape : m_Shapes)
			{
				shape->SetEnable(enable);
			}
		}
	};
}