#pragma once

namespace app::game
{
	class ColliCapsuleShapeBase : public ColliShape
	{
	public:
		float m_Radius{};
		float m_Height{};
	};

	class ColliCapsuleShapeCInfo : public ColliShapeCInfo
	{
	public:
		float m_Radius{};
		float m_Height{};

		ColliCapsuleShapeCInfo() : ColliShapeCInfo(CollisionShapeType::ShapeType::ShapeType_Capsule)
		{

		}
	};
}