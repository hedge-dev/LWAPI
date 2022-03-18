#pragma once

namespace app::game
{
	class CollisionObjCinfo
	{
	public:
		ushort m_Unk1{};
		ushort m_Flags{};
		uint m_Unk2{};
		uint m_Unk3{};
		uint m_ShapeID{};
		fnd::HFrame* m_pParent{};
		uint m_Unk4{};
		uint m_Unk5{};
		uint m_Unk6{};
		csl::math::Vector3 m_Position{ 0,0,0 };
		csl::math::Quaternion m_Rotation{ 0,0,0,1 };

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