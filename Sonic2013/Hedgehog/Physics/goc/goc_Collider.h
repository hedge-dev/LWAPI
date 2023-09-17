#pragma once

namespace app::game
{	
	class GOCColliderListener;

	class GOCCollider : public fnd::GOComponent
	{
	public:
		struct Description
		{
			size_t m_ShapeCount;
		};
		
		// app::game::ColliShape
		csl::ut::MoveArray<ColliShape*> m_Shapes{ GetAllocator() };
		csl::ut::MoveArray<GOCColliderListener*> m_Listeners{ GetAllocator() };
		fnd::HFrame* m_pFrame{};
		CPhysicsWorld* m_pPhysicsWorld{};

	public:
		inline static FUNCTION_PTR(ColliShape*, __thiscall, ms_fpCreateShape, ASLR(0x004B6C50), GOCCollider* pThis, const ColliShapeCInfo& rInfo);
		inline static FUNCTION_PTR(CharacterRigidBody*, __thiscall, ms_fpCreateCharacterRigidBody, ASLR(0x004B6490), GOCCollider* pThis, const CharacterRigidBodyCinfo& rInfo);
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

		ColliShape* CreateShape(const ColliShapeCInfo& rInfo)
		{
			return ms_fpCreateShape(this, rInfo);
		}

		CharacterRigidBody* CreateCharacterRigidBody(const CharacterRigidBodyCinfo& rInfo)
		{
			return ms_fpCreateCharacterRigidBody(this, rInfo);
		}

		ColliShape* GetShape() const
		{
			return m_Shapes.front();
		}

		ColliShape* GetShapeById(size_t id) const
		{
			if (m_Shapes.empty())
				return { nullptr };
			
			if (auto* pShape = FindColliShape(id))
				return pShape;
		
			return { nullptr };
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

	class GOCColliderListener
	{
	public:
		virtual ~GOCColliderListener() = default;
		virtual void OnEnter(void* rHitEventCollision) {}
		virtual void OnStay(void* rStayTrigger) {}
		virtual void OnLeave(void* rLeaveEventCollision) {}
	};
}