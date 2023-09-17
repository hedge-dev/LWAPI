#pragma once

namespace app
{
	class EnemyKeese;

	class MoveEnemyKeese : public game::MoveController
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x006C8C50), MoveEnemyKeese*, const fnd::SUpdateInfo&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetPath, ASLR(0x00689F70), MoveEnemyKeese*, game::PathComponent*, float);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetTargetDirection, ASLR(0x006C91E0), MoveEnemyKeese*, const csl::math::Vector3&, float);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpResetCurrent, ASLR(0x006C8820), MoveEnemyKeese*);

	public:
		struct PathBasePositionData
		{
			csl::math::Vector3 Unk1{};
			csl::math::Vector3 Unk2{};
			csl::math::Vector3 Unk3{};
			float Distance{};
			float Unk5{};
		};

		struct CallbackHandle
		{
#pragma pack(4)
			void (GameObject::* NotifyStopMemFunc)() {};
#pragma pack()
			GameObject* pOwner{};
		};
		
		PathBasePositionData Unk1{};
		PathBasePositionData Unk2{};
		PathBasePositionData Unk3{};
		PathBasePositionData Target{};
		game::PathEvaluator Path{};
		float Speed{ 10.0f };
		float RotateSpeed{ 30.0f };
		float Unk7{ -1.0f };
		float Unk8{};
		int Unk9{};
		bool Unk10{};
		CallbackHandle Callback{};

		MoveEnemyKeese() : game::MoveController(game::MoveControllerType::eMoveControllerType_EnemyKeese)
		{
			sizeof(CallbackHandle);
			ASSERT_OFFSETOF(MoveEnemyKeese, Callback, 0x138);
		}

		DEFINE_RTTI_PTR(ASLR(0x00F9B158));

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
		{
			return GetRuntimeTypeInfoStatic();
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			ms_fpUpdate(this, in_rUpdateInfo);
		}

		void StartMove()
		{
			auto* pMovementGoc = GetOwnerMovement();
			pMovementGoc->EnableMovementFlag(0);
			pMovementGoc->EnableMovementFlag(1);
		}

		void StopMove()
		{
			auto* pMovementGoc = GetOwnerMovement();
			pMovementGoc->DisableMovementFlag(0);
			pMovementGoc->DisableMovementFlag(1);
		}

		void SetPath(game::PathComponent* in_pComponent, float in_distance)
		{
			ms_fpSetPath(this, in_pComponent, in_distance);
		}

		void SetSpeed(float in_speed)
		{
			Speed = in_speed;
		}

		void SetRotateSpeed(float in_rotateSpeed)
		{
			RotateSpeed = in_rotateSpeed;
		}

		void SetTargetDirection(const csl::math::Vector3& in_rTargetDirection, float in_distance)
		{
			ms_fpSetTargetDirection(this, in_rTargetDirection, in_distance);
		}

		void SetTargetDistance(float in_targetDistance)
		{
			Target.Distance = Unk3.Distance + in_targetDistance;
		}

		void SetNotifyStopCallback(void (EnemyKeese::* in_pMemFunc)(), EnemyKeese* in_pOwner)
		{
			Callback.NotifyStopMemFunc = csl::ut::union_cast<void (GameObject::*)()>(in_pMemFunc);
			Callback.pOwner = reinterpret_cast<GameObject*>(in_pOwner);
		}

		void ResetCurrent()
		{
			ms_fpResetCurrent(this);
		}
	};
}