#pragma once

namespace app::Player
{
	class CSnowBall : public CPlayerVehicle
	{
	public:
		int Unk1{};
		int Unk2{};
		int Unk3{};
		hh::eff::CInstanceHandle<hh::eff::CEffectInstance> Unk4{};
		INSERT_PADDING(4);
		hh::eff::CInstanceHandle<hh::eff::CEffectInstance> Unk5{};
		INSERT_PADDING(4);
		hh::eff::CInstanceHandle<hh::eff::CEffectInstance> Unk6{};
		INSERT_PADDING(4);
		hh::eff::CInstanceHandle<hh::eff::CEffectInstance> Unk7{};
		INSERT_PADDING(4);
		fnd::SoundHandle Unk8{};
		fnd::SoundHandle Unk9{};
		fnd::HFrame Unk10{};
		fnd::HFrame Unk11{};
		int Unk69{};
		int Unk70{};
		int Unk71{};
		float Unk12{};
		float Radius{ 15.0f };
		float Unk14{ 285.0f };
		float Unk15{};
		float Unk16{};
		float Unk17{};
		float Unk18{};
		float Unk19{};
		float Unk20{};
		float Unk21{};
		int Unk22{};
		csl::math::Vector3 Unk23{};
		csl::math::Vector3 Position{};
		csl::math::Vector3 Unk28{};
		csl::math::Matrix34 Unk29{};
		csl::math::Matrix34 Unk30{};
		csl::math::Matrix34 Unk31{};
		csl::math::Quaternion Unk32{};
		csl::math::Quaternion Unk33{};
		csl::math::Vector3 Unk34{};
		csl::math::Vector3 Unk35{};
		csl::math::Vector3 Front{ 0.0f, 0.0f, 1.0f };
		csl::math::Vector3 Up{ 0.0f, 1.0f, 0.0f };
		csl::math::Vector3 Unk38{ 0.0f, 0.0f, 1.0f };
		csl::math::Vector3 Unk39{};
		bool IsOnGround{};
		char Unk41{};
		char Unk42{};
		char Unk43{};
		char Unk44{};
		char Unk45{};
		char Unk46{};
		char Unk47{};
		char Unk48{};
		char Unk49{};
		char Unk50{};
		char Unk51{};
		char Unk52{};
		char Unk53{};
		char Unk54{};
		char Unk55{};
		char Unk56{};
		char Unk57{};
		char Unk58{};
		char Unk59{};
		char Unk60{};
		char Unk61{};
		char Unk62{};
		char Unk63{};
		PlayerUtil::Hermite3 Unk64{};
		float Unk65{};
		float Unk66{};
		game::PathEvaluator Path{};
		fnd::Handle<game::ColliShape> Unk67{};
		int Unk68{};

		CSnowBall(CPlayer* in_pPlayer) : CPlayerVehicle(in_pPlayer, 1)
		{
			AddProperty(0x4003, 2);
		}

		void SetPosition(const csl::math::Vector3& in_rPosition)
		{
			Position = in_rPosition;
			Unk23 = Position;
			Unk34 = { 0.0, 0.0f, 0.0f };

			Unk22 = true;

			SetMovableGroundLock(false);

			Unk21 = false;

			ResetPathMode();

			Unk20 = false;

			if (!Unk22)
				return;
		
			SetRadius(15.0f);
			Unk22 = false;
			Unk43 = true;
		}

		void SetDirection(const csl::math::Vector3& in_rFront, const csl::math::Vector3& in_rUp)
		{
			Front = in_rFront;
			Up = in_rUp;
		}

		void SetMovableGroundLock(bool in_lockAbility);

		void ResetPathMode();

		csl::math::Vector3 GetGravityUpDirection(const csl::math::Vector3& in_rVector)
		{
			csl::math::Vector3 direction{};

			auto* pGravity = GetComponent<game::GOCGravity>();
			if (!pGravity || !pGravity->GetGravityDirection(in_rVector, &direction))
				return Up;

			return direction;
		}

		void SetRadius(float in_radius)
		{
			csl::math::Vector3 gravityUpDir = GetGravityUpDirection(Unk23);
			
			float radiusDiff = in_radius - Radius;
			Radius = in_radius;

			Unk23 += (gravityUpDir * radiusDiff);
			Position += (gravityUpDir * radiusDiff);

			auto* pCollider = GetComponent<game::GOCCollider>();
			if (pCollider)
			{
				auto* pShape = static_cast<game::ColliSphereShapeBase*>(pCollider->GetShapeById(0));
				if (pShape)
					pShape->SetRadius(Radius);
			}

			auto* pVisualModel = GetComponent<fnd::GOCVisualModel>();
			GetComponent<game::GOCShadow>();

			pVisualModel->SetLocalScale({ in_radius / 15.0f, in_radius / 15.0f, in_radius / 15.0f });
		}
	};
}