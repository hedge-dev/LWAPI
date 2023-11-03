#pragma once

namespace app::game
{
	class ColliShapeCInfo : public CollisionObjCinfo
	{
	public:
		csl::ut::Enum<CollisionShapeType::ShapeType, char> ShapeType{ CollisionShapeType::ShapeType::eShapeType_Max };
		csl::ut::Enum<PhysicsMotionType::MotionType, char> MotionType{ PhysicsMotionType::MotionType::eMotionType_Max };
		size_t Unk7{};
		size_t Unk8{};
		int Unk9{ -1 };

		ColliShapeCInfo(CollisionShapeType::ShapeType in_type) : ShapeType(in_type) {}
	};
}