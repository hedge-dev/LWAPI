#pragma once

namespace app
{
    static bool IsEnemyBlowOffRotationAngleSet = false;
    static float EnemyBlowOffRotationAngle = 0.0f;

    class EnemyBlowOffObject : public GameObject3D
    {
    private:
        inline static size_t ms_AnimationCount = 1;
        inline static size_t ms_ShapeCount = 2;
        inline static const char* ms_pAnimationName = "BLOW";

    protected:
        const EnemyBlowOffObjectCInfo* pCreateInfo{};
        MoveEnemyBlowOffObject* pMoveBlowOff{};
        fnd::HFrame Frame{};
        csl::math::Vector3 PositionOffset{};
        csl::math::Vector3 Unk3{};
        csl::math::Vector3 Unk4{};
        size_t PlayerNo{};
        GameObjectHandle<GameObject> Owner{};
        GameObjectHandle<GameObject> Target{};
        int FrameLifeSpan{ -1 };
        csl::ut::Enum<EnemyBlowOffObjectCInfo::EffectSize, byte> EffectSize{};
        float LifeSpan{ 0.5f };

    public:
        EnemyBlowOffObject(const EnemyBlowOffObjectCInfo* in_pCreateInfo)
            : GameObject3D()
            , pCreateInfo(in_pCreateInfo)
            , PlayerNo(in_pCreateInfo->PlayerNo)
            , Owner(in_pCreateInfo->Owner)
            , EffectSize(in_pCreateInfo->Size)
        {

        }

        void AddCallback(GameDocument* in_pDocument) override
        {
            FUNCTION_PTR(void, __thiscall, fpAddCallback, ASLR(0x0072BD90), EnemyBlowOffObject*, GameDocument*);
            fpAddCallback(this, in_pDocument);

            /*fnd::GOComponent::Create<game::GOCGravity>(*this);
            fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
            fnd::GOComponent::Create<game::GOCAnimationSimple>(*this);
            fnd::GOComponent::Create<game::GOCCollider>(*this);
            fnd::GOComponent::Create<game::GOCEffect>(*this);
            fnd::GOComponent::Create<game::GOCSound>(*this);
            fnd::GOComponent::Create<game::GOCMovementComplex>(*this);

            fnd::GOComponent::BeginSetup(*this);

            if (auto* pTransform = GetComponent<fnd::GOCTransform>())
            {
                pTransform->SetLocalTranslation(pCreateInfo->TrsMatrix.GetTransVector());
                pTransform->SetLocalRotation({ pCreateInfo->TrsMatrix });
                
                pTransform->Frame.AddChild(&Frame);
                pTransform->Frame.SetLocalTranslation(pCreateInfo->Offset);
            }

            PositionOffset = pCreateInfo->Offset;
            Unk3 = { 0.0f, pCreateInfo->CollisionRadius * 0.5f, 0.0f };

            if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
            {
                fnd::GOCVisualModel::Description description{};
                description.Model = pCreateInfo->Model;
                description.Skeleton = pCreateInfo->Skeleton;

                pVisualModel->Setup(description);
                pVisualModel->SetLocalScale({ pCreateInfo->Scale, pCreateInfo->Scale, pCreateInfo->Scale });

                if (auto* pAnimation = GetComponent<game::GOCAnimationSimple>())
                {
                    if (pCreateInfo->Animation.IsValid())
                    {
                        pAnimation->Setup({ ms_AnimationCount });
                        pAnimation->Add(ms_pAnimationName, pCreateInfo->Animation, game::PlayPolicy::Loop);
                        pVisualModel->AttachAnimation(pAnimation);
                        pAnimation->SetAnimation(ms_pAnimationName);
                    }
                    else
                    {
                        pAnimation->Setup({ 0 });
                        pVisualModel->AttachAnimation(pAnimation);
                    }
                }
            }

            if (auto* pCollider = GetComponent<game::GOCCollider>())
            {
                pCollider->Setup({ ms_ShapeCount });

                game::ColliSphereShapeCInfo collisionInfo{};
                collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
                collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
                collisionInfo.Unk2 |= 1;
                collisionInfo.Radius = pCreateInfo->CollisionRadius;
                collisionInfo.ShapeID = 0;
                collisionInfo.pParent = &Frame;
                ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk9, collisionInfo);
                pCollider->CreateShape(collisionInfo);

                game::ColliSphereShapeCInfo collisionInfo2{};
                collisionInfo2.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
                collisionInfo2.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
                collisionInfo2.Unk2 |= 1;
                collisionInfo2.Radius = pCreateInfo->CollisionRadius;
                collisionInfo2.ShapeID = 1;
                collisionInfo2.pParent = &Frame;
                ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk3, collisionInfo2);
                pCollider->CreateShape(collisionInfo2);
            }

            game::GOCGravity::SimpleSetup(this, 1);

            if (auto* pMovement = GetComponent<game::GOCMovementComplex>())
            {
                if (pMoveBlowOff = pMovement->SetMoveController<MoveEnemyBlowOffObject>())
                {
                    csl::math::Vector3 normalizedOffset{};
                    math::Vector3NormalizeZero(pCreateInfo->Offset, &normalizedOffset);

                    pMoveBlowOff->Setup(GetService<CPhysicsWorld>(), pCreateInfo->Unk3, { normalizedOffset * (pCreateInfo->Offset.norm() - pCreateInfo->Unk3) });
                    pMoveBlowOff->SetCallbackHandle({this, static_cast<MoveEnemyBlowOffObject::CallbackHandle::MemFunc>(&EnemyBlowOffObject::NotifyStopCallback) });
                }

                pMovement->GetContextParam()->Velocity = { pCreateInfo->Unk6 * 0.7f };
            }

            if (GetComponent<game::GOCEffect>())
                game::GOCEffect::SimpleSetup(this, 0, false);

            game::GOCSound::SimpleSetup(this, 0, 0);

            auto* pCollisionWorld = GetService<Collision::CCollisionWorld>();
            csl::math::Sphere sphere{ pCreateInfo->TrsMatrix.GetTransVector(), 100.0f };
            csl::ut::MoveArray<game::ColliOverlapOutput> sweeps{ GetAllocator() };
            if (pCollisionWorld->OverlapSphere(sphere, 0x80000, &sweeps))
            {
                csl::math::Vector3 normalizedVector{};
                if (math::Vector3NormalizeIfNotZero(pCreateInfo->Unk6, &normalizedVector))
                {
                    float max = FLT_MAX;

                    for (size_t i = 0; i < sweeps.size(); i++)
                    {
                        GameObjectHandle<GameObject> target = sweeps[i].pShape->GetGameObject();
                        if (Owner != target)
                        {
                            csl::math::Vector3 positionDiff{ sweeps[i].pShape->Transform.GetTransVector() - pCreateInfo->TrsMatrix.GetTransVector() };
                            float length = math::Vector3NormalizeWithLength(positionDiff, &positionDiff);
                            if (length > 0.0f && length < max && cosf(MATHF_PI / 6.0f) < normalizedVector.dot(positionDiff))
                            {
                                max = length;
                                Target = target;
                            }
                        }
                    }
                }
            }

            pCreateInfo = nullptr;

            fnd::GOComponent::EndSetup(*this);

            UpdateTargetVelocity();*/
        }

        bool ProcessMessage(fnd::Message& in_rMessage) override
        {
            if (PreProcessMessage(in_rMessage))
                return true;

            switch (in_rMessage.GetType())
            {
            case xgame::MsgHitEventCollision::MessageID:        return ProcMsgHitEventCollision(static_cast<xgame::MsgHitEventCollision&>(in_rMessage));
            case xgame::MsgDamage::MessageID:                   return ProcMsgDamage(static_cast<xgame::MsgDamage&>(in_rMessage));
            default:											return GameObject3D::ProcessMessage(in_rMessage);
            }
        }
        
        void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
        {
            auto* pMovement = GetComponent<game::GOCMovementComplex>();
            if (!pMovement)
                return;

            auto* pTransform = GetComponent<fnd::GOCTransform>();
            if (!pTransform)
                return;

            auto* pContextParam = pMovement->GetContextParam();
            auto velocity = pContextParam->Velocity;
            auto trsMatrix = pTransform->Frame.Unk3.Mtx;
            csl::math::Vector3 up{ trsMatrix.GetColumn(1) };
            csl::math::Matrix34 inverseMtx{};
            csl::math::Matrix34Inverse(trsMatrix, &inverseMtx);

            if (math::Vector3NormalizeIfNotZero(velocity, &velocity))
            {
                if (!IsEnemyBlowOffRotationAngleSet)
                {
                    IsEnemyBlowOffRotationAngleSet = true;
                    EnemyBlowOffRotationAngle = MATHF_PI * 3.0f;
                }

                csl::math::Vector3 direction{ inverseMtx * csl::math::Vector3(up.cross(velocity)) };
                if (csl::math::Vector3NearZero(direction))
                {
                    up = { trsMatrix.GetColumn(1) };
                    direction = { inverseMtx * csl::math::Vector3(up.cross(velocity)) };
                }

                if (!csl::math::Vector3NearZero(direction))
                {
                    csl::math::Quaternion rotation{ Eigen::AngleAxisf(EnemyBlowOffRotationAngle * in_rUpdateInfo.deltaTime, direction) };

                    auto* pVisualModel = GetComponent<fnd::GOCVisualModel>();
                    if (!pVisualModel)
                        return;

                    rotation = csl::math::QuaternionMultiply(pVisualModel->Transform.GetRotationQuaternion(), rotation).Normalize();

                    pVisualModel->SetLocalRotation(rotation);
                    pVisualModel->SetLocalTranslation({ PositionOffset - math::Vector3Rotate(rotation, PositionOffset) });
                }
            }

            UpdateTargetVelocity();

            if (FrameLifeSpan > 0)
            {
                FrameLifeSpan--;
                if (FrameLifeSpan <= 0)
                    OnDead(false);
            }

            if (LifeSpan > 0.0f)
                LifeSpan -= in_rUpdateInfo.deltaTime;
            
            if (LifeSpan <= 0.0f && !Target.IsValid())
                OnDead(false);
            
            csl::math::Vector3 position{ pTransform->Frame.Unk3.GetTranslation() };
            if (csl::math::Vector3NearZero({ position - Unk4 }))
                OnDead(false);
            else
                Unk4 = position;
        }

        bool ProcMsgHitEventCollision(xgame::MsgHitEventCollision& in_rMessage)
        {
            if (in_rMessage.pSelf->GetID() != 1)
                return true;
        
            GameObjectHandle<GameObject> otherOwner = in_rMessage.pOther->GetGameObject();
            if (Owner == otherOwner)
                return true;

            auto* pMovement = GetComponent<game::GOCMovementComplex>();
            if (!pMovement)
                return true;

            xgame::MsgDamage msg{ 3, 0x800, 3, in_rMessage, pMovement->GetContextParam()->Velocity };
            msg.PlayerNo = PlayerNo;
            msg.Bonus.Unk1 = 7;

            return SendMessageImm(in_rMessage.Sender, msg);
        }

        bool ProcMsgDamage(xgame::MsgDamage& in_rMessage)
        {
            OnDead(true);
            return true;
        }

        void NotifyStopCallback()
        {
            FrameLifeSpan = 2;
        }

        void UpdateTargetVelocity()
        {


            if (!Target.Get())
            {
                pMoveBlowOff->SetTargetMove(false);
                return;
            }

            auto* pGravity = GetComponent<game::GOCGravity>();
            if (!pGravity)
                return;

            auto gravityDir{ pGravity->GetGravityDirection() };

            auto* pTargetTransform = Target.Get()->GetComponent<fnd::GOCTransform>();
            if (!pTargetTransform)
                return;

            csl::math::Vector3 targetPosition{ pTargetTransform->Frame.Unk3.Mtx * csl::math::Vector4(Unk3, 1.0f) };

            auto* pTransform = GetComponent<fnd::GOCTransform>();
            if (!pTransform)
                return;

            pTransform->Frame.Unk3.Mtx.GetColumn(1);
            csl::math::Vector3 distance{ targetPosition - pTransform->Frame.Unk3.Mtx.GetTransVector() };
            float length = math::Vector3NormalizeWithLength(distance, &distance);

            auto* pMovement = GetComponent<game::GOCMovementComplex>();
            if (!pMovement)
                return;

            auto* pContextParam = pMovement->GetContextParam();
            if (pContextParam->Velocity.dot(distance) <= 0.0f)
            {
                Target = { nullptr };
                pMoveBlowOff->SetTargetMove(false);
            }
            else
            {
                pContextParam->Velocity = { distance * pContextParam->Velocity.norm() };
                pMoveBlowOff->SetTargetMove(true);
            }
        }

        void OnDead(bool in_unk)
        {
            if (IsKilled())
                return;
        
            enemy::DeadEffectCInfo effectInfo{};
            effectInfo.Owner = this;
            effectInfo.PlayerNo = PlayerNo;

            switch ((EnemyBlowOffObjectCInfo::EffectSize)EffectSize)
            {
            case EnemyBlowOffObjectCInfo::EffectSize::eEffectSize_Yoshi:
            {
                effectInfo.SetYoshiIsland();
                break;
            }
            case EnemyBlowOffObjectCInfo::EffectSize::eEffectSize_ZeldaKeese:
            {
                effectInfo.SetZeldaKeese();
                break;
            }
            case EnemyBlowOffObjectCInfo::EffectSize::eEffectSize_ZeldaStalBabyHead:
            {
                effectInfo.SetZeldaStalBabyHead();
                break;
            }
            case EnemyBlowOffObjectCInfo::EffectSize::eEffectSize_ZeldaDekunuts:
            {
                effectInfo.SetZeldaDekunuts();
                break;
            }
            default:
                effectInfo.EffectSize = EffectSize;
                effectInfo.Flags.reset(2);
                break;
            }

            GetService<EnemyManager>()->CreateDeadEffect(effectInfo);
            Kill();
        }

        static EnemyBlowOffObject* Create(csl::fnd::IAllocator* in_pAllocator, GameDocument& in_rDocument, const app::EnemyBlowOffObjectCInfo& in_rCreateInfo)
        {
            auto* pObject = new EnemyBlowOffObject(&in_rCreateInfo);
            if (!pObject)
                return { nullptr };

            in_rDocument.AddGameObject(pObject);
            return pObject;
        }
    };
}