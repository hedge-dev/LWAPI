#pragma once


namespace app::game
{
	class CharacterRigidBodyBase : public ColliShape
	{
	public:
		INSERT_PADDING(32){};
		csl::math::Vector3 LinearVelocity{};
		csl::math::Quaternion Rotation{};

		void SetLinearVelocity(const csl::math::Vector3 in_rLinearVelocity)
		{
			LinearVelocity = in_rLinearVelocity;
		}
	};

	class alignas(16) CharacterRigidBodyCinfo : public CollisionObjCinfo
	{
	public:
		float m_Unk7{};
		float m_Unk8{};
		float m_Unk9{ 0.78539819f };
		float m_Unk10{ 1000.0f };
		float m_Unk11{ 1 };
	};

	using CharacterRigidBody = CharacterRigidBodyBase;
}