#pragma once

namespace app::game
{
	class CollisionObjCinfo
	{
	public:
		char Unk1{};
		char Unk4{};
		ushort Flags{ 2 };
		short Unk2{};
		short Unk5{};
		uint Unk3{};
		uint ShapeID{ static_cast<uint>(-1) };
		fnd::HFrame* pParent{};
		csl::math::Vector3 Position{};
		csl::math::Quaternion Rotation{};

	public:
		void SetLocalPosition(const csl::math::Vector3& in_rPosition)
		{
			Position = in_rPosition;
			Unk1 |= 1;
		}

		void SetLocalRotation(const csl::math::Quaternion& in_rRotation)
		{
			Rotation = rRot;
			Unk1 |= 2;
		}
	};
}