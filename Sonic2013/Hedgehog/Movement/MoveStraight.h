#pragma once

namespace app::game
{
	class MoveStraightCallback
	{
	public:
		typedef void invoker_t(void* obj, void* func);

	protected:
		invoker_t* m_fpInvoker{};
#pragma pack(4)
		void (GameObject::* MemFunc)() {};
#pragma pack()
		float Unk1{ -1.0f };
		int Unk2{};

	public:
		MoveStraightCallback()
		{

		}

		template <typename T>
		MoveStraightCallback(void(T::*in_pFunc)())
		{
			m_fpInvoker = &memFuncInvoker<T>;
			MemFunc = union_cast<void (GameObject::*)()>(in_pFunc);
		}

		template<typename T>
		static void memFuncInvoker(void* in_pObj, void* in_pFunc)
		{
			T* pObj = static_cast<T*>(in_pObj);
			void (T::**pFunc)() = static_cast<void (T::**)()>(in_pFunc);
			(pObj->*(*pFunc))();
		}
	};

	class MoveStraight : public MoveController
	{
	public:
		enum GravityType : byte;

		struct SetupParam
		{
			csl::math::Vector3 Position{};
			csl::math::Quaternion Rotation{};
			float Unk3{ 100.0f };
			INSERT_PADDING(4) {};
			bool Unk4{ true };
			bool Unk5{ true };
			bool Unk6{};
			int Unk7{};
			csl::math::Vector3 CheckPositionOffset{};
			csl::math::Vector3 Unk8{};
			csl::math::Vector3 Unk9{};
			float CheckCriffDistance{ 10.0f };
		};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpOnEnter, ASLR(0x004C90A0), MoveStraight*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x004C9400), MoveStraight*, const fnd::SUpdateInfo&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetupParameter, ASLR(0x004C9910), MoveStraight*, SetupParam&);

	public:
		MovementUtility::SideviewInterpolateInfo SideViewInfo{};
		PathEvaluator Path{};
		float MaxDistance{ -1.0f };
		float StartDistance{};
		csl::math::Vector3 Unk3{};
		csl::ut::MoveArray<csl::math::Vector3> LandingRaycastOffsets{};
		int Unk4{};
		int Unk5{ 4 };
		MoveStraightCallback Callback{};
		BarrierChecker Barrier{};
		float GravitySpeed{ 100.0f };
		size_t CollisionFilter{ 0xC992 };
		csl::ut::Bitset<byte> Unk8{};
		csl::ut::Enum<GravityType, byte> Unk9{ (GravityType)0 };

		DEFINE_RTTI_PTR(ASLR(0x00F6BEDC));

		MoveStraight() : MoveController(MoveControllerType::eMoveControllerType_Straight)
		{

		}

		const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override
		{
			return GetRuntimeTypeInfoStatic();
		}

		bool IsOnGround()
		{
			return Unk8.test(0);
		}

		bool IsSideView()
		{
			if (Unk9 != (GravityType)1 && Unk9 != (GravityType)3)
				return false;
		
			return true;
		}

		void AddLandingRaycastOffset(const csl::math::Vector3& in_rOffset)
		{
			LandingRaycastOffsets.push_back(in_rOffset);
		}

		void ClearLandingRaycastOffset()
		{
			LandingRaycastOffsets.clear();
		}

		void ChangeCheckBarricadeLineFv(const csl::math::Vector3& in_rVec)
		{
			if (!IsSideView())
				Barrier.SetCheckLine(in_rVec);
		}

		void ChangeCheckBarricadeLineSv(const csl::math::Vector3& in_rVec)
		{
			if (IsSideView())
				Barrier.SetCheckLine(in_rVec);
		}

		void ChangeCheckBarricadeOffset(const csl::math::Vector3& in_rVec)
		{
			Barrier.SetCheckPositionOffset(in_rVec);
		}

		float GetGravitySpeed() const
		{
			return GravitySpeed;
		}

		void SetGravitySpeed(float in_speed)
		{
			GravitySpeed = in_speed;
		}

		PathEvaluator* GetPath() const
		{
			return const_cast<PathEvaluator*>(&Path);
		}

		PathEvaluator* GetSVPath() const
		{
			return const_cast<PathEvaluator*>(&SideViewInfo.Path);
		}

		void SetCheckFallFlag(bool in_enable)
		{
			if (in_enable)
				Unk8.set(2);
			else
				Unk8.reset(2);

			Barrier.ChangeCheckBarrier({ Unk8.test(1), Unk8.test(2) });
		}

		void SetCollisionFilter(size_t in_filter)
		{
			CollisionFilter = in_filter;
			Barrier.SetCollisionFilter(in_filter);
		}

		void SetFixedHeightMove(bool in_enable)
		{
			Unk8.set(4, in_enable);
		}

		void SetMaxMoveDistance(float in_maxDistance, float in_startDistance)
		{
			MaxDistance = in_maxDistance;
			StartDistance = in_startDistance;
		}

		void SetupParameter(SetupParam& in_rParam)
		{
			ms_fpSetupParameter(this, in_rParam);
		}

		void SetNotifyStopCallback(MoveStraightCallback in_callback)
		{
			Callback = in_callback;
		}

		void OnEnter() override
		{
			ms_fpOnEnter(this);
			/*auto* pMovement = GetOwnerMovement();
			auto* pContextParam = pMovement->GetContextParam();

			if (Path.Component.IsValid())
			{
				float pathLength = Path.GetLength();
				float distance{};
				Path.GetClosestPositionAlongSpline(pContextParam->Position, distance, 0.0f, &pathLength);
				Path.SetDistance(distance);
			}

			if (SideViewInfo.Path.Component.IsValid())
			{
				float pathLength = SideViewInfo.Path.GetLength();
				float distance{};
				SideViewInfo.Path.GetClosestPositionAlongSpline(pContextParam->Position, distance, 0.0f, &pathLength);
				SideViewInfo.Path.SetDistance(distance);
			}*/
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			ms_fpUpdate(this, in_rUpdateInfo);
		}

		void DebugDraw()
		{

		}

		void DebugDrawGravity() const
		{

		}
	};
}