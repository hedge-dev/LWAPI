#pragma once

namespace app
{
	class ObjEggBlock : public CSetObjectListener
	{
	protected:
		inline static const char* ms_pHitSoundName = "obj_yossyeggblock_hit";
		inline static csl::math::Vector3 ms_PositionOffset = { 0.0f, 5.0f, 0.0f };
		inline static const size_t ms_ShapeCount = 3;
		inline static const csl::math::Vector3 ms_CollisionSizes[] = { { 5.0f, 0.65f, 5.0f }, { 3.0f, 8.0f, 3.0f }, { 4.5f, 4.5f, 4.5f } };
		inline static const csl::math::Vector3 ms_CollisionOffsets[] = { { 0.0f, -0.65f, 0.0f }, { 0.0f, 13.0f, 0.0f }, { 0.0f, 4.5f, 0.0f } };
		inline static const size_t ms_EggRates[] = { 40, 20, 20, 20 };

	public:
		struct MotorSwing
		{
			float Unk1{};
			float ElapsedTime{};
			float Unk3{};
			float Unk4{};
			float Unk5{};
		};

		struct PopEggParam
		{
			csl::math::Vector3 Direction{};
			float Unk2{};
			float Unk3{};
			char Unk4{};
		};

		enum class EggBlockState : sint8
		{
			eEggBlockState_Idle,
			eEggBlockState_Damage
		};

		fnd::HFrame Frame{};
		MotorSwing IdleMotor{};
		MotorSwing DamageMotor{};
		csl::ut::Enum<EggBlockState, sint8> State{};
		PopEggParam PopEggParameter{};
		int PopEggNum{};
		float PopEggRandomAddSpeed{};
		game::PathEvaluator PathEvaluator{};
		
		ObjEggBlock() : CSetObjectListener()
		{

		}

	protected:
		void AddCallback(GameDocument& in_rDocument) override;

		bool ProcessMessage(fnd::Message& in_rMessage) override
		{
			if (PreProcessMessage(in_rMessage))
				return true;

			switch (in_rMessage.GetType())
			{
			case xgame::MsgDamage::MessageID:							return ProcMsgDamage(static_cast<xgame::MsgDamage&>(in_rMessage));
			default:													return CSetObjectListener::ProcessMessage(in_rMessage);
			}
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override;
		bool ProcMsgDamage(xgame::MsgDamage& in_rMessage);

		void DoCheckPopEgg()
		{
			if (PopEggNum <= 1 || PopEggParameter.Unk4 || DamageMotor.ElapsedTime <= DamageMotor.Unk3 * 0.25f)
				return;

			csl::math::Quaternion frameRot = Frame.m_Unk3.m_Mtx.GetRotation();
			csl::math::Vector3 framePos = Frame.m_Unk3.m_Mtx.GetTransVector();
			
			csl::math::Vector3 directionOffset{ math::Vector3Rotate(frameRot, PopEggParameter.Direction) };
			csl::math::Vector3 verticalOffset{ math::Vector3Rotate(frameRot, { 0.0f, 1.0f, 0.0f }) };

			csl::math::Vector3 popPos{ framePos + verticalOffset * 4.5f + directionOffset * 4.5f };

			if (auto* pTransform = GetComponent<fnd::GOCTransform>())
			{
				csl::math::Quaternion objectRot = pTransform->m_Frame.m_Unk3.GetRotationQuaternion();
				float random = floorf(SonicUSA::System::Random::GetInstance()->genrand_float32() * 100.0f);

				size_t limit{};
				size_t type{};
				for (size_t i = 0; i < 4; i++)
				{
					limit += ms_EggRates[i];
					if (random > limit)
					{
						type++;
						continue;
					}

					uint randomDistance = SonicUSA::System::Random::GetInstance()->genrand_float32() * 3.0f;
					if (random >= INT_MAX - 47)
						continue;

					egg::DroppedEggCInfo createInfo{};
					createInfo.Mtx = math::Matrix34AffineTransformation(popPos, objectRot);;
					createInfo.DropDirection = { directionOffset * (PopEggRandomAddSpeed / 3.0f * randomDistance + PopEggParameter.Unk3) };
					createInfo.PathEvaluator = PathEvaluator;
					createInfo.Type = type;
					createInfo.ZIndex = PopEggNum;

					egg::CreateDroppedEgg(*GetDocument(), createInfo);

					--PopEggNum;
					PopEggParameter.Unk4 = 1;
					SetExtUserData(eExtUserDataType_High, PopEggNum);

					if (auto* pSound = GetComponent<game::GOCSound>())
						pSound->Play3D(ms_pHitSoundName, 0.0f);

					return;
				}
			}
		}
	};
	
	inline void InitMotorParam(float in_unk1, float in_unk2, float in_unk3, ObjEggBlock::MotorSwing* out_pOutput)
	{
		if (!out_pOutput)
			return;

		out_pOutput->Unk1 = in_unk2;
		out_pOutput->ElapsedTime = 0.0f;
		out_pOutput->Unk3 = in_unk1;
		out_pOutput->Unk4 = MATHF_PI * 2 / in_unk1;
		out_pOutput->Unk5 = in_unk3 * MATHF_PI / 180.0f;
	}

	inline void InitPopEggParam(const csl::math::Vector3& in_rDirection, float in_unk2, float in_unk3, ObjEggBlock::PopEggParam* out_pOutput)
	{
		if (!out_pOutput)
			return;

		out_pOutput->Direction = in_rDirection;
		out_pOutput->Unk2 = in_unk2;
		out_pOutput->Unk3 = in_unk3;
		out_pOutput->Unk4 = 0;
	}

	inline void ObjEggBlock::AddCallback(app::GameDocument& in_rDocument)
	{
		auto* eggManager = in_rDocument.GetService<EggManager>();
		
		fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
		fnd::GOComponent::Create<game::GOCCollider>(*this);
		fnd::GOComponent::Create<game::GOCSound>(*this);

		auto* pParam = GetAdapter()->GetData<SEggBlockParam>();

		PopEggNum = GetExtUserData(eExtUserDataType_High);
		if (!PopEggNum)
			PopEggNum = pParam->PopEggNum + 1;

		PopEggRandomAddSpeed = pParam->PopEggRandomAddSpeed;

		fnd::GOComponent::BeginSetup(*this);

		if (auto* pTransform = GetComponent<fnd::GOCTransform>())
			pTransform->m_Frame.AddChild(&Frame);

		auto* pInfo = ObjUtil::GetObjectInfo<ObjEggBlockInfo>(in_rDocument);

		if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
		{
			fnd::GOCVisualModel::Description description{};
			description.m_Model = pInfo->Model;
			description.m_pParent = &Frame;

			pVisualModel->Setup(description);
			pVisualModel->SetLocalTranslation(ms_PositionOffset);
		}

		if (auto* pCollider = GetComponent<game::GOCCollider>())
		{
			pCollider->Setup({ ms_ShapeCount });

			for (size_t i = 0; i < pCollider->m_Shapes.capacity(); i++)
			{
				game::ColliBoxShapeCInfo collisionInfo{};
				collisionInfo.m_ShapeType = game::CollisionShapeType::ShapeType::ShapeType_Box;
				collisionInfo.m_MotionType = game::PhysicsMotionType::MotionType::MotionType_VALUE2;
				collisionInfo.m_ShapeID = i;

				collisionInfo.m_Unk2 |= 1;
				if (collisionInfo.m_ShapeID == 2)
				{
					collisionInfo.m_Flags = 4;
					collisionInfo.m_Unk2 &= ~1;
					collisionInfo.m_Unk2 |= 0x100;
					collisionInfo.m_Unk3 = 0x4003;
				}

				collisionInfo.m_Size = ms_CollisionSizes[i];
				collisionInfo.SetLocalPosition({ ms_CollisionOffsets[i] });

				if (collisionInfo.m_ShapeID != 2)
					ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Default, collisionInfo);

				pCollider->CreateShape(collisionInfo);
			}
		}

		game::GOCSound::SimpleSetup(this, 0, 0);

		InitMotorParam(1.8f, 0.0f, 8.0f, &IdleMotor);

		if (auto* pTransform = GetComponent<fnd::GOCTransform>())
		{
			csl::math::Matrix34 trsMatrix = pTransform->m_Transform.GetTransformMatrix();
			csl::math::Vector3 yAxis = { trsMatrix.GetColumn(1) };
			
			game::PathRaycastInput rayInput{};
			game::PathRaycastOutput rayOutput{};
			rayInput.From = trsMatrix.GetTransVector();
			rayInput.To = { rayInput.From - (yAxis * -400.0f) };
			rayInput.Unk1 = 1;
			rayInput.Unk2 = 1;

			if (auto* pPathManager = in_rDocument.GetService<game::PathManager>())
			{
				if (pPathManager->CastRay(rayInput, &rayOutput))
				{
					PathEvaluator.SetPathObject(rayOutput.pComponent);
					PathEvaluator.SetDistance(rayOutput.Distance);
				}
			}
		}

		fnd::GOComponent::EndSetup(*this);
	}

	inline void ObjEggBlock::Update(const fnd::SUpdateInfo& in_rUpdateInfo)
	{
		float angle = IdleMotor.Unk5 * sinf(IdleMotor.Unk4 * (IdleMotor.ElapsedTime + IdleMotor.Unk1));

		switch ((EggBlockState)State)
		{
		case EggBlockState::eEggBlockState_Idle:
		{
			IdleMotor.ElapsedTime += in_rUpdateInfo.deltaTime;

			csl::math::Quaternion rotation{ Eigen::AngleAxisf(angle, csl::math::Vector3::UnitZ()) };
			Frame.SetLocalRotation(rotation);
			if (auto* pCollider = GetComponent<game::GOCCollider>())
				if (auto* pShape = pCollider->GetShapeById(2))
					pShape->SetLocalRotation(rotation);

			break;
		}
		case EggBlockState::eEggBlockState_Damage:
		{
			float scalar = sinf(DamageMotor.Unk4 * (DamageMotor.ElapsedTime + DamageMotor.Unk1));
			csl::math::Vector3 position{ PopEggParameter.Direction * PopEggParameter.Unk2 * csl::math::Clamp(fabs(scalar), 0.0f, 1.0f) };
			Frame.SetLocalTranslation(position);

			DoCheckPopEgg();

			if (DamageMotor.ElapsedTime > DamageMotor.Unk3 * 0.5f)
			{
				State = EggBlockState::eEggBlockState_Idle;
				InitMotorParam(1.8f, 0.0f, 8.0f, &IdleMotor);
			}

			DamageMotor.ElapsedTime += in_rUpdateInfo.deltaTime;

			angle = csl::math::Lerp(angle, DamageMotor.Unk5 * scalar, csl::math::Clamp(DamageMotor.ElapsedTime / ((DamageMotor.Unk3 * 0.5f) * 0.1f), 0.0f, 1.0f));
			
			csl::math::Quaternion rotation{ Eigen::AngleAxisf(angle, csl::math::Vector3::UnitZ()) };
			Frame.SetLocalRotation(rotation);
			if (auto* pCollider = GetComponent<game::GOCCollider>())
				if (auto* pShape = pCollider->GetShapeById(2))
					pShape->SetLocalRotation(rotation);

			break;
		}
		default:
		{
			csl::math::Quaternion rotation{ Eigen::AngleAxisf(angle, csl::math::Vector3::UnitZ()) };
			Frame.SetLocalRotation(rotation);
			if (auto* pCollider = GetComponent<game::GOCCollider>())
				if (auto* pShape = pCollider->GetShapeById(2))
					pShape->SetLocalRotation(rotation);

			break;
		}
		}
	}

	inline bool ObjEggBlock::ProcMsgDamage(xgame::MsgDamage& in_rMessage)
	{
		if (State == EggBlockState::eEggBlockState_Damage)
			return true;
	
		auto* pShape = in_rMessage.m_SenderShape.Get();
		if (!pShape)
			return true;

		auto* pTransform = GetComponent<fnd::GOCTransform>();
		if (!pTransform)
			return true;

		auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), 0);
		if (!pPlayerInfo)
			return true;

		csl::math::Matrix34 objectMtx = pTransform->m_Frame.m_Unk3.m_Mtx;
		csl::math::Matrix34Inverse(objectMtx, &objectMtx);

		csl::math::Vector3 localPosition{ objectMtx * csl::math::Vector4(pPlayerInfo->Unk15, 1.0f) };
		csl::math::Vector3 playerNormal{ objectMtx * csl::math::Vector4(pPlayerInfo->Velocity, 1.0f) };

		if (!math::Vector3NormalizeIfNotZero(playerNormal, &playerNormal))
			return true;

		if (pShape->GetID() == 1 && localPosition.y() > 4.5f * 2.0f &&
			playerNormal.dot(csl::math::Vector3(0.0f, -1.0f, 0.0f)) >= 0.0f &&
			AttackType::IsDamaged(in_rMessage.AttackType, 10))
		{
			InitMotorParam(0.8f, 0.0f, 0.0f, &DamageMotor);
			InitPopEggParam({ 0.0f, -1.0f, 0.0f }, 5.0f, 50.0f, &PopEggParameter);

			if (auto* pSound = GetComponent<game::GOCSound>())
				pSound->Play(ms_pHitSoundName, 0.0f);

			in_rMessage.SetReply(pTransform->m_Frame.m_Unk3.GetTranslation(), false);

			State = EggBlockState::eEggBlockState_Damage;
		}
		else if (localPosition.y() < 0.0f &&
			playerNormal.dot(csl::math::Vector3(0.0f, 1.0f, 0.0f)) >= 0.0f &&
			(AttackType::And(in_rMessage.AttackType, 32) || AttackType::And(in_rMessage.AttackType, 64)))
		{
			if (!math::Vector3NormalizeIfNotZero(localPosition, &localPosition))
				return true;

			if (csl::math::Vector3(0.0f, -1.0f, 0.0f).dot(localPosition) >= MATHF_PI / 2.25)
				return true;

			csl::math::Vector3 normal = { csl::math::Vector3(0.0f, 1.0f, 0.0f).cross(localPosition) };
			if (!math::Vector3NormalizeIfNotZero(normal, &normal))
				return true;

			float dot = -csl::math::Vector3(0.0f, 0.0f, 1.0f).dot(normal);
			dot = csl::math::Clamp(dot, 0.5f, 0.0f);

			InitMotorParam(1.0f, dot, 30.0f, &DamageMotor);
			InitPopEggParam({ 0.0f, 1.0f, 0.0f }, 10.0f, 40.0f, &PopEggParameter);

			if (auto* pSound = GetComponent<game::GOCSound>())
				pSound->Play(ms_pHitSoundName, 0.0f);

			in_rMessage.SetReply(pTransform->m_Frame.m_Unk3.GetTranslation(), false);

			State = EggBlockState::eEggBlockState_Damage;
		}
		
		return true;
	}
}
