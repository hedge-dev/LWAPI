#pragma once

namespace app::game
{
	class ColliBoxShapeBase : public ColliShape
	{
	public:
		csl::math::Vector3 Size{};

		ColliBoxShapeBase()
		{
			ASSERT_OFFSETOF(ColliBoxShapeBase, Size, 352);
		}
	};

	class ColliBoxShapeCInfo : public ColliShapeCInfo
	{
	public:
		csl::math::Vector3 Size{};

		ColliBoxShapeCInfo() : ColliShapeCInfo(CollisionShapeType::ShapeType::eShapeType_Box)
		{

		}
	};
}