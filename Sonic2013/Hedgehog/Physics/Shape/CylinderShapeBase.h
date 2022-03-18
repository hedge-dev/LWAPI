#pragma once

namespace app::game
{
	class ColliCylinderShapeBase : public ColliShape
	{
	public:
		float m_Radius{};
		float m_Height{};
	};

	class ColliCylinderShapeCInfo : public ColliShapeCInfo
	{
	public:
		float m_Radius{};
		float m_Height{};

		ColliCylinderShapeCInfo() : ColliShapeCInfo(CollisionShapeType::ShapeType::ShapeType_Cylinder)
		{

		}
	};
}