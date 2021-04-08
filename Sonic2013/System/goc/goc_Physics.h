#pragma once

namespace app::game
{
	class GOCPhysics : public fnd::GOComponent
	{
	public:
		struct Description
		{
			size_t m_ShapeCount;
		};

	protected:
		csl::ut::MoveArray<ColliShape*> m_Shapes{ GetAllocator() };
		fnd::HFrame* m_pFrame{};
		PhysicsWorld* m_pPhysicsWorld{};

	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateShape, ASLR(0x004CB710), GOCPhysics* pThis, const ColliShapeCInfo& rInfo);
		inline static fnd::GOComponentClass* ms_pStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FD78B4));

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