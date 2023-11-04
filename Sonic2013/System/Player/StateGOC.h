#pragma once
#pragma push_macro("SendMessage")
#undef SendMessage

namespace app::Player
{
	class CStatePlugin;
	class CStateBase;

	typedef int EDisableTimer;

	class CStateGOC : public CGOComponent
	{
	private:
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpIsTimerDisable, ASLR(0x0085AE20), const CStateGOC*, EDisableTimer, uint);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpIsTimerDisable2, ASLR(0x0085ADF0), const CStateGOC*, EDisableTimer);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetDisableTime, ASLR(0x0085ADC0), CStateGOC*, EDisableTimer, float, uint);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetDisableTime2, ASLR(0x0085AD90), CStateGOC*, EDisableTimer, float);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpIsOutOfControl, ASLR(0x0085AB00), const CStateGOC*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStartOutOfControl, ASLR(0x0085AAC0), CStateGOC*, float, bool);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpIsDamagedShape, ASLR(0x0085E0D0), CStateGOC*, const game::ColliShape*);
		inline static FUNCTION_PTR(int, __thiscall, ms_fpGetCurrentState, ASLR(0x0085AA90), const CStateGOC*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpChangeState, ASLR(0x0085B400), CStateGOC*, int);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpChangeStateAlways, ASLR(0x0085B450), CStateGOC*, int);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAddStateContextParameter, ASLR(0x0085BC40), CStateGOC*, const SStateParameter&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpVisualLocaterStartInterporation, ASLR(0x0085BCF0), CStateGOC*, float, uint);
		inline static FUNCTION_PTR(CPlayerStateParameter*, __thiscall, ms_fpGetContextParameter, ASLR(0x00C60A50), CStateGOC*);
		inline static FUNCTION_PTR(CStatePlugin*, __thiscall, ms_fpGetStatePluginPtr, ASLR(0x0085C410), CStateGOC*, const char*);
		inline static FUNCTION_PTR(CStatePlugin*, __thiscall, ms_fpAddStatePlugin, ASLR(0x0085C3F0), CStateGOC*, uint);
		inline static FUNCTION_PTR(CStatePlugin*, __thiscall, ms_fpRemoveStatePlugin, ASLR(0x0085C400), CStateGOC*, uint);

		inline static const char* ms_pStaticId = (char*)ASLR(0x00DF77D8);

	public:
		void* Unk1{};
		bool Unk2{};
		ut::internal::HsmImpl Hsm{};
		hh::eff::CInstanceHandle<hh::eff::CEffectInstance> Effect{};
		INSERT_PADDING(4);
		app::fnd::SoundHandle Sound{};
		CPlayer* pPlayer{};
		csl::fnd::IAllocator* pAllocator{ GetAllocator() };
		INSERT_PADDING(4); // ut::RefPtr<ut::StateManager<CStateGOC>> rpStateManager;
		INSERT_PADDING(4); // ut::RefPtr<StatePluginManager> rpPluginManager;
		ut::ScopedPtr<CPlayerStateParameter> spParameter{ nullptr, nullptr };
		INSERT_PADDING(4); // CTimerCounterList* pCounterList;
		float MoveCylinderTimer{};
		float Unk4{};
		int Unk5{};
		INSERT_PADDING(8)[6]; // SDisableTimer[6];
		csl::ut::MoveArray<fnd::Handle<const game::ColliShape>>* pShapes{};
		game::GOCSound* pSound{};
		bool Unk7{};

		GameDocument* GetDocument() const
		{
			return pPlayer->GetDocument();
		}

		CBlackBoard* GetBlackBoard() const
		{
			return pPlayer->rpBlackboard.get();
		}

		CVisualGOC* GetVisualGoc()
		{
			return pPlayer->GetPlayerGOC<CVisualGOC>();
		}

		CVisualGOC* GetVisualGoc() const
		{
			return pPlayer->GetPlayerGOC<CVisualGOC>();
		}

		size_t GetPlayerNo() const
		{
			return GetBlackBoard()->PlayerNo;
		}

		size_t GetToHudPlayerNumber() const
		{
			return GetPlayerNo();
		}

		CPhysics* GetPhysics()
		{
			return pPlayer->rpPhysics.get();
		}

		CPhysics* GetPhysics() const
		{
			return pPlayer->rpPhysics.get();
		}

		CAttackStatus* GetAttackStatus()
		{
			return GetBlackBoard()->GetAttackStatus();
		}

		CPathService* GetPathService()
		{
			return pPlayer->spPathService.get();
		}

		game::PathEvaluator* GetPath(PathType in_type)
		{
			return pPlayer->spPathService.get()->GetPathEvaluator(in_type);
		}

		CCollisionGOC* GetCollision()
		{
			return pPlayer->GetPlayerGOC<CCollisionGOC>();
		}

		CStatePlugin* GetStatePluginPtr(const char* in_pName)
		{
			return ms_fpGetStatePluginPtr(this, in_pName);
		}

		template <typename T>
		T* GetStatePlugin()
		{
			return static_cast<T*>(GetStatePluginPtr(T::ms_pName));
		}

		void AddStatePlugin(uint index)
		{
			ms_fpAddStatePlugin(this, index);
		}

		void RemoveStatePlugin(uint index)
		{
			ms_fpRemoveStatePlugin(this, index);
		}

		csl::math::Vector3 GetPosition() const
		{
			return GetPhysics()->Position;
		}

		csl::math::Quaternion GetRotation() const
		{
			return GetPhysics()->Rotation;
		}

		csl::math::Matrix34 GetMatrix() const
		{
			return GetPhysics()->PhysicsMatrix;
		}

		csl::math::Vector3 GetVelocity() const
		{
			return GetPhysics()->GetVelocity();
		}

		csl::math::Vector3 GetHorzVelocity() const
		{
			return GetPhysics()->GetHorzVelocity();
		}

		csl::math::Vector3 GetUpDirection() const
		{
			return GetPhysics()->GetUp();
		}

		int GetCurrentState() const
		{
			return ms_fpGetCurrentState(this);
		}

		bool IsTimerDisable(EDisableTimer in_timer) const
		{
			return ms_fpIsTimerDisable2(this, in_timer);
		}

		bool IsTimerDisable(EDisableTimer in_timer, uint in_unk) const
		{
			return ms_fpIsTimerDisable(this, in_timer, in_unk);
		}

		void SetDisableTime(EDisableTimer in_timer, float in_time, int in_unk1)
		{
			ms_fpSetDisableTime(this, in_timer, in_time, in_unk1);
		}

		void SetDisableTime(EDisableTimer in_timer, float in_time)
		{
			ms_fpSetDisableTime2(this, in_timer, in_time);
		}

		bool IsOutOfControl() const
		{
			return ms_fpIsOutOfControl(this);
		}

		void StartOutOfControl(float in_time, bool in_unk)
		{
			ms_fpStartOutOfControl(this, in_time, in_unk);
		}

		bool IsDamagedShape(const game::ColliShape* in_pShape)
		{
			return ms_fpIsDamagedShape(this, in_pShape);
		}

		void AddDamagedShape(const game::ColliShape* in_pShape)
		{
			pShapes->push_back({ in_pShape });
		}

		void ChangeState(int state)
		{
			ms_fpChangeState(this, state);
		}

		void ChangeStateAlways(int state)
		{
			ms_fpChangeStateAlways(this, state);
		}

		void SetAnimation(const char* in_pAnim)
		{
			GetVisualGoc()->GetHumanAnimation().SetAnimation(in_pAnim);
		}

		void ChangeAnimation(const char* pAnim)
		{
			GetVisualGoc()->ChangeAnimation(pAnim);
		}

		const char* GetCurrentAnimationName() const
		{
			return GetVisualGoc()->GetCurrentAnimationName();
		}

		void ChangeVisual(BodyMode mode)
		{
			GetVisualGoc()->ChangeVisual(mode);
		}
		
		static const char* staticID()
		{
			return ms_pStaticId;
		}

		float GetParameter(uint in_index) const
		{
			return pPlayer->GetParameter(in_index);
		}

		CPlayerStateParameter* GetContextParameter()
		{
			return ms_fpGetContextParameter(this);
		}

		template <typename T>
		T* CreateStateContextParameter()
		{
			T* pParam = static_cast<T*>(GetContextParameter()->GetParam(T::ms_pName));
			if (!pParam)
				return GetContextParameter()->CreateParameter<T>();

			return pParam;
		}

		void AddStateContextParameter(const SStateParameter& in_rParam)
		{
			ms_fpAddStateContextParameter(this, in_rParam);
		}

		bool IsNowSuperSonic() const
		{
			auto* pBlackBoard = GetBlackBoard();
			return pBlackBoard->Unk1[3].test(23);
		}

		bool SendMessageImm(uint in_actorId, fnd::Message& in_rMessage)
		{
			if (!in_actorId)
				return false;
			
			return pPlayer->SendMessageImm(in_actorId, in_rMessage);
		}

		bool SendMessageImm(GameObject* in_pObject, fnd::Message& in_rMessage)
		{
			return pPlayer->SendMessageImmToGameObject(in_pObject, in_rMessage);
		}

		void SendMessageToGame(fnd::Message& in_rMessage)
		{
			size_t gameActorId = pPlayer->GetGameID();
			if (!gameActorId)
				return;

			pPlayer->SendMessage(gameActorId, in_rMessage);
		}

		bool SendMessageImmToGame(fnd::Message& in_rMessage)
		{
			size_t gameActorId = pPlayer->GetGameID();
			if (!gameActorId)
				return false;
		
			return pPlayer->SendMessageImm(gameActorId, in_rMessage);
		}

		bool SendMessageImmToCamera(fnd::Message& in_rMessage)
		{
			size_t cameraActorId = pPlayer->GetCameraActorID();
			if (!cameraActorId)
				return false;

			return pPlayer->SendMessageImm(cameraActorId, in_rMessage);
		}

		void SendMessageToRival(fnd::Message& in_rMessage)
		{
			size_t rivalActorId = pPlayer->GetRivalActorID();
			if (!rivalActorId)
				return;

			pPlayer->SendMessage(rivalActorId, in_rMessage);
		}

		void SendMessageToHud(fnd::Message& in_rMessage)
		{
			size_t hudActorId = pPlayer->GetHudID();
			if (!hudActorId)
				return;

			pPlayer->SendMessage(hudActorId, in_rMessage);
		}

		bool ProcessMessageToCurrentState(fnd::Message& in_rMessage)
		{
			if (Hsm.HSM_STATE() == -1)
				return false;

			return Hsm.HSM_DISPATCH(in_rMessage);
		}

		bool IsOnGround() const
		{
			return GetPhysics()->IsOnGround();
		}

		bool Is2DMode() const
		{
			return GetBlackBoard()->Unk2;
		}

		bool IsControlMode2D() const
		{
			return Is2DMode();
		}

		bool ChangeTo2DMode(const csl::math::Vector3& in_rPosition, bool in_unk)
		{
			csl::math::Vector3 normalizedPos{};
			if (!math::Vector3NormalizeIfNotZero(in_rPosition, &normalizedPos))
				return Is2DMode();

			float unk{};
			if (auto* pPathComponent = GetPathService()->Search2DPath({ GetPosition() - normalizedPos * 0.1f }, { GetPosition() + in_rPosition }, &unk))
			{
				pPlayer->ChangeDimension(true, in_unk, pPathComponent, unk);
				return true;
			}

			return false;
		}

		bool ChangeTo3DMode(bool in_unk)
		{
			pPlayer->ChangeDimension(false, in_unk, nullptr, 0.0f);
		}

		void VisualLocaterStartInterpolation(float in_unk1, uint in_unk2)
		{
			ms_fpVisualLocaterStartInterporation(this, in_unk1, in_unk2);
		}

		CLevelInfo* GetLevelInfo() const
		{
			return pPlayer->GetLevelInfo();
		}

		fnd::SoundHandle PlaySE(const char* in_pName, bool in_unk);

		int GetRingNum() const
		{
			return GetBlackBoard()->GetRingParameter()->GetRingCount();
		}

		void SetMoveCylinderTimer(float in_timer);

		void StopSE(fnd::SoundHandle in_soundHandle)
		{
			in_soundHandle.Stop(0.0f);
		}
	};
}

#pragma pop_macro("SendMessage")
