#pragma once

namespace app::PlayerUtil
{
	class PositionTracer;
}

namespace app::Player
{
	class CSnowBall;
	class CPlayer;

	struct SGroundInfo
	{
		bool IsOnGround{};
		char Unk2{};
		int Unk3{};
		csl::math::Vector3 Unk4{};
		csl::math::Vector3 Unk5{};
		int Attribute{};
		float Unk7{};
		fnd::Handle<game::ColliShape> ColliShape{};

		int GetAttribute() const
		{
			return Attribute;
		}

		int GetMaterial() const
		{
			return GetAttribute() >> 24;
		}

		void Reset()
		{
			IsOnGround = false;
			Unk2 = false;
			Unk4 = { csl::math::Vector3::UnitY() };
			Unk5 = *csl::math::Vector3::Zero;
			Attribute = 0;
			Unk7 = 0.0f;
			ColliShape = { nullptr };
		}
	};

	class CPhysics : public fnd::ReferencedObject
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetGroundInfo, ASLR(0x00857440), CPhysics*, const SGroundInfo&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpNormalizeRotationMatrix, ASLR(0x00856890), CPhysics*);

	public:
		CPlayer* m_pPlayer{};
		int m_Unk1{};
		csl::math::Vector3 m_Position{};
		csl::math::Quaternion m_Rotation{};
		csl::math::Matrix34 PhysicsMatrix{};
		csl::math::Vector3 m_Velocity{};
		csl::math::Vector3 m_Unk3{};
		csl::math::Vector3 m_Unk4{};
		csl::math::Vector3 m_Unk5{};
		csl::math::Vector3 m_Unk6{};
		csl::math::Vector3 m_DrawnForce{};
		csl::math::Vector3 m_DrawnPosition{};
		csl::math::Vector3 m_Up{};
		byte m_Unk18{};
		int m_Unk19{};
		INSERT_PADDING(8);
		csl::math::Vector3 m_PositionHistory[256]{};
		csl::math::Quaternion m_RotationHistory[256]{};
		csl::math::Vector3 m_VelocityHistory[256]{};
		INSERT_PADDING(1024);
		csl::ut::Bitset<size_t> m_Unk7{};
		csl::math::Matrix34 m_CameraViewMtx{};
		SGroundInfo m_Unk9{};
		SGroundInfo m_Unk10{};
		csl::math::Vector3 m_Unk11{};
		INSERT_PADDING(36);
		float m_Unk20{};
		INSERT_PADDING(8);
		csl::math::Vector3 m_Unk12{};
		csl::math::Vector3 m_Unk13{};
		csl::math::Vector3 m_Unk14{};
		INSERT_PADDING(4);
		ut::ScopedPtr<CParameterSpeed> m_spSpeedParameter{ nullptr, nullptr };
		ut::RefPtr<GravityController> m_rpGravityController{};
		INSERT_PADDING(4); // app::Player::TouchedMovableShapeInfo
		fnd::Handle<game::ColliShape> m_Unk15{};
		INSERT_PADDING(84);
		INSERT_PADDING(4); // app::Player::TouchedMovableShapeInfo
		fnd::Handle<game::ColliShape> m_Unk16{};
		INSERT_PADDING(84);
		ut::ScopedPtr<PlayerUtil::PositionTracer> m_rpPositionTracer { nullptr, nullptr };
		csl::math::Vector3 m_Unk17{};

		bool IsOnGround() const
		{
			return m_Unk9.IsOnGround;
		}

		void SetOnGround(bool in_isOnGround)
		{
			m_Unk9.IsOnGround = in_isOnGround;
		}
		
		void ResetGroundState()
		{
			m_Unk9.Reset();
			m_Up = GetGravityController()->GetUpDirectionAtPoint(m_Position);

			m_Unk9.IsOnGround = false;
		}

		bool IsGravityDirectionNotUpdate(const csl::math::Vector3& in_position, bool in_isOnGround) const
		{
			if (m_Unk7.test(4))
				return false;
		
			if (m_Unk7.test(5) || m_Unk7.test(6))
				return true;
		
			if (!in_isOnGround && m_rpGravityController->IsGravityTypeInner() && !m_Unk7.test(9))
				return true;

			if (in_isOnGround)
				return false;

			if (m_rpGravityController->GetType() == (game::GravityType)12)
				return false;
		
			auto* pPathEvaluator = &m_rpGravityController->Path;
			if (!pPathEvaluator->Component.IsValid())
				return false;

			csl::math::Vector3 point{};
			csl::math::Vector3 normal{};
			csl::math::Vector3 tangent{};
			pPathEvaluator->GetPNT(pPathEvaluator->Distance, &point, &normal, &tangent);
			csl::math::Vector3 worldPos{ pPathEvaluator->GetWorldPosition(csl::math::Max(pPathEvaluator->Distance - 10.0f, 0.0f)) };
			csl::math::Vector3 worldPos2{ pPathEvaluator->GetWorldPosition(csl::math::Min(pPathEvaluator->Distance + 10.0f, pPathEvaluator->GetLength() - 0.001f)) };

			csl::math::Vector3 offset{ worldPos - point };
			if (!math::Vector3NormalizeIfNotZero(offset, &offset))
				return true;

			csl::math::Vector3 offset2{ worldPos2 - point };

			if (!math::Vector3NormalizeIfNotZero(offset2, &offset2))
				return true;

			float dot = offset.dot(offset2);
			if (dot <= cosf(3.1241393f))
				return true;
		
			csl::math::Vector3 cross{ normal.cross(tangent) };
			csl::math::Vector3 cross2{ offset.cross(offset2) };
			if (fabs(cross2.squaredNorm()) <= 0.000001f)
				return true;
		
			if (cross2.dot(cross) < 0.0f)
				return false;
		
			return true;
		}

		void DisableExternalForce(float in_unk)
		{
			m_Unk20 = in_unk;
			m_Unk7.set(1, true);
		}

		bool IsDistableExternalForce()
		{
			return m_Unk7.test(1);
		}

		void EnableExternalForce()
		{
			return m_Unk7.set(1, false);
		}

		void SetPosition(const csl::math::Vector3& in_rPosition)
		{
			m_Position = in_rPosition;
			PhysicsMatrix = { csl::math::Matrix34(in_rPosition.x(), in_rPosition.y(), in_rPosition.z()) * csl::math::Matrix34(m_Rotation) };
		}

		void NormalizeRotationMatrix()
		{
			ms_fpNormalizeRotationMatrix(this);
		}

		void SetRotation(const csl::math::Matrix34& in_rRotationMatrix)
		{
			PhysicsMatrix = { csl::math::Matrix34(m_Position.x(), m_Position.y(), m_Position.z()) * in_rRotationMatrix };
			NormalizeRotationMatrix();
		}

		csl::math::Vector3 GetVelocity() const
		{
			return m_Velocity;
		}

		void SetVelocity(const csl::math::Vector3& in_rVelocity)
		{
			m_Velocity = in_rVelocity;
		}

		csl::math::Vector3 GetHorzVelocity() const
		{
			return static_cast<csl::math::Vector3>(GetVelocity() - m_Up * GetVelocity().dot(m_Up));
		}

		float GetHorzVelocityLength() const
		{
			return GetHorzVelocity().norm();
		}

		void SetHorzVelocity(const csl::math::Vector3& in_rHorzVelocity)
		{
			m_Velocity = { in_rHorzVelocity + GetVertVelocity() };
		}

		csl::math::Vector3 GetVertVelocity() const
		{
			return static_cast<csl::math::Vector3>(m_Up * GetVelocity().dot(m_Up));
		}

		csl::math::Vector3 ConvertAirVertVector(const csl::math::Vector3& in_rVertVelocity) const
		{
			csl::math::Vector3 gravityUpDir{ GetGravityUpDirection() };

			csl::math::Matrix34 invGravityMtx{};
			csl::math::Matrix34Inverse(GetGravityUpMatrix(), &invGravityMtx);

			return { invGravityMtx * csl::math::Vector3(gravityUpDir * in_rVertVelocity.dot(gravityUpDir)) };
		}

		csl::math::Vector3 GetRight() const
		{
			return { -PhysicsMatrix.GetColumn(0) };
		}

		csl::math::Vector3 GetUp() const
		{
			return { PhysicsMatrix.GetColumn(1) };
		}

		csl::math::Vector3 GetFront() const
		{
			return { PhysicsMatrix.GetColumn(2) };
		}

		byte GetHistoryID(byte in_index) const
		{
			if (in_index < m_Unk19)
			{
				return (byte)(m_Unk18 - in_index);
			}
			else
			{
				return (byte)(m_Unk19 - 1);
			}
		}

		csl::math::Vector3 GetHistoryPosition(byte in_index) const
		{
			return { m_PositionHistory[GetHistoryID(in_index)] };
		}

		GravityController* GetGravityController()
		{
			return m_rpGravityController.get();
		}

		GravityController* GetGravityController() const
		{
			return m_rpGravityController.get();
		}

		csl::math::Vector3 GetGravityDirection() const
		{
			return { GetGravityController()->GravityDirection };
		}

		csl::math::Vector3 GetGravityUpDirection() const
		{
			return { -GetGravityController()->GravityDirection };
		}

		csl::math::Matrix34 GetGravityUpMatrix() const
		{
			return GetGravityController()->Unk6;
		}

		bool IsGravityTypeRunPath() const
		{
			return GetGravityController()->IsGravityTypeRunPath();
		}

		CParameterSpeed* GetSpeedParameter()
		{
			return m_spSpeedParameter.get();
		}

		void UpdateViewMatrix();

		void UpdateBeforeMove(float in_deltaTime)
		{
			m_Unk3 = m_Velocity;
			m_Unk4 = GetGravityDirection();
			UpdateViewMatrix();
			if (!IsGravityDirectionNotUpdate(m_Position, IsOnGround()))
			{
				m_rpGravityController->ApplyGravityDirectionAndPosition();
			}
			else
			{
				m_rpGravityController->ApplyGravityPathPosition();
			}

			m_Unk7.set(2, false);
			if (IsDistableExternalForce() && m_Unk18 > 0.0f)
			{
				m_Unk18 -= in_deltaTime;
				if (m_Unk18 <= 0.0f)
				{
					EnableExternalForce();
				}
			}
			
			int material = m_Unk9.GetMaterial();
			bool groundStatus = false;
			if (IsOnGround() && material != 15 && material != 20 && material != 21 && material != 12 && material != 13)
				groundStatus = m_Unk7.test(8);
		
			m_spSpeedParameter->SetGroundStatus((CParameterSpeed::EGroundStatus)groundStatus);
			m_spSpeedParameter->Update();
		}

		void UpdateGravityForced(const csl::math::Vector3& in_rVector)
		{
			m_rpGravityController->UpdateForcedGravity(in_rVector);
		}

		void SetGravityScale(float in_gravityScale)
		{
			m_rpGravityController.get()->GravityScale = in_gravityScale;
		}

		void SetDrawnPosition(const csl::math::Vector3& in_rDrawnPosition)
		{
			m_DrawnPosition = in_rDrawnPosition;
		}

		void SetGroundInfo(const SGroundInfo& in_rGroundInfo)
		{
			ms_fpSetGroundInfo(this, in_rGroundInfo);
		}
	};
}