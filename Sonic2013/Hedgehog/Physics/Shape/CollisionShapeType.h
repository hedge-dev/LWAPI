#pragma once

namespace app::game
{
	class CollisionShapeType
	{
	public:
		enum class ShapeType : char
		{
			ShapeType_Sphere,
			ShapeType_Box,
			ShapeType_Capsule,
			ShapeType_Cylinder,
			ShapeType_Mesh,
			ShapeType_RigidBody,
			ShapeType_MAX
		};
	};
}