#pragma once

namespace app::game
{
	class ColliCapsuleShapeBase : public ColliShape
	{
	public:
		float Radius{};
		float Height{};
	};

	class ColliCapsuleShapeCInfo : public ColliShapeCInfo
	{
	public:
		float Radius{};
		float Height{};

		ColliCapsuleShapeCInfo() : ColliShapeCInfo(CollisionShapeType::ShapeType::eShapeType_Capsule)
		{

		}
	};
}