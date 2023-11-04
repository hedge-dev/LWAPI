#pragma once

namespace app::Player
{
	struct SCinfo
	{
		int Unk1{};
		csl::math::Vector3 Position{};
		csl::math::Quaternion Rotation{};
		float DeadLine{ -5000.0f };
		float EagleAltitude{};
		csl::ut::Bitset<ushort> Flags{};
		bool Unk3{};
		int Unk4{};
		const csl::ut::InplaceMoveArray<app::Game::EPhantomType, app::Game::EPhantomType::ePhantom_Max>* pPhantoms{};
	};

	struct RegisterCompornentsInfo;
	class CStateGOC;
	class CVisualGOC;
	class CPathService;
	class SVisualCinfo;
	class CHomingTargetService;

	typedef int EActionFlag;

	class CPlayer : public GameObject3D
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpChangeDimension, ASLR(0x00851DA0), CPlayer*, bool, bool, game::PathComponent*, float);

	public:
		INSERT_PADDING(8) {};
		CWorld* pWorld{};
		CGOCCollection<10> Components{};
		INSERT_PADDING(4); // app::ut::RefPtr<CPostureInputManager>
		INSERT_PADDING(4); // app::ut::RefPtr<CPostureMoveManager>
		ut::RefPtr<CPhysics> rpPhysics{};
		ut::RefPtr<CBlackBoard> rpBlackboard{};
		ut::ScopedPtr<CPathService> spPathService{ nullptr, nullptr };
		ut::ScopedPtr<CHomingTargetService> spHomingService{ nullptr, nullptr };
		const SCinfo* pCinfo{};
		ut::ScopedPtr<SVisualCinfo> spVisualCinfo{nullptr, nullptr};
		size_t CameraId{};
		void* Unk1{};
		GameObjectHandle<CPlayerVehicle> Vehicle{};
		app::ut::RefPtr<Camera::CCameraController> rpCamera{};
		INSERT_PADDING(20) {};
		
		CPlayer()
		{
			
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			/*auto* pCollector = GetComponent<GOCCollector>();
			if (pCollector)
				pCollector->UpdateChangeRequest();
			
			rpPhysics->UpdateBeforeMove(in_rUpdateInfo.deltaTime);
			
			auto* pInput = GetComponent<GOCCharacterInput>();
			if (pInput)
				pInput->UpdateManual();
			
			rpInputManager->Update(in_rUpdateInfo);
			rpMoveManager->Update(in_rUpdateInfo);
			
			GetPlayerGOC<CStateGOC>()->Update(in_rUpdateInfo);
			
			UpdateTransform();
			
			Components.Update(in_rUpdateInfo);

			rpPhysics->UpdateAfterMove(in_rUpdateInfo.deltaTime);
			
			GetPlayerGOC<CVisualGOC>()->Update(in_rUpdateInfo);
			GetPlayerGOC<CEffectGOC>()->Update(in_rUpdateInfo);
			
			UpdatePlayerInformation();
			
			UpdateGroundShapeInfo();

			rpPhysics->UpdateHistoryData(in_rUpdateInfo.deltaTime);

			if (rpBlackboard->Unk1[2].test(4))
				UpdateApplyGravityFromDirection(in_rUpdateInfo.deltaTime);*/
		}

		template <typename T>
		T* GetPlayerGOC() const
		{
			return Components.GetGOC<T>();
		}

		CStateGOC* GetStateGOC() const
		{
			return Components.GetGOC<CStateGOC>();
		}

		size_t GetGameID()
		{
			return GetDocument()->GameActorID;
		}

		size_t GetCameraActorID()
		{
			return GetLevelInfo()->Cameras[GetPlayerNo()];
		}

		size_t GetRCActorID()
		{
			return GetLevelInfo()->RcActor;
		}

		bool HaveVehicle()
		{
			return Vehicle.IsValid();
		}

		CPlayerVehicle* GetPlayerVehicle()
		{
			return Vehicle.Get();
		}

		void SetPlayerVehicle(CPlayerVehicle* in_pVehicle)
		{
			Vehicle = in_pVehicle;
		}

		size_t GetPlayerNo() const
		{
			return rpBlackboard->PlayerNo;
		}

		size_t GetRivalActorID()
		{
			return GetLevelInfo()->GetPlayerID(GetPlayerNo() == 0);
		}

		size_t GetRivalPlayerNo() const
		{
			return GetPlayerNo() == 0;
		}

		size_t GetHudID()
		{
			return GetLevelInfo()->HudActor;
		}

		float GetParameter(size_t in_parameter) const
		{
			return GetPlayerGOC<CParameterGOC>()->Get(in_parameter);
		}

		CLevelInfo* GetLevelInfo() const
		{
			return GetDocument()->GetService<CLevelInfo>();
		}

		CWorld* GetWorld() const
		{
			return pWorld;
		}

		void ChangeToTopView(bool in_isTopView)
		{
			GetPlayerGOC<CParameterGOC>()->ChangeParam(in_isTopView ? 3 : 2);
		}

		void ChangeDimension(bool in_unk, bool in_unk2, game::PathComponent* in_pComponent, float in_unk3)
		{
			ms_fpChangeDimension(this, in_unk, in_unk2, in_pComponent, in_unk3);
		}

		void UpdatePlayerInformation();

		void UpdateTransform()
		{
			GetComponent<fnd::GOCTransform>()->SetLocalTranslationAndRotation(rpPhysics->Position, rpPhysics->Rotation);
		}

		void InitializePlayerInformation()
		{
			UpdatePlayerInformation();
		}

		void SendMessageImmToRC(fnd::Message& in_rMessage)
		{
			if (GetRCActorID() == 0)
				return;
			
			SendMessageImm(GetRCActorID(), in_rMessage);
		}
	};

	static CPlayer* CreatePlayer(GameDocument* in_pDocument, SCinfo& in_rCreateInfo)
	{
		FUNCTION_PTR(CPlayer*, __cdecl, fpCreatePlayer, ASLR(0x0085A8F0), GameDocument*, SCinfo&);
		return fpCreatePlayer(in_pDocument, in_rCreateInfo);
	}
}