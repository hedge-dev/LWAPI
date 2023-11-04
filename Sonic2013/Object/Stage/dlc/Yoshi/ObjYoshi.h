#pragma once
#pragma push_macro("min")
#undef min

namespace app
{
	namespace detail_yoshi
	{
		class Random
		{
		public:
			typedef size_t result_type;

			result_type operator()()
			{
				return (result_type)(floorf(SonicUSA::System::Random::GetInstance()->genrand_float32()) * 4);
			}

			static constexpr result_type min()
			{
				return 0;
			}

			static constexpr result_type max()
			{
				return INT_MAX;
			}
		};
	}

	// Red and Blue Yoshi are swapped when their models are being initialized compared to eggs, thus this is needed.
	static size_t YoshiTypes[] = { 0, 2, 1, 3 };

	class ObjYoshi : public GameObject3D, public TTinyFsm<ObjYoshi>
	{
	private:
		inline static csl::math::Vector3 ms_PositionOffset = { 0.0f, -3.5f, 0.0f };
		inline static csl::math::Vector3 ms_Scale = { 0.55f, 0.55f, 0.55f };
		inline static size_t ms_AnimationLinkCount = 12;
		inline static size_t ms_UvAnimationCount = 2;
		inline static const char* ms_pSoundName = "enm_yossy_voice";
		inline static const char* ms_UvAnimationNames[] = {
			"RESULT1_START", "RESULT1_LOOP",
			"RESULT2_START", "RESULT2_LOOP",
			"RESULT3_START", "RESULT3_LOOP",
			"RESULT4_START", "RESULT4_LOOP",
			"RESULT5_START", "RESULT5_LOOP",
			"RESULT6_START", "RESULT6_LOOP"
		};

		inline static const char* ms_AnimationNames[] = { "RESULT1", "RESULT2", "RESULT3", "RESULT4", "RESULT5", "RESULT6" };

	public:
		class CInfo
		{
		public:
			size_t Type{};
			csl::math::Vector3 Position{};
			csl::math::Quaternion Rotation{};
			size_t Index{};
		};

		class BoundListener : public game::MoveBound::Listener
		{
		public:
			ObjYoshi* pOwner{};

			void OnBound(const csl::math::Plane& in_rPlane) override
			{
				if (pOwner)
					pOwner->BoundCallback();
			}
		};

	private:
		size_t Type{};
		csl::math::Vector3 Position{};
		csl::math::Quaternion Rotation{};
		size_t Index{};
		BoundListener Listener{};
		EnemyUvAnimLinkController UvAnimController{};
		float Time{};
		float RotationAngle{};
		bool IsMovementDisabled{};
		bool IsAnimationStopped{};

	public:
		ObjYoshi(const CInfo& in_rInfo) : GameObject3D(), TTinyFsm<ObjYoshi>(&ObjYoshi::StateRelease)
		{
			Type = in_rInfo.Type;
			Position = in_rInfo.Position;
			Rotation = in_rInfo.Rotation;
			Index = in_rInfo.Index;
		}

		void AddCallback(GameDocument* in_pDocument) override
		{	
			fnd::GOComponent::Create<game::GOCGravity>(*this);
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCAnimationScript>(*this);
			fnd::GOComponent::Create<game::GOCEffect>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			fnd::GOComponent::Create<game::GOCMovementComplex>(*this);

			fnd::GOComponent::BeginSetup(*this);

			if ((Index % 2) == 0)
			{
				Rotation *= csl::math::Quaternion(Eigen::AngleAxisf(MATHF_PI, csl::math::Vector3::UnitY()));
				Rotation = Rotation.Normalize();
			}

			if (auto* pTransform = GetComponent<fnd::GOCTransform>())
			{
				pTransform->SetLocalTranslation(Position);
				pTransform->SetLocalRotation(Rotation);
			}

			auto* pInfo = ObjUtil::GetObjectInfo<ObjYoshiInfo>(*in_pDocument);

			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.Model = pInfo->ModelContainer.Models[Type];
				description.Skeleton = pInfo->Skeleton;
				description.Unk2 |= 0x400000u;

				pVisualModel->Setup(description);

				pVisualModel->SetLocalTranslation(ms_PositionOffset);
				pVisualModel->SetLocalScale(ms_Scale);

				if (auto* pAnimationScript = GetComponent<game::GOCAnimationScript>())
				{
					pAnimationScript->Setup({ &pInfo->AnimationContainer });
					pVisualModel->AttachAnimation(pAnimationScript);
					
					pAnimationScript->SetAnimation("JUMP");
				}
			}

			EnemyUvAnimLinkController::Description uvAnimDescription{};
			uvAnimDescription.AnimationLinkCount = ms_AnimationLinkCount;
			uvAnimDescription.UvAnimationCount = ms_UvAnimationCount;
			uvAnimDescription.Owner = this;

			UvAnimController.Setup(uvAnimDescription, GetAllocator());
			for (size_t i = 0; i < ms_AnimationLinkCount; i++)
			{
				for (size_t j = 0; j < ms_UvAnimationCount; j++)
				{
					auto uvAnimation = pInfo->TexSrtAnimContainer.Animations[2 * i + j];

					if (uvAnimation.IsValid())
					{
						UvAnimController.Add(uvAnimation, ms_UvAnimationNames[i], 0);
					}
				}
			}
			
			game::GOCGravity::SimpleSetup(this, 1);

			if (auto* pEffect = GetComponent<game::GOCEffect>())
				game::GOCEffect::SimpleSetup(this, 0, 0);

			game::GOCSound::SimpleSetup(this, 0, 0);

			if (auto* pMovement = GetComponent<game::GOCMovementComplex>())
			{
				if (auto* pMoveBound = pMovement->SetMoveController<game::MoveBound>())
				{
					float random = SonicUSA::System::Random::GetInstance()->genrand_float32() * 0.6f - 0.3f;

					auto rotVec = math::Vector3RotateX(-((-(int)Index + 87.5f + random - 0.7f) * (MATHF_PI / 180.0f)),
						{ csl::math::Vector3::UnitZ() });

					csl::math::Vector3 leftVec = { csl::math::Vector3::UnitX() };
					if ((Index & 2) == 0)
						leftVec = { -csl::math::Vector3::UnitX() };

					if ((Index % 2) == 0 && (Index & 1))
					{
						rotVec = math::Vector3RotateX(-((-(int)Index + 87.5f + random) * (MATHF_PI / 180.0f)),
							{ csl::math::Vector3::UnitZ() });

						leftVec = { -csl::math::Vector3::UnitX() };
					}
					
					ObjUtil::GetSVPath(*GetDocument(), Position, { math::Vector3Rotate(Rotation, { -csl::math::Vector3::UnitY() }) });

					game::MoveBound::Desc description{};
					description.Velocity = { math::Vector3Rotate(Rotation, rotVec) * 130.0f + math::Vector3Rotate(Rotation, leftVec) * 0.3f * 10.0f };
					description.Unk3 = 200.0f;
					description.Unk4 = 1.2f;
					description.Unk5 = 0.0f;
					description.Flags.set(0);
				
					pMoveBound->Setup(description);
					Listener.pOwner = this;
					pMoveBound->ResetListener(&Listener);

					auto* pContextParam = pMovement->GetContextParam();
					pContextParam->Velocity = description.Velocity;
				}
			}

			fnd::GOComponent::EndSetup(*this);

			if (auto* pSound = GetComponent<game::GOCSound>())
				pSound->Play(ms_pSoundName, 0.0f);
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			default:
				return GameObject3D::ProcessMessage(in_rMessage);
			}
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			DispatchFSM(TiFsmBasicEvent<ObjYoshi>::CreateUpdate(in_rUpdateInfo.DeltaTime));
		}

		void BoundCallback()
		{
			IsMovementDisabled = true;
			if (auto* pMovement = GetComponent<game::GOCMovementComplex>())
				pMovement->DisableMovementFlag(0);

			if (!IsAnimationStopped)
			{
				IsAnimationStopped = true;
				if (auto* pAnimation = GetComponent<game::GOCAnimationScript>())
					pAnimation->ExitLoopSeqInsideAnimation();
			}
		}

		void UpdateModelPosture(float in_deltaTime)
		{
			if (!IsAnimationStopped)
				return;
		
			RotationAngle += in_deltaTime * (MATHF_PI * 2.0f);
			RotationAngle = csl::math::Min(RotationAngle, MATHF_PI / 2.0f);

			if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
			{
				csl::math::Quaternion rotation { Eigen::AngleAxisf(-1.0f * RotationAngle, csl::math::Vector3::UnitY()) };

				if ((Index & 1) == 0)
					rotation = { Eigen::AngleAxisf(RotationAngle, csl::math::Vector3::UnitY()) };

				pVisualModel->SetLocalRotation(rotation);
			}
		}

		void PopupOneup()
		{
			auto* pTransform = GetComponent<fnd::GOCTransform>();
			if (!pTransform)
				return;

			ObjYoshiOneUp::CInfo createInfo{};
			createInfo.PlayerNo = 0;
			createInfo.Position = pTransform->Frame.Unk3.GetTranslation();
			createInfo.Rotation = pTransform->Frame.Unk3.GetRotationQuaternion();

			ObjYoshiOneUp::Create(*GetDocument(), createInfo);
		}

		void ChangeState(TiFsmState_t in_state)
		{
			FSM_TRAN(in_state);
		}

		TiFsmState_t StateRelease(const TiFsmBasicEvent<ObjYoshi>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_UPDATE:
			{
				UpdateModelPosture(in_rEvent.getFloat());
				if (IsMovementDisabled)
				{
					ChangeState(&ObjYoshi::StatePose);
					return {};
				}

				if (IsAnimationStopped)
					return{};

				auto* pTransform = GetComponent<fnd::GOCTransform>();
				if (!pTransform)
					return {};

				csl::math::Vector3 upVec{ pTransform->Frame.Unk3.Mtx.GetColumn(1) };

				auto* pMovement = GetComponent<game::GOCMovementComplex>();
				if (!pMovement)
					return {};

				if (pMovement->GetContextParam()->Velocity.dot(upVec) <= 0.0f)
					return {};

				csl::math::Vector3 from{ pTransform->Frame.Unk3.Mtx.GetTransVector() };
				csl::math::Vector3 to{ from + upVec * 10.0f };

				if (ObjUtil::RaycastHitCollision(*GetDocument(), from, to, 0xC996))
				{
					IsAnimationStopped = true;
					if (auto* pAnimation = GetComponent<game::GOCAnimationScript>())
						pAnimation->ExitLoopSeqInsideAnimation();
				}

				return {};
			}
			case TiFSM_SIGNAL_LEAVE:
				return {};
			default:
				return FSM_TOP();
			}
		}

		TiFsmState_t StatePose(const TiFsmBasicEvent<ObjYoshi>& in_rEvent)
		{
			switch (in_rEvent.getSignal())
			{
			case TiFSM_SIGNAL_UPDATE:
			{
				UpdateModelPosture(in_rEvent.getFloat());

				int previousTime = (int)Time;
				Time += in_rEvent.getFloat();
				if (previousTime >= (int)Time)
					return{};
			
				if ((int)Time < 3)
				{
					PopupOneup();
				}

				return{};
			}
			case TiFSM_SIGNAL_ENTER:
			{
				auto* pInfo = ObjUtil::GetObjectInfo<ObjYoshiInfo>(*GetDocument());
				if (!Index)
				{
					detail_yoshi::Random rand{};

					std::shuffle(pInfo->AnimationIndices.begin(), pInfo->AnimationIndices.end(), rand);
				}

				if (auto* pAnimation = GetComponent<game::GOCAnimationScript>())
					pAnimation->ChangeAnimation(ms_AnimationNames[pInfo->AnimationIndices[Index % ms_AnimationLinkCount]]);

				Time = 0.0f;

				PopupOneup();

				return {};
			}
			case TiFSM_SIGNAL_LEAVE:
				return {};
			default:
				return FSM_TOP();
			}
		}

		static ObjYoshi* Create(GameDocument& in_rDocument, const CInfo& in_rInfo)
		{
			auto* pObject = new ObjYoshi(in_rInfo);
			if (!pObject)
				return { nullptr };

			in_rDocument.AddGameObject(pObject);
			return pObject;
		}
	};
}

#pragma pop_macro("min")