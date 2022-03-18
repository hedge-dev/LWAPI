#pragma once

namespace app::game
{
	class ColliSphereShapeBase : public ColliShape
	{
	public:
		float m_Radius{};
		size_t m_Unk9{};

		ColliSphereShapeBase()
		{
			ASSERT_OFFSETOF(ColliSphereShapeBase, m_Radius, 352);
		}
	};

	class ColliSphereShapeCInfo : public ColliShapeCInfo
	{
	public:
		float m_Radius{};
		size_t m_Unk9{};

		ColliSphereShapeCInfo() : ColliShapeCInfo(CollisionShapeType::ShapeType::ShapeType_Sphere)
		{

		}
	};
}