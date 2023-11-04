#pragma once

namespace app
{
	class ObjCocco;

	class MoveObjCocco : public game::MoveController
	{
	public:
		struct alignas(16) CallbackHandle
		{
#pragma pack(4)
			void (GameObject::* NotifyStopMemFunc)() {};
#pragma pack()
			GameObject* pOwner{};
		};

		enum MoveType : byte
		{
			eMoveType_None,
			eMoveType_TargetPoint,
			eMoveType_RelativeTargetPoint,
			eMoveType_TargetDirection,
			eMoveType_TargetDirectionJump,
			eMoveType_TargetPlayer
		};

		enum State : byte
		{
			eState_Unk0,
			eState_Unk1,
		};

		CallbackHandle Callback{};
		csl::ut::Enum<MoveType, byte> Type{};
		csl::math::Vector3 TargetPosition{};
		csl::math::Vector3 TargetDirection{};
		float Speed{};
		alignas(16) csl::ut::Enum<State, byte> CurrentState{ State::eState_Unk1 };

		MoveObjCocco() : game::MoveController(game::MoveControllerType::eMoveControllerType_ObjCocco)
		{

		}

		DEFINE_RTTI;

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
		{
			return GetRuntimeTypeInfoStatic();
		}

		void OnEnter() override
		{
			TargetDirection = math::Vector3Rotate(GetOwnerMovement()->GetContextParam()->Rotation, { csl::math::Vector3::UnitZ() });
		}

		void OnLeave() override
		{
			
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			if (Type == MoveType::eMoveType_None)
				return;

			auto* pMovementGoc = GetOwnerMovement();
			auto* pContextParam = pMovementGoc->GetContextParam();

			csl::math::Vector3 position{ pContextParam->Position };
			csl::math::Vector3 upVector{ math::Vector3Rotate(pContextParam->Rotation, { csl::math::Vector3::UnitY() }) };
			csl::math::Vector3 leftVector{ math::Vector3Rotate(pContextParam->Rotation, { csl::math::Vector3::UnitZ() }) };
			csl::math::Vector3 target{};
			csl::math::Vector3 destination{};
			csl::math::Vector3 downVector{};

			switch ((MoveType)Type)
			{
			case MoveType::eMoveType_TargetPoint:
			{
				target = { TargetPosition };
				destination = { target - pContextParam->Position };

				break;
			}
			case MoveType::eMoveType_RelativeTargetPoint:
			{
				if (auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*pMovementGoc->pActiveObject->GetDocument(), 0))
				{
					target = { pPlayerInfo->Position + TargetPosition };
					destination = { target - pContextParam->Position };
				}

				break;
			}
			case MoveType::eMoveType_TargetDirection:
			case MoveType::eMoveType_TargetDirectionJump:
			{
				target = { pContextParam->Position };
				destination = { TargetPosition };

				break;
			}
			case MoveType::eMoveType_TargetPlayer:
			{
				target = { pContextParam->Position };

				auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*pMovementGoc->pActiveObject->GetDocument(), 0);
				if (!pPlayerInfo)
				{
					destination = { TargetPosition };
					break;
				}

				if (pContextParam->Velocity.squaredNorm() <= 40000.0f)
				{
					destination = { pPlayerInfo->Position - pContextParam->Position };
					break;
				}
				else
				{
					csl::math::Vector3 playerVelocity{};
					math::Vector3Normalize(pPlayerInfo->Velocity, &playerVelocity);
					destination = { pPlayerInfo->Position + playerVelocity * 100.0f - pContextParam->Position };

					break;
				}

				break;
			}
			case MoveType::eMoveType_None:
			default:
			{
				break;
			}
			}

			destination -= csl::math::Vector3(upVector * destination.dot(upVector));
			math::Vector3NormalizeZero(destination, &destination);

			float scalar = fabs(acosf(csl::math::Clamp(destination.dot(leftVector), -1.0f, 1.0f)));
			if (scalar > 0.000001f)
			{
				float angle = MATHF_PI * 4.0f * in_rUpdateInfo.DeltaTime;
				if (angle >= scalar)
				{
					if (Type == MoveType::eMoveType_TargetPlayer)
					{
						TargetPosition = destination;
						Type = MoveType::eMoveType_TargetDirection;
					}
				}
				else
				{
					csl::math::Vector3 frontVector{ math::Vector3Rotate(pContextParam->Rotation, { csl::math::Vector3::UnitX() }) };
					destination = math::Vector3Rotate({ Eigen::AngleAxisf(csl::math::Select(frontVector.dot(destination), fabs(angle), csl::math::Nabs(angle)), upVector) }, leftVector);
				}
			}

			csl::math::Vector3 velocity{ upVector * pContextParam->Velocity.dot(upVector) };

			if (CurrentState == State::eState_Unk1)
			{
				if (Type != MoveType::eMoveType_RelativeTargetPoint)
					downVector = { -upVector * 100.0f };
				else
					downVector = { -upVector * 2.0f };
			}

			pContextParam->Velocity = { destination * Speed + velocity + downVector * in_rUpdateInfo.DeltaTime };
			pContextParam->Position += csl::math::Vector3(pContextParam->Velocity * in_rUpdateInfo.DeltaTime);
			TargetDirection = destination;

			csl::math::Vector3 normalizedDir{ TargetDirection - upVector * TargetDirection.dot(upVector) };
			math::Vector3NormalizeZero(normalizedDir, &normalizedDir);

			csl::math::Vector3 front{ upVector.cross(normalizedDir) };
			csl::math::Vector3 left{ front.cross(upVector) };

			math::Vector3NormalizeZero(front, &front);
			csl::math::Matrix34 rotationMtx{};
			rotationMtx.SetColumn(0, front);
			rotationMtx.SetColumn(1, upVector);
			rotationMtx.SetColumn(2, left);
			pContextParam->Rotation = { rotationMtx };

			switch ((State)CurrentState)
			{
			case State::eState_Unk0:
			{
				csl::math::Vector3 from{ pContextParam->Position + upVector * 5.0f };
				csl::math::Vector3 to{ pContextParam->Position - upVector * 0.5f };

				game::PhysicsRaycastOutput output{};
				if (ObjUtil::RaycastNearestCollision(&output, *pMovementGoc->pActiveObject->GetDocument(), from, to, 0xC996))
				{
					if ((output.Attribute & 0x10) == 0)
					{
						pContextParam->Velocity -= csl::math::Vector3(upVector * pContextParam->Velocity.dot(upVector));
						pContextParam->Position = output.HitPoint;
					}
				}
				else
				{
					CurrentState = State::eState_Unk1;
				}

				break;
			}
			case State::eState_Unk1:
			{
				csl::math::Vector3 to{ pContextParam->Position };

				csl::math::Vector3 offsetPosition{ position - pContextParam->Position };
				float length = math::Vector3NormalizeWithLength(offsetPosition, &offsetPosition);

				csl::math::Vector3 from{ pContextParam->Position + offsetPosition * (length + 0.1f) };

				game::PhysicsRaycastOutput output{};
				if (ObjUtil::RaycastNearestCollision(&output, *pMovementGoc->pActiveObject->GetDocument(), from, to, 0xC996)
					&& (output.Attribute & 0x10) == 0)
				{
					CurrentState = State::eState_Unk0;
					pContextParam->Position = output.HitPoint;
				}

				break;
			}
			default:
			{
				break;
			}
			}

			if (Type == MoveType::eMoveType_None)
				return;

			if (Type <= MoveType::eMoveType_RelativeTargetPoint)
			{
				csl::math::Vector3 distance{ target - position };
				distance -= csl::math::Vector3(upVector * distance.dot(upVector));

				csl::math::Vector3 newDistance{ target - pContextParam->Position };
				newDistance -= csl::math::Vector3(upVector * newDistance.dot(upVector));

				if (distance.dot(newDistance) <= 0.0f || newDistance.norm() <= 5.0f)
				{
					pMovementGoc->DisableMovementFlag(0);
					if (Callback.pOwner && Callback.NotifyStopMemFunc)
						(Callback.pOwner->*Callback.NotifyStopMemFunc)();
				}
			}
			else if (Type == MoveType::eMoveType_TargetDirectionJump && CurrentState == State::eState_Unk0)
			{
				pMovementGoc->DisableMovementFlag(0);
				if (Callback.pOwner && Callback.NotifyStopMemFunc)
					(Callback.pOwner->*Callback.NotifyStopMemFunc)();
			}
		}

		void SetTargetPoint(const csl::math::Vector3& in_rTargetPoint, float in_speed)
		{
			Type = MoveType::eMoveType_TargetPoint;
			TargetPosition = in_rTargetPoint;
			Speed = in_speed;

			GetOwnerMovement()->EnableMovementFlag(0);
		}

		void SetRelativeTargetPoint(const csl::math::Vector3& in_rTargetPoint, float in_speed)
		{
			Type = MoveType::eMoveType_RelativeTargetPoint;
			TargetPosition = in_rTargetPoint;
			Speed = in_speed;

			GetOwnerMovement()->EnableMovementFlag(0);
		}

		void SetTargetDirection(const csl::math::Vector3& in_rTargetDirection, float in_speed)
		{
			Type = MoveType::eMoveType_TargetDirection;
			TargetPosition = in_rTargetDirection;
			Speed = in_speed;

			GetOwnerMovement()->EnableMovementFlag(0);
		}

		void SetTargetDirectionJump(const csl::math::Vector3& in_rJumpDirection, float in_speed, float in_velocity)
		{
			Type = MoveType::eMoveType_TargetDirectionJump;
			TargetPosition = in_rJumpDirection;
			Speed = in_speed;
			CurrentState = State::eState_Unk1;

			GetOwnerMovement()->GetContextParam()->Velocity = { 0.0f, in_velocity, 0.0f };
		}

		void SetTargetPlayer(float in_speed, float in_velocity)
		{
			auto* pMovementGoc = GetOwnerMovement();
			auto* pContextParam = pMovementGoc->GetContextParam();

			csl::math::Vector3 direction{ math::Vector3Rotate(pContextParam->Rotation, {csl::math::Vector3::UnitY()}) };

			auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*pMovementGoc->pActiveObject->GetDocument(), 0);
			if (!pPlayerInfo)
				return;

			csl::math::Vector3 offset{ pPlayerInfo->Position - pContextParam->Position };
			offset -= csl::math::Vector3(direction * offset.dot(direction));
			math::Vector3NormalizeZero(offset, &offset);

			Type = MoveType::eMoveType_TargetPlayer;
			TargetPosition = offset;
			Speed = in_speed;
			CurrentState = State::eState_Unk1;

			pContextParam->Velocity = { 0.0f, in_velocity, 0.0f };
			pMovementGoc->EnableMovementFlag(0);
		}

		void SetNotifyStopCallback(void (ObjCocco::* in_pMemFunc)(), ObjCocco* in_pOwner)
		{
			Callback.NotifyStopMemFunc = csl::ut::union_cast<void (GameObject::*)()>(in_pMemFunc);
			Callback.pOwner = reinterpret_cast<GameObject*>(in_pOwner);
		}
	};
}