#pragma once

namespace app::game
{	
	class GOCColliderListener;

	class GOCCollider : public fnd::GOComponent
	{
	private:
		inline static FUNCTION_PTR(ColliShape*, __thiscall, ms_fpCreateShape, ASLR(0x004B6C50), GOCCollider* pThis, const ColliShapeCInfo& rInfo);
		inline static FUNCTION_PTR(CharacterRigidBody*, __thiscall, ms_fpCreateCharacterRigidBody, ASLR(0x004B6490), GOCCollider* pThis, const CharacterRigidBodyCinfo& rInfo);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD75A4));

	public:
		struct Description
		{
			size_t ShapeCount;
		};
		
		// app::game::ColliShape
		csl::ut::MoveArray<ColliShape*> Shapes{ GetAllocator() };
		csl::ut::MoveArray<GOCColliderListener*> Listeners{ GetAllocator() };
		fnd::HFrame* pFrame{};
		CPhysicsWorld* pPhysicsWorld{};

		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		void Setup(const Description& in_rDesc)
		{
			Shapes.change_allocator(GetAllocator());
			Shapes.clear();
			Shapes.reserve(in_rDesc.ShapeCount);
		}

		ColliShape* CreateShape(const ColliShapeCInfo& in_rInfo)
		{
			return ms_fpCreateShape(this, in_rInfo);
		}

		CharacterRigidBody* CreateCharacterRigidBody(const CharacterRigidBodyCinfo& in_rInfo)
		{
			return ms_fpCreateCharacterRigidBody(this, in_rInfo);
		}

		ColliShape* GetShape() const
		{
			return Shapes.front();
		}

		ColliShape* GetShapeById(size_t in_id) const
		{
			if (Shapes.empty())
				return { nullptr };
			
			if (auto* pShape = FindColliShape(in_id))
				return pShape;
		
			return { nullptr };
		}

		ColliShape* FindColliShape(size_t in_id) const
		{
			for (auto& shape : Shapes)
			{
				if (shape->GetID() == in_id)
					return shape;
			}

			return nullptr;
		}

		void SetEnable(bool in_enable)
		{
			for (auto& shape : Shapes)
			{
				shape->SetEnable(in_enable);
			}
		}
	};

	class GOCColliderListener
	{
	public:
		virtual ~GOCColliderListener() = default;
		virtual void OnEnter(void* in_pHitEventCollision) {}
		virtual void OnStay(void* in_pStayTrigger) {}
		virtual void OnLeave(void* in_pLeaveEventCollision) {}
	};
}