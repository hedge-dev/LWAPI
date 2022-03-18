#pragma once

namespace app::game
{
	class ColliShapeCInfo : public CollisionObjCinfo
	{
	protected:
		csl::ut::Enum<CollisionShapeType::ShapeType, char> m_Type{ CollisionShapeType::ShapeType::ShapeType_MAX };

	public:
		char m_MotionType{};
		size_t m_Unk7{};
		size_t m_Unk8{};

		ColliShapeCInfo(CollisionShapeType::ShapeType in_type) : m_Type(in_type) {}
	};
}