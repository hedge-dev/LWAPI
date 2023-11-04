#pragma once

namespace app::game
{
	class GOCPhysics : public fnd::GOComponent
	{
	private:
		inline static FUNCTION_PTR(ColliShape*, __thiscall, ms_fpCreateShape, ASLR(0x004CB710), GOCPhysics* pThis, const ColliShapeCInfo& rInfo);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD78B4));
		
	public:
		struct Description
		{
			size_t ShapeCount;
		};

	protected:
		csl::ut::MoveArray<ColliShape*> m_Shapes{ GetAllocator() };
		fnd::HFrame* m_pFrame{};
		CPhysicsWorld* m_pPhysicsWorld{};

	public:
		static fnd::GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}

		void Setup(const Description& in_rDesc)
		{
			m_Shapes.change_allocator(GetAllocator());
			m_Shapes.clear();
			m_Shapes.reserve(in_rDesc.ShapeCount);
		}

		ColliShape* CreateShape(const ColliShapeCInfo& in_rInfo)
		{
			return ms_fpCreateShape(this, in_rInfo);
		}

		ColliShape* GetShape() const
		{
			return m_Shapes.front();
		}

		ColliShape* FindColliShape(size_t in_id) const
		{
			for (auto& shape : m_Shapes)
			{
				if (shape->GetID() == in_id)
					return shape;
			}

			return nullptr;
		}

		void SetEnable(bool in_enable)
		{
			for (auto& shape : m_Shapes)
			{
				shape->SetEnable(in_enable);
			}
		}
	};
}