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
		uint m_Unk4{};
		fnd::HFrame* m_pParent{};
		uint m_Unk5{};
		uint m_Unk6{};
		uint m_Unk7{};
		csl::math::Vector3 m_Position{ 0,0,0 };
		csl::math::Quaternion m_Rotation{ 0,0,0,1 };

	public:
		void SetLocalPosition(const csl::math::Vector3& rPos)
		{
			m_Position = rPos;
			m_Flags |= 1;
		}

		void SetLocalRotation(const csl::math::Quaternion& rRot)
		{
			m_Rotation = rRot;
			m_Flags |= 2;
		}
	};

	class ColliShapeCInfo : public CollisionObjCinfo
	{
	protected:
		csl::ut::Enum<CollisionShapeType::ShapeType, char> m_Type{ CollisionShapeType::ShapeType::TYPE_INVALID };

	public:
		char m_MotionType{};
		size_t m_Unk8{};
		size_t m_Unk9{};
	};

	class ColliSphereShapeCInfo : public ColliShapeCInfo
	{
	public:
		float m_Radius{};
		size_t m_Unk10{};

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
		float m_Unk8;
		float m_Unk9;
		float m_Unk10{ 0.78539819f };
		float m_Unk11{ 1000.0f };
		float m_Unk12{ 1 };
	};
	
	class GOCColliderListener
	{
	public:
		virtual ~GOCColliderListener() = default;
		virtual void OnEnter(void* rHitEventCollision) {}
		virtual void OnStay(void* rStayTrigger) {}
		virtual void OnLeave(void* rLeaveEventCollision) {}
	};
	
	class GOCCollider : public fnd::GOComponent
	{
	public:
		struct Description
		{
			size_t m_ShapeCount;
		};
		
	protected:
		// app::game::ColliShape
		csl::ut::MoveArray<void*> m_Shapes{GetAllocator()};
		csl::ut::MoveArray<GOCColliderListener*> m_Listeners{GetAllocator()};
		fnd::HFrame* m_pFrame{};
		void* m_Unk2{};

	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateShape, ASLR(0x004B6C50), GOCCollider* pThis, const ColliShapeCInfo& rInfo);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateCharacterRigidBody, ASLR(0x004B6490), GOCCollider* pThis, const CharacterRigidBodyCinfo& rInfo);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD75A4));

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		void Setup(Description& rDesc)
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
	};
}