#pragma once

namespace app::Player
{
	class CPlayer;

	class GravityController : public fnd::ReferencedObject
	{
	private:
		inline static FUNCTION_PTR(csl::math::Vector3&, __thiscall, ms_fpGetUpDirectionAtPoint, ASLR(0x00853550), const GravityController*, const csl::math::Vector3&);
		inline static FUNCTION_PTR(csl::math::Vector3&, __thiscall, ms_fpGetGravityDirectionAtPointWorld, ASLR(0x00853590), const GravityController*, const csl::math::Vector3&);
		
		class MyGravityPhantomListener;

	public:
		Player::CPlayer* pPlayer{};
		game::GOCGravity* pGravityGoc{};
		float Unk2{ 350.0f };
		float GravityScale{ 1.0f };
		float Unk4{ 350.0f };
		csl::math::Vector3 GravityDirection{};
		csl::math::Matrix34 Unk6{ /* math::Matrix34OrthonormalDirection({0.0f, 1.0f, 0.0f}) */ };
		csl::ut::Bitset<size_t> Unk7{};
		game::PathEvaluator Path{};
		MyGravityPhantomListener* PhantomListener{};
		GravityController* Unk8{ this };

		game::GravityField* GetGravityField() const
		{
			return pGravityGoc->GetGravityField();
		}

		game::GravityType GetType() const
		{
			auto* pGravityField = pGravityGoc->GetGravityField();
			if (pGravityField)
			{
				return pGravityField->GetType();
			}

			return (game::GravityType)1;
		}

		csl::math::Vector3 GetPhantomPosition() const
		{
			return pGravityGoc->GetGravityPhantom()->GetPosition();
		}

		csl::math::Vector3& GetUpDirectionAtPoint(const csl::math::Vector3& in_rPoint) const
		{
			return ms_fpGetUpDirectionAtPoint(this, in_rPoint);
		}

		csl::math::Vector3& GetGravityDirectionAtPointWorld(const csl::math::Vector3& in_rPoint) const
		{
			return ms_fpGetGravityDirectionAtPointWorld(this, in_rPoint);
		}

		bool IsGravityTypeRunPath() const
		{
			return csl::ut::DynamicCast<game::GFieldCylinderSpline, game::GravityField>(GetGravityField());
		}

		bool IsGravityTypeInner() const
		{
			game::GravityType type = GetType();
			return (game::GravityType)type == 5 || type == (game::GravityType)7;
		}

		bool IsGravityTypeOuter() const
		{
			game::GravityType type = GetType();
			return type >= 2 && (type <= 4 || type == 6);
		}

		bool GetInnerRadius(float* out_pRadius) const
		{
			auto* pGravityField = pGravityGoc->GetGravityField();
			if (!pGravityField)
				return false;
		
			switch (pGravityField->GetType())
			{
			case game::GravityType::eGravityType_OutsideCylinderSpline:
			{
				*out_pRadius = csl::ut::DynamicCast<game::GFieldOutsideCylinderSpline, game::GravityField>(pGravityField)->Radius;
				return true;
			}
			case game::GravityType::eGravityType_InsideCylinderSpline:
			{
				*out_pRadius = csl::ut::DynamicCast<game::GFieldInsideCylinderSpline, game::GravityField>(pGravityField)->Radius;
				return true;
			}
			case game::GravityType::eGravityType_OutsidePrismSpline:
			{
				*out_pRadius = csl::ut::DynamicCast<game::GFieldOutsidePrismSpline, game::GravityField>(pGravityField)->Radius;
				return true;
			}
			case game::GravityType::eGravityType_InsidePrismSpline:
			{
				*out_pRadius = csl::ut::DynamicCast<game::GFieldInsidePrismSpline, game::GravityField>(pGravityField)->Radius;
				return true;
			}
			default:
			{
				return false;
			}
			}
		}

		bool GetCenterPosition(csl::math::Vector3* out_pCenter) const
		{
			if (Path.Component.IsValid())
			{
				*out_pCenter = Path.GetWorldPosition(Path.Distance);
				return true;
			}

			auto* pGravityField = pGravityGoc->GetGravityField();
			if (!pGravityField)
				return false;

			if (pGravityField->GetType() == game::GravityType::eGravityType_Sphere)
			{
				auto* pGravitySphere = csl::ut::DynamicCast<game::GFieldSphere, game::GravityField>(pGravityField);
				*out_pCenter = pGravitySphere->GetPosition();

				return true;
			}
			else if (pGravityField->GetType() == game::GravityType::eGravityType_Hemisphere)
			{
				auto* pGravitySphere = csl::ut::DynamicCast<game::GFieldHemisphere, game::GravityField>(pGravityField);
				*out_pCenter = pGravitySphere->GetPosition();

				return true;
			}
			else
			{
				return false;
			}
		}

		void ApplyGravityPathPosition()
		{
			auto* pGravityField = pGravityGoc->GetGravityField();
			if (!pGravityField)
				return;
		
			auto* pGravityPhantom = pGravityGoc->GetGravityPhantom();

			if (!Path.Component.IsValid())
				return;
		
			if (csl::ut::DynamicCast<game::GFieldCylinderSpline, game::GravityField>(pGravityField))
			{
				float distance = csl::ut::DynamicCast<game::SplineGravityEffect, game::GravityEffect>(pGravityPhantom->pGravityEffect)->GetDistanceOnPath();
				Path.SetDistance(distance);
			}
			else if (csl::ut::DynamicCast<game::GFieldSvSpline, game::GravityField>(pGravityField))
			{
				float distance = csl::ut::DynamicCast<game::SvSplineGravityEffect, game::GravityEffect>(pGravityPhantom->pGravityEffect)->GetDistanceOnPath();
				Path.SetDistance(distance);
			}
			else
			{
				float point{};
				Path.GetClosestPositionAlongSpline(GetPhantomPosition(), Path.Distance - 100.0f, Path.Distance + 100.0f, &point);
				Path.SetDistance(point);
			}
		}

		void ApplyGravityDirectionAndPosition()
		{
			GravityDirection = pGravityGoc->GetGravityDirection();

			csl::math::Quaternion rotation;
			csl::math::QuaternionRotationBetweenNormals(&rotation, { 0.0f, 1.0f, 0.0f }, { -GravityDirection });
			Unk6 = { rotation };

			ApplyGravityPathPosition();
		}

		void UpdateForcedGravity(const csl::math::Vector3 in_rVector)
		{
			auto* pGravityPhantom = pGravityGoc->GetGravityPhantom();
			pGravityPhantom->SetPosition(in_rVector);
			pGravityPhantom->Update();

			ApplyGravityDirectionAndPosition();
		}
	};
}
