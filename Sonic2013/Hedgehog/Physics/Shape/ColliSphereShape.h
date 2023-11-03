#pragma once

namespace app::game
{
	class ColliSphereShapeBase : public ColliShape
	{
	public:
		float Radius{};
		size_t Unk9{};

		ColliSphereShapeBase()
		{
			ASSERT_OFFSETOF(ColliSphereShapeBase, Radius, 352);
		}

		void SetRadius(float in_radius)
		{
			if (Radius == in_radius)
				return;

			Radius = in_radius;
			OnShapeEvent(2);
		}
	};

	class ColliSphereShapeCInfo : public ColliShapeCInfo
	{
	public:
		float m_Radius{};
		char m_Unk9{};

		ColliSphereShapeCInfo() : ColliShapeCInfo(CollisionShapeType::ShapeType::ShapeType_Sphere)
		{

		}
	};
}