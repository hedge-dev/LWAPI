#pragma once

namespace app::game
{
	class CharacterRigidBodyBase : public ColliShape
	{
	public:
		INSERT_PADDING(32){};
		csl::math::Vector3 LinearVelocity{};
		csl::math::Quaternion Rotation{};

		void SetLinearVelocity(const csl::math::Vector3 in_linearVelocity)
		{
			LinearVelocity = in_linearVelocity;
		}
	};

	using CharacterRigidBody = CharacterRigidBodyBase;
}