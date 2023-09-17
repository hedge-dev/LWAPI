#pragma once

namespace app::game
{
	bool SearchPlane(csl::math::Plane* out_pPlane, GameDocument& in_rDocument, const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo);
	bool SerachPlaneAndGrindPath(csl::math::Plane* out_pPlane, GameDocument& in_rDocument, const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo);
	using SearchPlane_t = bool(*)(csl::math::Plane* out_pPlane, GameDocument& in_rDocument, const csl::math::Vector3& in_rFrom, const csl::math::Vector3& in_rTo);

	class MoveBound : public MoveController
	{
	public:
		class Listener
		{
		public:
			virtual void OnBound(const csl::math::Plane& in_rPlane) = 0;
		};

		struct Desc
		{
			csl::math::Vector3 Velocity{};
			float Unk2{ 3.0f };
			float Unk3{ 300.0f };
			float Unk4{ 0.8f };
			float Unk5{ 0.75f };
			float Unk6{ 150.0f };
			int Unk7{};
			int Unk8{ 1 };
			float Unk9{ 0.1f };
			float Unk10{};
			char Unk11{};
			PathEvaluator PathEvaluator{};
			csl::ut::Bitset<uint16> Flags{};
			int Unk13{};
		};
		
		csl::math::Plane Plane{};
		Desc Description{};
		csl::ut::Bitset<uint16> Flags{};
		SearchPlane_t pSearchPlane = nullptr;
		Listener* pListener{};

		DEFINE_RTTI_PTR(ASLR(0x00F6BD84));

		void RegisterSearchFunction(SearchPlane_t in_pFunction)
		{
			pSearchPlane = in_pFunction;
		}

		MoveBound() : MoveController(MoveControllerType::eMoveControllerType_Bound)
		{
			RegisterSearchFunction(&app::game::SearchPlane);
		}

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
		{
			return GetRuntimeTypeInfoStatic();
		}

		void OnEnter() override
		{
			if (Flags.test(1))
				RaycastSearchPlane(0.015f);
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			ResetLocalFlag();
			UpdatePlane(in_rUpdateInfo.deltaTime);
			CalcVelocity(in_rUpdateInfo.deltaTime);
			AdvancePosition(in_rUpdateInfo.deltaTime);
			DetectTerrainCollision(in_rUpdateInfo.deltaTime);
		}

		void ResetLocalFlag()
		{
			Flags.reset();
		}

		void UpdatePlane(float in_delta)
		{
			UpdateRequestRayCast();
			if (Flags.test(1))
				RaycastSearchPlane(in_delta);
		}

		void Setup(MoveBound::Desc& in_rDescription)
		{
			Description = in_rDescription;

			auto* pMovement = GetOwnerMovement();
			auto* pContextParam = pMovement->GetContextParam();
			
			pContextParam->Velocity = in_rDescription.Velocity;
		
			if (in_rDescription.Flags.test(1))
				Flags.set(1);
		}

		void UpdateRequestRayCast()
		{
			if (Description.Unk7 < Description.Unk8 - 1)
			{
				Description.Unk7++;
				return;
			}

			Flags.set(1);
			Description.Unk7 = 0;
		}

		void RaycastSearchPlane(float in_delta)
		{
			auto* pMovement = GetOwnerMovement();
			auto* pContextParam = pMovement->GetContextParam();

			csl::math::Vector3 velocityDelta{ pContextParam->Velocity * in_delta * csl::math::Max(Description.Unk8, 1) };
			
			if (Description.PathEvaluator.Component.IsValid())
			{
				auto tangent = Description.PathEvaluator.GetTangent(Description.PathEvaluator.Distance);
				auto normal = Description.PathEvaluator.GetNormal(Description.PathEvaluator.Distance);
				auto binormal = tangent.cross(normal);

				velocityDelta -= csl::math::Vector3(binormal * velocityDelta.dot(binormal));
			}

			float length = app::math::Vector3NormalizeWithLength(velocityDelta, &velocityDelta);
			csl::math::Vector3 rayStart{ pContextParam->Position - (velocityDelta * Description.Unk2) };
			csl::math::Vector3 rayEnd{ pContextParam->Position + velocityDelta * (length + Description.Unk2 * 2 + Description.Unk9) };

			if (!pSearchPlane(&Plane, *pMovement->GetGameObject()->GetDocument(), rayStart, rayEnd))
			{
				Plane.Normal = *csl::math::Vector3::Zero;
				Plane.Distance = 1.0f;
			}
		}

		void CalcVelocity(float in_delta)
		{
			auto* pMovement = GetOwnerMovement();
			auto* pContextParam = pMovement->GetContextParam();

			csl::math::Vector3 gravityDir{ 0.0f, -1.0f, 0.0f };
			if (auto* pGravity = GetOwnerMovement()->GetGameObject()->GetComponent<game::GOCGravity>())
				gravityDir = pGravity->GetGravityDirection();
		
			gravityDir *= Description.Unk3 * in_delta;
			
			pContextParam->Velocity += gravityDir;

			if (Description.Unk11)
			{
				csl::math::Vector3 velocityNormalized{};
				float length = math::Vector3NormalizeWithLength(pContextParam->Velocity, &velocityNormalized);
				if (length != 0.0f && length > Description.Unk10)
					pContextParam->Velocity = { velocityNormalized * Description.Unk10 };
			}
		}

		void ModifyVelocityWhenSV(const csl::math::Vector3& in_rVec, float in_delta)
		{
			auto* pMovement = GetOwnerMovement();
			auto* pContextParam = pMovement->GetContextParam();

			pContextParam->Velocity = { (pContextParam->Position - in_rVec) * 1.0f / in_delta };
		}

		void AdvancePosition(float in_delta)
		{
			auto* pMovement = GetOwnerMovement();
			auto* pContextParam = pMovement->GetContextParam();

			if (!Description.PathEvaluator.Component.IsValid())
			{
				pContextParam->Position += csl::math::Vector3(pContextParam->Velocity * in_delta);
				return;
			}
		
			csl::math::Vector3 velocityScaled{ pContextParam->Velocity * in_delta };
			auto tangent = Description.PathEvaluator.GetTangent(Description.PathEvaluator.Distance);
			auto normal = Description.PathEvaluator.GetNormal(Description.PathEvaluator.Distance);
			auto position = Description.PathEvaluator.GetWorldPosition(Description.PathEvaluator.Distance);
		
			csl::math::Vector3 newPos{ pContextParam->Position - position + normal * velocityScaled.dot(normal) };

			float speed = velocityScaled.dot(tangent);
			if (Description.PathEvaluator.Distance + speed >= 0.0f && Description.PathEvaluator.GetLength())
			{
				Description.PathEvaluator.Advance(speed);
				position = Description.PathEvaluator.GetWorldPosition(Description.PathEvaluator.Distance);
				if (Description.Flags.Test(2))
				{
					normal = Description.PathEvaluator.GetNormal(Description.PathEvaluator.Distance);
					newPos *= newPos.norm();
				}

				auto oldPos = pContextParam->Position;
				pContextParam->Position = { position + newPos };
				ModifyVelocityWhenSV(oldPos, in_delta);
				return;
			}

			Description.PathEvaluator.Reset();
			pContextParam->Position += csl::math::Vector3(pContextParam->Velocity * in_delta);
		}

		void DetectTerrainCollision(float in_delta)
		{
			auto* pMovement = GetOwnerMovement();
			auto* pContextParam = pMovement->GetContextParam();
			
			float distance = Plane.Distance + Plane.Normal.dot(pContextParam->Position - Plane.Normal * Description.Unk2);
			if (distance >= -0.000001f)
				return;
			
			Flags.set(0);
			if (pListener)
				pListener->OnBound(Plane);
			
			pContextParam->Position -= Plane.Normal * distance;
			if (Description.Flags.test(0))
			{
				pContextParam->Velocity = *csl::math::Vector3::Zero;
				return;
			}
			
			csl::math::Vector3 gravityDir = Plane.Normal;
			if (Description.Flags.test(3))
			{
				if (auto* pGravity = pMovement->GetGameObject()->GetComponent<GOCGravity>())
					gravityDir = { -pGravity->GetGravityDirection() };
			}

			pContextParam->Velocity = { gravityDir * csl::math::Min(-(gravityDir.dot(pContextParam->Velocity) * Description.Unk5), Description.Unk6) +
				(pContextParam->Velocity - gravityDir * gravityDir.dot(pContextParam->Velocity)) * Description.Unk4 };
			
			Description.Unk7 = Description.Unk8;
		}

		void ResetListener(Listener* in_pListener)
		{
			pListener = in_pListener;
		}

		void ResetPathDistance()
		{
			if (!Description.PathEvaluator.Component.IsValid())
				return;

			auto* pMovement = GetOwnerMovement();
			auto* pContextParam = pMovement->GetContextParam();

			float pathLen = Description.PathEvaluator.GetLength();
			float distance{};
			Description.PathEvaluator.GetClosestPositionAlongSpline(pContextParam->Position, distance, 0.0f, &pathLen);
			Description.PathEvaluator.SetDistance(distance);
		}
	};
}