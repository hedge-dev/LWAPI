#pragma once

namespace app::game
{
	class CollisionObjCinfo
	{
	public:
		char m_Unk1{};
		char m_Unk4{};
		ushort m_Flags{ 2 };
		short m_Unk2{};
		short m_Unk5{};
		uint m_Unk3{};
		uint m_ShapeID{ static_cast<uint>(-1) };
		fnd::HFrame* m_pParent{};
		csl::math::Vector3 m_Position{};
		csl::math::Quaternion m_Rotation{};

	public:
		void SetLocalPosition(const csl::math::Vector3& rPos)
		{
			m_Position = rPos;
			m_Unk1 |= 1;
		}

		void SetLocalRotation(const csl::math::Quaternion& rRot)
		{
			m_Rotation = rRot;
			m_Unk1 |= 2;
		}
	};
}