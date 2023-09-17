#pragma once

namespace app::game
{
	class ColliShapeCInfo : public CollisionObjCinfo
	{
	public:
		csl::ut::Enum<CollisionShapeType::ShapeType, char> m_ShapeType{ CollisionShapeType::ShapeType::ShapeType_MAX };
		csl::ut::Enum<PhysicsMotionType::MotionType, char> m_MotionType{ PhysicsMotionType::MotionType::MotionType_MAX };
		size_t m_Unk7{};
		size_t m_Unk8{};
		int Unk9{ -1 };

		ColliShapeCInfo(CollisionShapeType::ShapeType in_type) : m_ShapeType(in_type) {}
	};
}