#pragma once

namespace app::game
{
	class MoveObjGolonRock : public MoveController
	{
	public:
		struct SetupParam
		{
			csl::math::Vector3 Position{};
			float YOffset{};
			float PopupTime{};
			float RollWaitTime{};
			float Speed{};
			float Unk1{};
			float Unk2{};
			float Unk3{};
			bool Unk4{};
			float Unk5{};
			float Unk6{};
			bool IsCheckFall{};
			INSERT_PADDING(3);
#pragma pack(4)
			void (GameObject::* MoveEndMemFunc)() {};
#pragma pack()
#pragma pack(4)
			void (GameObject::* PassPlayerMemFunc)() {};
#pragma pack()
			GameObject* pOwner{};
		};

		enum Mode : char
		{
			eMode_Shoot,
			eMode_Move,
			eMode_Fall,
		};
		
		float PopupTime{};
		float RollWaitTime{};
		float Speed{};
		float Unk1{};
		float Unk2{};
		float Unk3{};
		bool Unk4{};
		float Unk5{};
		float Unk6{};
		bool IsCheckFall{};
		csl::ut::Enum<Mode, char> MovementMode{ static_cast<Mode>(-1) };
		PathEvaluator PathEvaluator{};
		float YOffset{};
		float OffsetMagnitude{};
		float Unk8{};
		float ElapsedTime{};
		csl::math::Vector3 Direction{};
		CPhysicsWorld* pPhysicsWorld{};
		ut::RefPtr<PhysicsRaycastJob> rpRaycastJob{};
		float RadianLocalRotation{};
		float Unk11{};
#pragma pack(4)
		void (GameObject::* MoveEndMemFunc)() {};
#pragma pack()
#pragma pack(4)
		void (GameObject::* PassPlayerMemFunc)() {};
#pragma pack()
		GameObject* pOwner{};

		MoveObjGolonRock() : MoveController(MoveControllerType::eMoveControllerType_ObjGolonRock)
		{
			sizeof(MoveObjGolonRock);
		}

		DEFINE_RTTI;

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
		{
			return GetRuntimeTypeInfoStatic();
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			auto* pContextParam = GetOwnerMovement()->GetContextParam();

			switch ((Mode)MovementMode)
			{
			case Mode::eMode_Shoot:
			{
				ElapsedTime += in_rUpdateInfo.deltaTime;

				float scalar = -(YOffset * 2.0f / PopupTime * ElapsedTime - OffsetMagnitude);
				if (ElapsedTime <= PopupTime)
				{
					csl::math::Vector3 point{}, normal{}, tangent{};
					PathEvaluator.GetPNT(PathEvaluator.Distance, &point, &normal, &tangent);

					csl::math::Vector3 rotationDir{ csl::math::Matrix34(csl::math::Quaternion(Eigen::AngleAxisf(Unk8, tangent))) * normal };

					pContextParam->Position = { point + rotationDir * scalar };
					pContextParam->Rotation = { math::Matrix34OrthonormalDirection(tangent, { -rotationDir }) };
					break;
				}

				if (RollWaitTime >= 0.0f)
				{
					RollWaitTime -= in_rUpdateInfo.deltaTime;
					break;
				}

				scalar = OffsetMagnitude - YOffset * 2.0f;
				OffsetMagnitude = scalar;
				if (!pOwner)
				{
					csl::math::Vector3 point{}, normal{}, tangent{};
					PathEvaluator.GetPNT(PathEvaluator.Distance, &point, &normal, &tangent);

					csl::math::Vector3 rotationDir{ csl::math::Matrix34(csl::math::Quaternion(Eigen::AngleAxisf(Unk8, tangent))) * normal };

					pContextParam->Position = { point + rotationDir * scalar };
					pContextParam->Rotation = { math::Matrix34OrthonormalDirection(tangent, { -rotationDir }) };
					break;
				}

				if (MoveEndMemFunc)
					(pOwner->*MoveEndMemFunc)();

				break;
			}
			case Mode::eMode_Move:
			{
				csl::math::Vector3 rotationDir{ UpdateRotDirPathToPos(in_rUpdateInfo.deltaTime) };
				pContextParam->Position = { UpdateMovePathPos(in_rUpdateInfo.deltaTime) + rotationDir * OffsetMagnitude };
				pContextParam->Rotation = { math::Matrix34OrthonormalDirection(PathEvaluator.GetTangent(PathEvaluator.Distance), { -rotationDir }) };

				Direction = { (OffsetMagnitude + YOffset) * Unk3, 0.0f, Speed * in_rUpdateInfo.deltaTime };

				UpdateLocalRotRad(in_rUpdateInfo.deltaTime);

				if (!IsCheckFall || !CheckFall(rotationDir, in_rUpdateInfo.deltaTime))
				{
					if (IsPassOverPlayer() && pOwner && PassPlayerMemFunc)
						(pOwner->*PassPlayerMemFunc)();
				}
				else
				{
					if (pOwner && MoveEndMemFunc)
						(pOwner->*MoveEndMemFunc)();
				}

				break;
			}
			case Mode::eMode_Fall:
			{
				csl::math::Vector3 gravityDir{ GetOwnerMovement()->activeObject->GetComponent<game::GOCGravity>()->GetGravityDirection() };
				pContextParam->Velocity += csl::math::Vector3(gravityDir * Unk5 * in_rUpdateInfo.deltaTime);
				pContextParam->Position += csl::math::Vector3(pContextParam->Velocity * in_rUpdateInfo.deltaTime);

				UpdateLocalRotRad(in_rUpdateInfo.deltaTime);

				ElapsedTime += in_rUpdateInfo.deltaTime;
				if (ElapsedTime <= Unk6)
					break;

				if (pOwner && MoveEndMemFunc)
					(pOwner->*MoveEndMemFunc)();

				break;
			}
			default:
				break;
			}
		}

		void UpdateLocalRotRad(float in_deltaTime)
		{
			float angle{};

			csl::math::Vector3 direction{ Direction };
			float length = math::Vector3NormalizeWithLength(direction, &direction);
			if (length > 0.0f)
			{
				csl::math::Vector3 forwardVec{ math::Vector3RotateY(RadianLocalRotation, { csl::math::Vector3::UnitZ() }) };

				float scalar = acosf(csl::math::Clamp(forwardVec.dot(direction), -1.0f, 1.0f));

				if (scalar >= MATHF_PI / 6.0f * in_deltaTime)
				{
					scalar = csl::math::Min(scalar, MATHF_PI / 3.0f * in_deltaTime);
					angle = csl::math::Select(forwardVec.cross(csl::math::Vector3::UnitY()).dot(direction), fabs(scalar), csl::math::Nabs(scalar));
				}
			
				RadianLocalRotation = csl::math::Clamp(RadianLocalRotation + angle, -(MATHF_PI / 3.0f), MATHF_PI / 3.0f);
			}

			Unk11 = SonicUSA::System::RadianMaskS(Unk11 + length / YOffset);
		}

		csl::math::Vector3 UpdateMovePathPos(float in_deltaTime)
		{
			float distance = Speed * in_deltaTime + PathEvaluator.Distance;
			if (distance > 0.0f || distance < PathEvaluator.GetLength())
				PathEvaluator.SetDistance(distance);
		
			return PathEvaluator.GetWorldPosition(PathEvaluator.Distance);
		}

		csl::math::Vector3 UpdateRotDirPathToPos(float in_deltaTime)
		{
			csl::math::Vector3 point{}, normal{}, tangent{};
			PathEvaluator.GetPNT(PathEvaluator.Distance, &point, &normal, &tangent);

			if (!Unk4)
				return math::Vector3Rotate({ Eigen::AngleAxisf(Unk8, tangent) }, normal);
		
			auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetOwnerMovement()->activeObject->GetDocument(), 0);
			if (!pPlayerInfo)
				return { csl::math::Vector3::UnitY() };

			csl::math::Vector3 offset{ pPlayerInfo->Position - point };
			offset = { offset - tangent * offset.dot(tangent) };

			if (!math::Vector3NormalizeIfNotZero(offset, &offset))
				return { csl::math::Vector3::UnitY() };
		
			csl::math::Vector3 binormal{ math::Vector3Rotate({ Eigen::AngleAxisf(Unk8, tangent) }, normal) };
			float scalar = acosf(csl::math::Clamp(binormal.dot(offset), -1.0f, 1.0f));
			float otherScalar = Unk1 * in_deltaTime;

			if (offset.dot(tangent.cross(binormal)) < 0.0f)
			{
				otherScalar = -otherScalar;
				scalar = -scalar;
			}

			Unk3 = csl::math::Clamp(Unk3 + otherScalar, -(Unk2 * in_deltaTime), Unk2 * in_deltaTime);
			if (Unk3 > 0.0f && scalar > 0.0f || Unk3 < 0.0f && scalar < 0.0f)
			{
				if (fabs(Unk3) > fabs(scalar))
					Unk3 = csl::math::Lerp(Unk3, scalar, csl::math::Min(10.0f * in_deltaTime, 1.0f));
			}

			Unk8 = SonicUSA::System::RadianMaskS(Unk8 + Unk3);

			return math::Vector3Rotate({ Eigen::AngleAxisf(Unk8, tangent) }, normal);
		}

		csl::math::Vector3 UpdateRotDirPathToPosKeepRotAngVel(float in_deltaTime)
		{
			csl::math::Vector3 point{}, normal{}, tangent{};
			PathEvaluator.GetPNT(PathEvaluator.Distance, &point, &normal, &tangent);

			Unk8 = SonicUSA::System::RadianMaskS(Unk8 + Unk3);
		
			csl::math::Matrix34 rotationMatrix{ csl::math::Quaternion(Eigen::AngleAxisf(Unk8, tangent)) };
			return { rotationMatrix * csl::math::Vector4(normal, 1.0f) };
		}

		bool CheckFall(const csl::math::Vector3& in_rPosition, float in_deltaTime)
		{
			bool result = 0;

			int unknown[]{ -1, -1, -1 };
			if (!rpRaycastJob->m_Commands.empty())
			{
				for (size_t i = 0; i < rpRaycastJob->m_Commands.size(); i++)
				{
					unknown[i] = 1;
					if (rpRaycastJob->m_Commands[i].m_IsHit)
						unknown[i] = 0;
				}

				rpRaycastJob->Clear();
			}

			auto* pMovementGoc = GetOwnerMovement();
			auto* pContextParam = pMovementGoc->GetContextParam();

			if (unknown[0] == 1 && unknown[2] == 1)
			{
				float scalar = csl::math::Select(Unk3, fabs(Unk2 * in_deltaTime), csl::math::Nabs(Unk2 * in_deltaTime));
				if (unknown[1] || unknown[1] == 1)
					scalar *= 1.0f;
				else
					scalar *= -1.0f;

				pContextParam->Velocity = { math::Vector3Rotate(pContextParam->Rotation, { OffsetMagnitude * scalar, 0.0f, Speed * in_deltaTime }) * 1.0f / in_deltaTime };
				
				result = true;
			}

			rpRaycastJob->Add(pContextParam->Position, { pContextParam->Position + in_rPosition * (YOffset * 2.0f) }, 0xC996, 0, 1);
			if (unknown[0] == 1)
			{
				float masks[2]{};

				csl::math::Vector3 point{}, normal{}, tangent{};
				PathEvaluator.GetPNT(PathEvaluator.Distance, &point, &normal, &tangent);

				masks[0] = SonicUSA::System::RadianMaskS(Unk8 + csl::math::Select(Unk3, fabs(YOffset * 0.5f / (OffsetMagnitude + YOffset)), csl::math::Nabs(YOffset * 0.5f / (OffsetMagnitude + YOffset))));
				masks[1] = SonicUSA::System::RadianMaskS(Unk8 - csl::math::Select(Unk3, fabs(YOffset * 0.5f / (OffsetMagnitude + YOffset)), csl::math::Nabs(YOffset * 0.5f / (OffsetMagnitude + YOffset))));

				for (size_t i = 0; i < 2; i++)
				{
					csl::math::Matrix34 rotationMatrix{ csl::math::Quaternion(Eigen::AngleAxisf(masks[i], tangent)) };
					csl::math::Vector3 offset{ rotationMatrix * csl::math::Vector4(normal, 1.0f) };
					
					csl::math::Vector3 from{ point + offset * OffsetMagnitude };
					rpRaycastJob->Add(from, { from + offset * (YOffset + 2.0f) }, 0xC996, 0, 1);
				}
			}

			pPhysicsWorld->AddRaycastJob(rpRaycastJob);

			return result;
		}

		csl::math::Quaternion GetLocalRotate() const
		{
			csl::math::Quaternion rotation{ csl::math::QuaternionMultiply({ Eigen::AngleAxisf(RadianLocalRotation, csl::math::Vector3::UnitY()) }, { Eigen::AngleAxisf(Unk11, -csl::math::Vector3::UnitX()) }) };
			
			return csl::math::QuaternionNormalize(rotation);
		}

		csl::math::Vector3 GetWorldMoveDir() const
		{
			auto* pMovementGoc = GetOwnerMovement();

			csl::math::Vector3 direction{ math::Vector3Rotate(pMovementGoc->GetContextParam()->Rotation, Direction) };
			if (math::Vector3NormalizeIfNotZero(direction, &direction))
				return direction;
		
			return { PathEvaluator.GetTangent(PathEvaluator.Distance) * csl::math::Select(Unk3, fabs(1.0f), csl::math::Nabs(-1.0f)) };
		}

		bool IsPassOverPlayer() const
		{
			auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetOwnerMovement()->activeObject->GetDocument(), 0);
			if (!pPlayerInfo)
				return false;

			csl::math::Vector3 point{}, normal{}, tangent{};
			PathEvaluator.GetPNT(PathEvaluator.Distance, &point, &normal, &tangent);

			csl::math::Vector3 distance{ pPlayerInfo->Position - point };
			distance = { distance - normal * distance.dot(normal) };
			tangent = { tangent * csl::math::Select(Speed, fabs(1.0f), csl::math::Nabs(-1.0f)) };
			
			if (tangent.dot(distance) >= 0.0f)
				return false;

			if (distance.squaredNorm() > 90000.0f)
				return true;
		
			return false;
		}

		void Setup(const SetupParam& in_rSetupParam)
		{
			YOffset = in_rSetupParam.YOffset;
			PopupTime = in_rSetupParam.PopupTime;
			RollWaitTime = in_rSetupParam.RollWaitTime;
			Speed = in_rSetupParam.Speed;
			Unk1 = in_rSetupParam.Unk1;
			Unk2 = in_rSetupParam.Unk2;
			Unk3 = in_rSetupParam.Unk3;
			Unk4 = in_rSetupParam.Unk4;
			Unk5 = in_rSetupParam.Unk5;
			Unk6 = in_rSetupParam.Unk6;
			IsCheckFall = in_rSetupParam.IsCheckFall;
			MoveEndMemFunc = in_rSetupParam.MoveEndMemFunc;
			PassPlayerMemFunc = in_rSetupParam.PassPlayerMemFunc;
			pOwner = in_rSetupParam.pOwner;

			auto* pDocument = GetOwnerMovement()->activeObject->GetDocument();
			pPhysicsWorld = pDocument->GetService<CPhysicsWorld>();
			rpRaycastJob = new(pOwner->GetAllocator()) PhysicsRaycastJob();
			
			auto* pGravityField = ObjUtil::GetGravityField(*pDocument, in_rSetupParam.Position);
			if (!pGravityField)
				return;
			
			auto* pGravityPath = ObjUtil::GetGravityPathInsideCylinder(pGravityField);
			if (!pGravityPath)
				return;

			PathEvaluator.SetPathObject(pGravityPath);

			float distance{};
			PathEvaluator.GetClosestPositionAlongSpline(in_rSetupParam.Position, 0.0f, PathEvaluator.GetLength(), &distance);
			PathEvaluator.SetDistance(distance);

			csl::math::Vector3 point{}, normal{}, tangent{};
			PathEvaluator.GetPNT(PathEvaluator.Distance, &point, &normal, &tangent);

			csl::math::Vector3 offset{ in_rSetupParam.Position - point };
			OffsetMagnitude = offset.norm();

			if (!math::Vector3NormalizeIfNotZero(offset, &offset))
				return;
		
			Unk8 = acosf(csl::math::Clamp(normal.dot(offset), -1.0f, 1.0f));
			if (tangent.cross(normal).dot(offset) < 0.0f)
				Unk8 = -Unk8;
		}

		void StartMode(csl::ut::Enum<Mode, char> in_mode)
		{
			MovementMode = in_mode;
			ElapsedTime = 0.0f;
		}
	};
}