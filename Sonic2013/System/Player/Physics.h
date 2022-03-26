#pragma once

namespace app::PlayerUtil
{
	class PositionTracer;
}

namespace app::Player
{
	class CPlayer;
	class CParameterSpeed;
	class GravityController;

	class CPhysics : public fnd::ReferencedObject
	{
	public:
		CPlayer* m_pPlayer{};
		int m_Unk1{};
		csl::math::Vector3 m_Position{};
		csl::math::Quaternion m_Rotation = csl::math::Quaternion::Identity;
		csl::math::Matrix34 m_Unk2{};
		csl::math::Vector3 m_Velocity{};
		csl::math::Vector3 m_Unk3{};
		csl::math::Vector3 m_Unk4{};
		csl::math::Vector3 m_Unk5{};
		csl::math::Vector3 m_Unk6{};
		csl::math::Vector3 m_DrawnForce{};
		csl::math::Vector3 m_DrawnPosition{};
		csl::math::Vector3 m_Up{};
		INSERT_PADDING(16);
		csl::math::Vector3 m_PositionHistory[256]{};
		csl::math::Quaternion m_RotationHistory[256]{};
		csl::math::Vector3 m_VelocityHistory[256]{};
		INSERT_PADDING(1024);
		csl::ut::Bitset<size_t> m_Unk7{};
		csl::math::Matrix34 m_Unk8{};
		INSERT_PADDING(56); // app::Player::SGroundInfo
		fnd::Handle<game::ColliShape> m_Unk9{};
		INSERT_PADDING(56); // app::Player::SGroundInfo
		fnd::Handle<game::ColliShape> m_Unk10{};
		csl::math::Vector3 m_Unk11{};
		INSERT_PADDING(48);
		csl::math::Vector3 m_Unk12{};
		csl::math::Vector3 m_Unk13{};
		csl::math::Vector3 m_Unk14{};
		INSERT_PADDING(4);
		ut::ScopedPtr<CParameterSpeed> m_spSpeedParamater{ nullptr, nullptr };
		ut::RefPtr<GravityController> m_rpGravityController{};
		INSERT_PADDING(4); // app::Player::TouchedMovableShapeInfo
		fnd::Handle<game::ColliShape> m_Unk15{};
		INSERT_PADDING(84);
		INSERT_PADDING(4); // app::Player::TouchedMovableShapeInfo
		fnd::Handle<game::ColliShape> m_Unk16{};
		INSERT_PADDING(84);
		ut::ScopedPtr<PlayerUtil::PositionTracer> m_rpPositionTracer { nullptr, nullptr };
		csl::math::Vector3 m_Unk17{};

		csl::math::Vector3 GetVelocity() const
		{
			return m_Velocity;
		}

		csl::math::Vector3 GetHorzVelocity() const
		{
			return static_cast<csl::math::Vector3>(GetVelocity() - m_Up * GetVelocity().dot(m_Up));
		}

		csl::math::Vector3 GetVertVelocity() const
		{
			return static_cast<csl::math::Vector3>(m_Up * GetVelocity().dot(m_Up));
		}
	};
}