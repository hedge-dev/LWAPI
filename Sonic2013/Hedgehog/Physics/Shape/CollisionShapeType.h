#pragma once

namespace app::game
{
	class CollisionShapeType
	{
	public:
		enum class ShapeType : char
		{
			eShapeType_Sphere,
			eShapeType_Box,
			eShapeType_Capsule,
			eShapeType_Cylinder,
			eShapeType_Mesh,
			eShapeType_RigidBody,
			eShapeType_Max
		};
	};
}