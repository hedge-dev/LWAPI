#pragma once

inline app::fnd::GameService* construct_EggManager(csl::fnd::IAllocator* in_pAllocator);

inline extern app::fnd::GameServiceClass EGG_MANAGER = app::fnd::GameServiceClass("EggManager", construct_EggManager);

namespace app
{
    namespace egg
    {
        struct EggCInfo
        {
            csl::math::Matrix34 Mtx{};
            size_t Type{};
        };

        inline float CalcSlipperyRatio(float in_unk1, float in_unk2)
        {
            return csl::math::Clamp(sinf(MATHF_PI * 2 / in_unk2 * in_unk1), -1.0f, 1.0f);
        }

        inline csl::math::Vector3 CalcSlipperyScale(float in_time, float in_unk1, float in_unk2, float in_unk3)
        {
            float ratio = fabs(CalcSlipperyRatio(in_time, in_unk1));
            return { in_unk3 * ratio + 1.0f, -(in_unk2 * ratio - 1.0f), 1.0f };
        }
    }

    class ObjEgg;

    class EggManager : public fnd::GameService
    {
    public:
        struct LocusData
        {
            csl::math::Vector3 Position{};
            csl::math::Quaternion Rotation{};
            bool IsAirborne{};
        };

        csl::ut::ObjectMoveArray<GameObjectHandle<ObjEgg>> Eggs{ GetAllocator() };
        csl::ut::CircularBuffer<LocusData> Loci{ csl::fnd::Singleton<GameObjectSystem>::GetInstance()->pPooledAllocator };
        float ElapsedTime{};
        csl::ut::Bitset<uint8> SpaceShrinkFlags{};
        csl::ut::Bitset<uint8> FlowerFlags{};

        EggManager();
        void StartGame(bool in_a1) override;
        void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override;
        bool AddEgg(GameObjectHandle<ObjEgg> in_egg, size_t* out_pIndex);
        void AddSpaceCount();
        void SubSpaceCount();
        bool CheckAccessLocusData(size_t in_index, LocusData* out_pOutput) const;
        void DoCheckClearAllEggEndExtrication();
        void DoCheckReleaseAllEgg();
        LocusData GetTargetData(size_t in_index, bool* out_pIsValid, float* out_pNorm) const;
        size_t GetTargetLocusIndex(size_t in_index) const;
        LocusData GetTargetDataFromLocusIndex(size_t in_index, bool* out_pIsValid, float* out_pNorm) const;
        bool IsEndExtrication() const;
        bool IsLocusDataInGroundToAir() const;
        bool IsYoshiSpecialFlowerTaked(size_t in_index) const;
        void TakeYoshiSpecialFlower(size_t in_index);
        void SetForceSpaceShrink(bool in_isShrink);
        void StartExtrication();
        void UpdateEggSpace();
        void UpdateLocusPos(float in_delta);
       
        inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEE764));

        static fnd::GameServiceClass& staticClass()
        {
            return *ms_pStaticClass;
        }
    };
}

namespace app
{
    class ObjEgg : public GameObject3D, public TTinyFsm<ObjEgg>
    {
    protected:
        inline static const char* ms_pGetSoundName = "obj_yossyegg_get";
        inline static const char* ms_pEggBreakSoundName = "obj_yossyeggitem_break";
        inline static const char* ms_pOneUpSoundName = "obj_yossy_1up";
        inline static const char* ms_pBirthEffectName = "ef_dl2_yossi_birth";
        inline static const size_t ms_ShapeCount = 1;
        inline static const float ms_CollisionRadius = 3.0f;
        inline static const csl::math::Vector3 ms_Scale = { 1.0f, 1.0f, 1.0f };

    public:
        const egg::EggCInfo* pCreateInfo{};
        size_t Type{};
        size_t Index{ static_cast<uint>(-1) };
        size_t SpaceOffset{ 10 };
        size_t ElapsedFrames{};
        float Time{};
        bool ApplyRotation{};
        csl::math::Vector3 DropVelocity{};
        float ElapsedTime{};
        float PositionOffset{};
        float LocalScaleX{ 1.0f };
        float LocalScaleY{ 1.0f };
        size_t SlipperyType{ 1 };
        csl::ut::Bitset<uint8> Flags{};

        ObjEgg(const egg::EggCInfo* in_pInfo) : GameObject3D(), TTinyFsm<ObjEgg>(&ObjEgg::StateToFirstLocus)
        {
            pCreateInfo = in_pInfo;
            Type = in_pInfo->Type;
        }

        void AddCallback(GameDocument* in_pDocument) override
        {
            fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
            fnd::GOComponent::Create<game::GOCCollider>(*this);
            fnd::GOComponent::Create<game::GOCGravity>(*this);
            fnd::GOComponent::Create<game::GOCEffect>(*this);
            fnd::GOComponent::Create<game::GOCSound>(*this);
            
            fnd::GOComponent::BeginSetup(*this);

            bool eggSuccess{};
            if (auto* pEggManager = in_pDocument->GetService<EggManager>())
                eggSuccess = pEggManager->AddEgg(this, &Index);

            if (auto* pTransform = GetComponent<fnd::GOCTransform>())
            {
                pTransform->SetLocalTranslation(pCreateInfo->Mtx.GetTransVector());
                pTransform->SetLocalRotation(pCreateInfo->Mtx.GetRotation());
            }
            
            auto* pInfo = ObjUtil::GetObjectInfo<ObjEggInfo>(*in_pDocument);

            if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
            {
                fnd::GOCVisualModel::Description description{};
                description.Model = pInfo->ModelContainer.Models[Type];
                description.Unk2 |= 0x400000u;
                description.ZOffset = -0.2f * Index - 2.0f;

                pVisualModel->Setup(description);
                pVisualModel->SetLocalScale(ms_Scale);
                
                csl::math::Quaternion q(Eigen::AngleAxisf(MATHF_PI * 0.5f, csl::math::Vector3::UnitY()));
                pVisualModel->SetLocalRotation({ q.normalized() });
            }

            if (auto* pCollider = GetComponent<game::GOCCollider>())
            {
                pCollider->Setup({ ms_ShapeCount });

                game::ColliSphereShapeCInfo collisionInfo{};
                collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Sphere;
                collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
                collisionInfo.Radius = ms_CollisionRadius;
                ObjUtil::SetupCollisionFilter(ObjUtil::eFilter_Unk2, collisionInfo);
                pCollider->CreateShape(collisionInfo);
            }

            if (auto* pGravity = GetComponent<game::GOCGravity>())
                game::GOCGravity::SimpleSetup(this, 1);

            if (auto* pEffect = GetComponent<game::GOCEffect>())
                game::GOCEffect::SimpleSetup(this, 0, 0);

            if (auto* pSound = GetComponent<game::GOCSound>())
                game::GOCSound::SimpleSetup(this, 0, 0);
            
            fnd::GOComponent::EndSetup(*this);

            pCreateInfo = nullptr;
            InitFSM();

            if (eggSuccess)
            {
                if (auto* pSound = GetComponent<game::GOCSound>())
                    pSound->Play(ms_pGetSoundName, 0.0f);
            }
            else
            {
                xgame::MsgTakeObject msg{ xgame::MsgTakeObject::eType_OneUp };
                if (ObjUtil::SendMessageImmToPlayer(*this, msg) && msg.Taken)
                {
                    if (auto* pEffect = GetComponent<game::GOCEffect>())
                        pEffect->CreateEffect(ms_pBirthEffectName);

                    if (auto* pSound = GetComponent<game::GOCSound>())
                        pSound->Play(ms_pOneUpSoundName, 0.0f);
                }
                
                Kill();
            }
        }

        bool ProcessMessage(fnd::Message& in_rMessage) override
        {
            switch (in_rMessage.GetType())
            {
            case xgame::MsgDlcChangeEggRotation::MessageID:				return ProcMsgDlcChangeEggRotation(static_cast<xgame::MsgDlcChangeEggRotation&>(in_rMessage));
            default:													return GameObject3D::ProcessMessage(in_rMessage);
            }
        }

        void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
        {
            DispatchFSM(TiFsmBasicEvent<ObjEgg>::CreateUpdate(in_rUpdateInfo.deltaTime));
        }

        bool ProcMsgDlcChangeEggRotation(xgame::MsgDlcChangeEggRotation& in_rMessage)
        {
            if (in_rMessage.IsEnter && !ApplyRotation)
            {
                ApplyRotation = true;
                LocalScaleX = 0.3f;
            }
            else if (ApplyRotation)
            {
                ApplyRotation = false;
                LocalScaleX = 0.03f;
            }

            return true;
        }

        bool AddSpaceOffset()
        {
            if (SpaceOffset >= 10)
                return false;
        
            SpaceOffset++;
            return true;
        }

        bool SubSpaceOffset()
        {
            if (!SpaceOffset)
                return false;

            SpaceOffset--;
            return true;
        }

        void Extrication()
        {
            if (auto* pEffect = GetComponent<game::GOCEffect>())
                pEffect->CreateEffect(ms_pBirthEffectName);

            if (auto* pSound = GetComponent<game::GOCSound>())
                pSound->Play(ms_pEggBreakSoundName, 0.0f);

            if (auto* pVisual = GetComponent<fnd::GOCVisualModel>())
                pVisual->SetVisible(false);

            auto* pTransform = GetComponent<fnd::GOCTransform>();
            csl::math::Matrix34 trsMatrix{ pTransform->Frame.Unk3.Mtx };
            auto rRotation = trsMatrix.GetRotation();

            csl::math::Vector3 upVector{ csl::math::Vector3::UnitY() * 10.0f };
            csl::math::Vector3 from{ trsMatrix * csl::math::Vector4(upVector, 1.0f) };
            csl::math::Vector3 to{ -trsMatrix.GetColumn(1) };

            auto* pPathComponent = ObjUtil::GetSVPath(*GetDocument(), from, to);
            if (pPathComponent)
            {
                game::PathEvaluator evaluator{};
                evaluator.SetPathObject(pPathComponent);
                if (evaluator.Component.IsValid())
                {
                    csl::math::Vector3 position{ trsMatrix.GetTransVector() };
                    float pathLength = evaluator.GetLength();
                    float distance{};

                    evaluator.GetClosestPositionAlongSpline(position, distance, 0.0f, &pathLength);
                    evaluator.SetDistance(distance);

                    csl::math::Vector3 point{};
                    csl::math::Vector3 normal{};
                    csl::math::Vector3 tangent{};
                    evaluator.GetPNT(evaluator.Distance, &point, &normal, &tangent);
                    
                    csl::math::Matrix34 mtx{};
                    mtx.SetColumn(0, { normal.cross(tangent) });
                    mtx.SetColumn(1, normal);
                    mtx.SetColumn(2, tangent);
                    mtx.SetColumn(3, { 0.0f, 0.0f, 0.0f });

                    rRotation = mtx.GetRotation();
                }
            }

            ObjYoshi::CInfo yoshiInfo{};
            yoshiInfo.Position = trsMatrix.GetTransVector();
            yoshiInfo.Rotation = rRotation;
            yoshiInfo.Type = YoshiTypes[Type];
            yoshiInfo.Index = Index;

            ObjYoshi::Create(*GetDocument(), yoshiInfo);
        }

        bool IsEndExtrication() const
        {
            if (FSM_STATE() == &ObjEgg::StateAfterExtrication)
                return true;

            return false;
        }

        void UpdateRotation(csl::math::Quaternion in_rotation, float in_delta)
        {
            auto rotation = csl::math::QuaternionNormalize(in_rotation);
            
            if (!ApplyRotation)
            {
                if (auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*GetDocument(), 0))
                    rotation = csl::math::QuaternionNormalize(pPlayerInfo->Rotation);
            }

            auto* pTransform = GetComponent<fnd::GOCTransform>();
            if (!pTransform)
                return;

            if (Time <= 0.0f)
            {
                pTransform->SetLocalRotation(rotation);
                return;
            }

            auto curRotation = pTransform->Frame.Unk3.GetRotationQuaternion();
            pTransform->SetLocalRotation(curRotation.slerp(csl::math::Clamp(1.0f - Time / 0.3f, 0.0f, 1.0f), rotation));
        
            Time -= in_delta;
        }

        void SlipperyInterpolate(float in_unk1, float in_positionOffsetTarget, float in_scaleXTarget, float in_scaleYTarget)
        {
            float time = ElapsedTime / in_unk1 * 0.5f;
            if (time > 1.0f)
                Flags.reset(1);

            PositionOffset = csl::math::Lerp(PositionOffset, in_positionOffsetTarget, time);
            LocalScaleX = csl::math::Lerp(LocalScaleX, in_scaleXTarget, time);
            LocalScaleY = csl::math::Lerp(LocalScaleY, in_scaleYTarget, time);
        }

        void SetSlipperyHeightScale(float in_positionOffset, float in_scaleX, float in_scaleY)
        {
            PositionOffset = in_positionOffset;
            LocalScaleX = in_scaleX;
            LocalScaleY = in_scaleY;
        }

        void UpdateSlippery(bool in_isAirborne, bool in_isValid, float in_delta, float in_norm)
        {
            auto* pVisualModel = GetComponent<fnd::GOCVisualModel>();
            if (!pVisualModel)
                return;
                
            size_t slipperyType = 2;
            if (!in_isAirborne)
                slipperyType = !in_isValid;
        
            if (SlipperyType != slipperyType)
            {
                Flags.set(1);
                Flags.reset(0);
                ElapsedTime = 0.0f;
                SlipperyType = slipperyType;
            }

            float power = 1.6f;
            float positionOffset = 0.0f;
            float scaleX = 1.0f;
            float scaleY = 1.0f;

            switch (SlipperyType)
            {
            case 0:
            {
                positionOffset = 0.0f;

                float scalar = 0.13f;
                scaleX = 0.6f;
                power = 0.18f;
                scaleY = 0.05f;

                if (Flags.test(0))
                {
                    scaleX = 0.4f;
                    power = 0.1f;
                    scaleY = 0.1f;
                    scalar = 0.1f;
                }

                ElapsedTime += in_delta;
                float ratio = egg::CalcSlipperyRatio(csl::math::Max(ElapsedTime + (Index * power * 0.25f), 0.0f), power);
                
                if (positionOffset <= ratio)
                {
                    scaleX = scaleY * ratio + 1.0f;
                    scaleY = -(scalar * ratio - 1.0f);
                }
                else
                {
                    positionOffset = scaleX * abs(ratio);
                    scaleX = 1.0f;
                    scaleY = 1.0f;
                }

                if (Flags.test(1))
                {
                    SlipperyInterpolate(power, positionOffset, scaleX, scaleY);
                }
                else
                {
                    SetSlipperyHeightScale(positionOffset, scaleX, scaleY);

                    bool flag = 60.0f * in_delta < in_norm;
                    if (Flags.test(0) != flag)
                    {
                        if (!flag)
                            power = 0.18f;
                    }

                    PositionOffset = Index * power * 0.25f;
                    Flags.set(0, flag);
                }

                break;
            }
            case 1:
            {
                ElapsedTime += in_delta;
                float ratio = egg::CalcSlipperyRatio(ElapsedTime + (Index * power * 0.25f), power);
                scaleX = 0.1f * abs(ratio) + 1.0f;
                scaleY = 1.0f - 0.1f * abs(ratio);

                if (Flags.test(1))
                {
                    SlipperyInterpolate(power, positionOffset, scaleX, scaleY);
                }
                else
                {
                    SetSlipperyHeightScale(positionOffset, scaleX, scaleY);
                }

                break;
            }
            case 2:
            {
                power = 0.2f;

                ElapsedTime += in_delta;
                if (Flags.test(1))
                {
                    SlipperyInterpolate(power, positionOffset, scaleX, scaleY);
                }

                break;
            }
            default:
                break;
            }

            pVisualModel->SetLocalScale({ LocalScaleX, LocalScaleY, 1.0f });
            pVisualModel->SetLocalTranslation({ csl::math::Vector3::UnitY() * PositionOffset });
        }

        void StartDrop()
        {
            ChangeState(&ObjEgg::StateDrop);
        }

        void StartExtrication()
        {
            ChangeState(&ObjEgg::StateMoveToExtrication);
        }

        void ChangeState(TiFsmState_t in_state)
        {
            FSM_TRAN(in_state);
        }

        TiFsmState_t StateToFirstLocus(const TiFsmBasicEvent<ObjEgg>& in_rEvent)
        {
            switch (in_rEvent.getSignal())
            {
            case TiFSM_SIGNAL_ENTER:
            {
                ElapsedFrames = 0;
                if (auto* pLevelInfo = GetDocument()->GetService<CLevelInfo>())
                {
                    if (pLevelInfo->StageFlags.test(16))
                    {
                        Time = 30.0f / 30.0f;
                    }
                    else
                    {
                        Time = 30.0f / 60.0f;
                    }
                }

                return {};
            }
            case TiFSM_SIGNAL_UPDATE:
            {
                auto* pEggManager = GetDocument()->GetService<EggManager>();
                if (!pEggManager)
                    return {};

                auto* pTransform = GetComponent<fnd::GOCTransform>();
                if (!pTransform)
                    return {};

                auto targetLocus = pEggManager->GetTargetDataFromLocusIndex(0, nullptr, nullptr);

                auto position = pTransform->Frame.Unk3.GetTranslation();

                pTransform->SetLocalTranslation({ (targetLocus.Position - position) * csl::math::Clamp(ElapsedFrames / 30.0f, 0.0f, 1.0f) + position });
                UpdateRotation(targetLocus.Rotation, in_rEvent.getFloat());
                UpdateSlippery(targetLocus.IsAirborne, true, in_rEvent.getFloat(), 0.0f);

                ++ElapsedFrames;
                if (ElapsedFrames > 30)
                {
                    ChangeState(&ObjEgg::StateToIndexLocus);
                }

                return {};
            }
            default:
                return FSM_TOP();
            }
        }

        TiFsmState_t StateToIndexLocus(const TiFsmBasicEvent<ObjEgg>& in_rEvent)
        {
            switch (in_rEvent.getSignal())
            {
            case TiFSM_SIGNAL_ENTER:
            {
                ElapsedFrames = 0;
                
                return {};
            }
            case TiFSM_SIGNAL_UPDATE:
            {
                auto* pEggManager = GetDocument()->GetService<EggManager>();
                if (!pEggManager)
                    return {};

                auto* pTransform = GetComponent<fnd::GOCTransform>();
                if (!pTransform)
                    return {};
                
                auto locusIndex = pEggManager->GetTargetLocusIndex(Index);
                auto index = ElapsedFrames;
                if (locusIndex < index)
                    index = locusIndex;

                auto targetLocus = pEggManager->GetTargetDataFromLocusIndex(index, nullptr, nullptr);

                pTransform->SetLocalTranslation(targetLocus.Position);
                UpdateRotation(targetLocus.Rotation, in_rEvent.getFloat());
                UpdateSlippery(targetLocus.IsAirborne, true, in_rEvent.getFloat(), 0.0f);

                ++ElapsedFrames;
                if (locusIndex < ElapsedFrames)
                {
                    ChangeState(&ObjEgg::StateMoveIndexLocus);
                }

                return {};
            }
            default:
                return FSM_TOP();
            }
        }

        TiFsmState_t StateMoveToExtrication(const TiFsmBasicEvent<ObjEgg>& in_rEvent)
        {
            switch (in_rEvent.getSignal())
            {
            case TiFSM_SIGNAL_ENTER:
            {
                return {};
            }
            case TiFSM_SIGNAL_UPDATE:
            {
                bool isExtricationReady = true;

                auto* pEggManager = GetDocument()->GetService<EggManager>();
                if (!pEggManager)
                    return {};

                auto locusIndex = pEggManager->GetTargetLocusIndex(Index);
                if (locusIndex)
                {
                    for (size_t i = 0; i < locusIndex;)
                    {
                        if (pEggManager->GetTargetDataFromLocusIndex(i, nullptr, nullptr).IsAirborne)
                        {
                            isExtricationReady = false;
                            break;
                        }
                    
                        if (++i >= locusIndex)
                            break;
                    }
                }

                auto targetLocus = pEggManager->GetTargetDataFromLocusIndex(locusIndex, nullptr, nullptr);

                auto* pTransform = GetComponent<fnd::GOCTransform>();
                if (!pTransform)
                    return {};

                pTransform->SetLocalTranslation(targetLocus.Position);
                UpdateRotation(targetLocus.Rotation, in_rEvent.getFloat());
                UpdateSlippery(targetLocus.IsAirborne, true, in_rEvent.getFloat(), 0.0f);

                if (targetLocus.IsAirborne)
                    return {};

                if (isExtricationReady)
                {
                    Extrication();
                    ChangeState(&ObjEgg::StateAfterExtrication);
                }

                return {};
            }
            default:
                return FSM_TOP();
            }
        }

        TiFsmState_t StateMoveIndexLocus(const TiFsmBasicEvent<ObjEgg>& in_rEvent)
        {
            switch (in_rEvent.getSignal())
            {
            case TiFSM_SIGNAL_ENTER:
            {
                return {};
            }
            case TiFSM_SIGNAL_UPDATE:
            {
                auto* pEggManager = GetDocument()->GetService<EggManager>();
                if (!pEggManager)
                    return {};

                auto* pTransform = GetComponent<fnd::GOCTransform>();
                if (!pTransform)
                    return {};

                bool isValidLocus{};
                float locusNorm{};
                auto targetLocus = pEggManager->GetTargetData(Index, &isValidLocus, &locusNorm);

                pTransform->SetLocalTranslation(targetLocus.Position);
                UpdateRotation(targetLocus.Rotation, in_rEvent.getFloat());
                UpdateSlippery(targetLocus.IsAirborne, isValidLocus, in_rEvent.getFloat(), locusNorm);

                return {};
            }
            default:
                return FSM_TOP();
            }
        }

        TiFsmState_t StateDrop(const TiFsmBasicEvent<ObjEgg>& in_rEvent)
        {
            switch (in_rEvent.getSignal())
            {
            case TiFSM_SIGNAL_ENTER:
            {
                ElapsedFrames = 0;

                auto* pCamera = GetDocument()->pWorld->GetCamera(0);

                auto* pGravity = GetComponent<game::GOCGravity>();
                if (!pGravity)
                    return {};

                csl::math::Vector3 dropDirection{ pGravity->GetGravityDirection() * -1.0f };
                csl::math::Vector3 cameraView{ pCamera->GetInvViewMatrix() * csl::math::Vector3(csl::math::Vector3::UnitZ()) };
                csl::math::Vector3 velocity{ dropDirection + cameraView };
                if (math::Vector3NormalizeIfNotZero(velocity, &velocity))
                    DropVelocity = { velocity * 50.0f };

                return {};
            }
            case TiFSM_SIGNAL_UPDATE:
            {
                auto* pGravity = GetComponent<game::GOCGravity>();
                if (!pGravity)
                    return {};

                DropVelocity += csl::math::Vector3(pGravity->GetGravityDirection() * 200.0f * in_rEvent.getFloat());

                auto* pTransform = GetComponent<fnd::GOCTransform>();
                if (!pTransform)
                    return {};

                auto position = pTransform->Frame.Unk3.GetTranslation();
                
                pTransform->SetLocalTranslation({ position + DropVelocity * in_rEvent.getFloat() });
                if (!(ElapsedFrames % 5))
                {
                    if (auto* pVisualModel = GetComponent<fnd::GOCVisualModel>())
                        pVisualModel->SetVisible(!pVisualModel->IsVisible());
                }

                ElapsedFrames++;
                if (ElapsedFrames > 300)
                    Kill();

                return {};
            }
            default:
                return FSM_TOP();
            }
        }

        TiFsmState_t StateAfterExtrication(const TiFsmBasicEvent<ObjEgg>& in_rEvent)
        {
            return FSM_TOP();
        }
    };
}

inline app::fnd::GameService* construct_EggManager(csl::fnd::IAllocator* in_pAllocator)
{
    return new(in_pAllocator) app::EggManager();
}