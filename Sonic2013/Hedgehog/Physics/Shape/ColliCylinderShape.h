#pragma once

namespace app::game
{
	class ColliCylinderShapeBase : public ColliShape
	{
	public:
		float Radius{};
		float Height{};
	};

	class ColliCylinderShapeCInfo : public ColliShapeCInfo
	{
	public:
		float Radius{};
		float Height{};

		ColliCylinderShapeCInfo() : ColliShapeCInfo(CollisionShapeType::ShapeType::eShapeType_Cylinder)
		{

		}
	};
}