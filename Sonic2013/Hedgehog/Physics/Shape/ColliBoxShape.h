#pragma once

namespace app::game
{
	class ColliBoxShapeBase : public ColliShape
	{
	public:
		csl::math::Vector3 m_Size{};

		ColliBoxShapeBase()
		{
			ASSERT_OFFSETOF(ColliBoxShapeBase, m_Size, 352);
		}
	};

	class ColliBoxShapeCInfo : public ColliShapeCInfo
	{
	public:
		csl::math::Vector3 m_Size{};

		ColliBoxShapeCInfo() : ColliShapeCInfo(CollisionShapeType::ShapeType::ShapeType_Box)
		{

		}
	};
}