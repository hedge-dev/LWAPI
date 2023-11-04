#pragma once

namespace app
{
	// The following object will crash the game eventually if enough of them are spawned,
	// as the ObjectPartPointLight object never gets cleaned up as part of this object's code.
	// To fix this, send the message app::xgame::MsgKill to all valid instances found in the 
	// PointLights array by overriding this object's RemoveCallback.
	class ObjLoftBird : public CSetObjectListener
	{
		class Listener : public animation::AnimationListener
		{
		public:
			ObjLoftBird* pOwner{};

			void OnEvent(animation::NotifyTiming timing) override
			{
				if (!pOwner)
					return;

				pOwner->UpdateNodeTransform();
			}
		};

	private:
		inline static const size_t ms_ModelCount = 2;
		inline static const size_t ms_AnimationCount = 2;
		inline static size_t ms_AnimationLinkCount = 2;
		inline static size_t ms_UvAnimationCount = 2;
		inline static constexpr size_t ms_PointLightCount = 2;
		inline static const char* ms_pLinkDefaultAnimationName = "IDLE_LOOP";
		inline static const char* ms_pLoftBirdDefaultAnimationName = "FLY_LOOP";
		inline static const char* ms_pUvLinkAnimationNames[] = { "EVENT_ONE", "EVENT_TWO" };
		inline static const char* ms_pFlySoundName = "obj_loftbird_fly";
		inline static const char* ms_pCrySoundName = "obj_loftbird_cry";
		inline static const char* ms_pFlapSoundName = "obj_loftbird_flap";
		inline static const csl::math::Vector3 ms_ModelScale = { 2.0f, 2.0f, 2.0f };
		inline static const csl::math::Vector3 ms_PointLightOffsets[] = { { 10.0f, 10.0f, 35.0f }, { -5.0f, 0.0f, 30.0f }, { -15.0f, 6.0f, 15.0f }, { -15.0f, 15.0f, 0.0f } };
		inline static const float ms_PointLightRedColors[] = { 1.0f, 0.5f, 1.0f, 0.4f };
		inline static const float ms_PointLightGreenColors[] = { 1.0f, 0.5f, 0.7f, 0.3f };
		inline static const float ms_PointLightBlueColors[] = { 1.0f, 0.5f, 0.3f, 0.3f };
		inline static const float ms_PointLightUnkValues[] = { 35.0f, 35.0f, 30.0f, 30.0f };
		inline static const bool ms_PointLightIsValid[] = { true, true };
		inline static const float ms_CollisionRadius = 20.0f;

	public:
		game::PathEvaluator Path{};
		float EndDistance{};
		float MovementSpeed{};
		Listener Listener{};
		fnd::SoundHandle SoundHandle{};
		bool IsAwake{};
		EnemyUvAnimLinkController UvAnimController{};
		int PointLightType{};
		csl::ut::InplaceObjectMoveArray<GameObjectHandle<ObjectPartPointLight>, ms_PointLightCount> PointLights{ ms_PointLightCount };

	public:
		ObjLoftBird() : CSetObjectListener()
		{
			Listener.Timing = 2;
		}

	protected:
		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualContainer>(*this);
			fnd::GOComponent::Create<game::GOCAnimationContainer>(*this);
			fnd::GOComponent::Create<game::GOCSphereCollider>(*this);
			fnd::GOComponent::Create<game::GOCSound>(*this);
			
			fnd::GOComponent::BeginSetup(*this);

			auto* pParam = GetAdapter()->GetData<SLoftBirdParam>();
			EndDistance = pParam->EndDist;
			MovementSpeed = pParam->MoveSpeed;
			if (pParam->PointLight >= 0 && pParam->PointLight <= 1)
				PointLightType = pParam->PointLight;
		
			auto* pInfo = ObjUtil::GetObjectInfo<ObjLoftBirdInfo>(*in_pDocument);

			if (auto* pVisualContainerGoc = GetComponent<fnd::GOCVisualContainer>())
			{
				pVisualContainerGoc->Setup({ ms_ModelCount });

				for (size_t i = 0; i < ms_ModelCount; i++)
				{
					auto* pVisualGoc = fnd::GOComponent::CreateSingle<fnd::GOCVisualModel>(*this);

					fnd::GOCVisualModel::Description description{};
					description.Model = pInfo->ModelContainer.Models[i];
					description.Skeleton = pInfo->SkeletonContainer.Skeletons[i];

					pVisualGoc->Setup(description);
					pVisualContainerGoc->Add(pVisualGoc);
					pVisualGoc->SetVisible(false);
					pVisualGoc->SetLocalScale(ms_ModelScale);
				}

				if (auto* pAnimationContainerGoc = GetComponent<game::GOCAnimationContainer>())
				{
					pAnimationContainerGoc->Setup({ ms_AnimationCount });

					if (auto* pAnimationScriptGoc = fnd::GOComponent::CreateSingle<game::GOCAnimationScript>(*this))
					{
						pAnimationScriptGoc->Setup({ &pInfo->LinkAnimationContainer });
						pAnimationContainerGoc->Add(pAnimationScriptGoc);
						static_cast<fnd::GOCVisualModel*>(pVisualContainerGoc->Visuals[0])->AttachAnimation(pAnimationScriptGoc);
						pAnimationScriptGoc->SetAnimation(ms_pLinkDefaultAnimationName);

						pAnimationScriptGoc->RegisterCallback(-1, animation::CreateAnimCallback<ObjLoftBird>(this, &app::ObjLoftBird::AnimationChangeCallback, GetAllocator()));
					}

					if (auto* pAnimationScriptGoc = fnd::GOComponent::CreateSingle<game::GOCAnimationScript>(*this))
					{
						pAnimationScriptGoc->Setup({ &pInfo->LoftBirdAnimationContainer });
						pAnimationContainerGoc->Add(pAnimationScriptGoc);
						static_cast<fnd::GOCVisualModel*>(pVisualContainerGoc->Visuals[1])->AttachAnimation(pAnimationScriptGoc);
						pAnimationScriptGoc->SetAnimation(ms_pLoftBirdDefaultAnimationName);

						pAnimationScriptGoc->RegisterCallback(0, animation::CreateAnimCallback<ObjLoftBird>(this, &app::ObjLoftBird::SoundCallback, GetAllocator()));

						Listener.pOwner = this;
						pAnimationScriptGoc->AddListener(&Listener);
					}
				}

				EnemyUvAnimLinkController::Description uvAnimDescription{};
				uvAnimDescription.AnimationLinkCount = ms_AnimationLinkCount;
				uvAnimDescription.UvAnimationCount = ms_UvAnimationCount;
				uvAnimDescription.Owner = this;
				uvAnimDescription.Unk4.set(0);

				UvAnimController.Setup(uvAnimDescription, GetAllocator());
				for (size_t i = 0; i < ms_AnimationLinkCount; i++)
				{
					for (size_t j = 0; j < ms_UvAnimationCount; j++)
					{
						auto uvAnimation = pInfo->TexSrtAnimContainer.Animations[2 * i + j];
						UvAnimController.Add(uvAnimation, ms_pUvLinkAnimationNames[i], 0);
					}
				}
			}

			if (auto* pCollider = GetComponent<game::GOCSphereCollider>())
			{
				game::GOCSphereColliderCinfo collisionInfo{};
				collisionInfo.Radius = ms_CollisionRadius;
				collisionInfo.Unk9 = 1;
				ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk2, collisionInfo);

				pCollider->Setup(collisionInfo);
			}

			game::GOCSound::SimpleSetup(this, 1, 1);

			if (auto* pPathManager = GetService<game::PathManager>())
			{
				if (auto* pPathObject = pPathManager->GetPathObject(pParam->ObjPathId))
				{
					Path.SetPathObject(pPathObject);
					if (Path.Component.IsValid())
					{
						Path.SetDistance(pParam->StartDist);

						csl::math::Vector3 point{}, normal{}, tangent{};
						Path.GetPNT(Path.Distance, &point, &normal, &tangent);

						csl::math::Matrix34 rotationMatrix{};
						rotationMatrix.SetColumn(0, { normal.cross(tangent) });
						rotationMatrix.SetColumn(1, normal);
						rotationMatrix.SetColumn(2, tangent);
						rotationMatrix.SetColumn(3, { 0.0f, 0.0f, 0.0f });
						GetComponent<fnd::GOCTransform>()->SetLocalRotation({ rotationMatrix });
					}
				}
			}

			CreatePointLight();

			fnd::GOComponent::EndSetup(*this);
			
			Sleep();
		}

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgNotifyObjectEvent::MessageID:				return ProcMsgNotifyObjectEvent(static_cast<xgame::MsgNotifyObjectEvent&>(in_rMessage));
			case xgame::MsgDlcZeldaNoticeStopEnemy::MessageID:			return ProcMsgDlcZeldaNoticeStopEnemy(static_cast<xgame::MsgDlcZeldaNoticeStopEnemy&>(in_rMessage));
			case xgame::MsgLoftBirdCollision::MessageID:				return ProcMsgLoftBirdCollision(static_cast<xgame::MsgLoftBirdCollision&>(in_rMessage));
			default:													return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		bool ProcMsgNotifyObjectEvent(xgame::MsgNotifyObjectEvent& in_rMessage)
		{
			if (in_rMessage.GetEventType() != 1 || IsAwake)
				return true;

			auto* pVisualContainer = GetComponent<fnd::GOCVisualContainer>();
			for (size_t i = 0; i < pVisualContainer->Visuals.size(); i++)
				pVisualContainer->Visuals[i]->SetVisible(true);

			game::SoundFollowFrameInfo followInfo{};
			followInfo.TransType = 1;
			followInfo.pCueName = ms_pFlySoundName;
			SoundHandle = GetComponent<game::GOCSound>()->Play3D(followInfo);

			IsAwake = true;

			Resume();

			return true;
		}

		bool ProcMsgDlcZeldaNoticeStopEnemy(xgame::MsgDlcZeldaNoticeStopEnemy& in_rMessage)
		{
			if (IsAwake)
			{
				SoundHandle.StopImm();
				Kill();
				SetStatusRetire();
			}

			return true;
		}

		bool ProcMsgLoftBirdCollision(xgame::MsgLoftBirdCollision& in_rMessage)
		{
			auto* pAnimationContainer = GetComponent<game::GOCAnimationContainer>();

			switch (in_rMessage.ActionType)
			{
			case 0:
				static_cast<game::GOCAnimationScript*>(pAnimationContainer->Get(1))->ChangeAnimation("FLAP_WING");
				break;
			case 1:
				GetComponent<game::GOCSound>()->Play(ms_pCrySoundName, 0.0f);
				break;
			case 2:
				static_cast<game::GOCAnimationScript*>(pAnimationContainer->Get(0))->ChangeAnimation("EVENT_ONE");
				break;
			case 3:
				static_cast<game::GOCAnimationScript*>(pAnimationContainer->Get(0))->ChangeAnimation("EVENT_TWO");
				break;
			default:
				break;
			}

			return true;
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			if (!IsAwake)
				return;

			float length = Path.GetLength();
			float position = MovementSpeed * in_rUpdateInfo.DeltaTime + Path.Distance;
			if (position >= length || position >= EndDistance)
			{
				SoundHandle.StopImm();
				SetStatusRetire();
				Kill();

				return;
			}

			Path.SetDistance(csl::math::Clamp(position, 0.0f, length));

			csl::math::Vector3 point{}, normal{}, tangent{};
			Path.GetPNT(Path.Distance, &point, &normal, &tangent);

			csl::math::Matrix34 rotationMatrix{};
			rotationMatrix.SetColumn(0, { normal.cross(tangent) });
			rotationMatrix.SetColumn(1, normal);
			rotationMatrix.SetColumn(2, tangent);
			rotationMatrix.SetColumn(3, { 0.0f, 0.0f, 0.0f });

			auto* pTransform = GetComponent<fnd::GOCTransform>();

			pTransform->SetLocalTranslation(point);
			pTransform->SetLocalRotation({ pTransform->GetLocalRotation().slerp(10.0f * in_rUpdateInfo.DeltaTime, csl::math::Quaternion(rotationMatrix)) });
		}

		void AnimationChangeCallback(animation::CharactorAnimation* in_pAnimation, animation::ETriggerValueType in_triggerType, animation::CallbackParam in_param)
		{
			UvAnimController.ChangeCallback(in_pAnimation, in_triggerType, in_param);
		}

		void SoundCallback(animation::CharactorAnimation* in_pAnimation, animation::ETriggerValueType in_triggerType, animation::CallbackParam in_param)
		{
			if (in_triggerType == 1)
				GetComponent<game::GOCSound>()->Play3D(ms_pFlapSoundName, 0.0f);
		}

		void UpdateNodeTransform()
		{
			auto* pVisualContainer = GetComponent<fnd::GOCVisualContainer>();
			auto* pLoftBirdVisualGoc = pVisualContainer->Visuals[1];
			if (!pLoftBirdVisualGoc)
				return;

			math::Transform transform{};
			if (!static_cast<fnd::GOCVisualModel*>(pLoftBirdVisualGoc)->GetNodeTransform(1, "Const_link", &transform))
				return;

			auto* pLinkVisualGoc = pVisualContainer->Visuals[0];
			if (pLinkVisualGoc)
				static_cast<fnd::GOCVisualModel*>(pLinkVisualGoc)->SetNodeTransform(1, "Reference", transform);

			for (size_t i = 0; i < 2; i++)
			{
				if (!PointLights[i].IsValid())
					continue;

				auto* pPointLight = PointLights[i].Get();
				if (!pPointLight)
					continue;

				auto* pLightTransform = pPointLight->GetComponent<fnd::GOCTransform>();
				if (!pLightTransform)
					continue;

				pLightTransform->SetLocalTranslation({ transform.Position + math::Vector3Rotate(transform.Rotation, ms_PointLightOffsets[2 * PointLightType + i]) });
			}
		}

		void CreatePointLight()
		{
			auto* pVisualContainerGoc = GetComponent<fnd::GOCVisualContainer>();
			auto* pLoftBirdVisualGoc = pVisualContainerGoc->Visuals[1];
			if (!pLoftBirdVisualGoc)
				return;

			math::Transform transform{};
			if (!static_cast<fnd::GOCVisualModel*>(pLoftBirdVisualGoc)->GetNodeTransform(1, "Const_link", &transform))
				return;

			auto* pLinkVisualGoc = pVisualContainerGoc->Visuals[0];
			if (!pLinkVisualGoc)
				return;

			for (size_t i = 0; i < 2; i++)
			{
				if (!PointLights[i].IsValid())
				{
					ObjectPartPointLight::CInfo createInfo{};
					createInfo.Position = { transform.Position + math::Vector3Rotate(transform.Rotation, ms_PointLightOffsets[2 * PointLightType + i]) };
					createInfo.Unk1 = ms_PointLightUnkValues[2 * PointLightType + i];
					createInfo.LifeTime = -1.0f;
					createInfo.pParentTransform = GetComponent<fnd::GOCTransform>();
					createInfo.R = ms_PointLightRedColors[2 * PointLightType + i];
					createInfo.G = ms_PointLightGreenColors[2 * PointLightType + i];
					createInfo.B = ms_PointLightBlueColors[2 * PointLightType + i];

					PointLights[i] = ObjectPartPointLight::Create(*GetDocument(), createInfo);
				}

				if (!ms_PointLightIsValid[PointLightType])
					break;
			}
		}
	};
}