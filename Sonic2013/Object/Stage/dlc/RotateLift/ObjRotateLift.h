#pragma once

namespace app
{
    class ObjRotateLift : public CSetObjectListener
    {
    private:
        inline static const char* ms_pSoundName = "obj_yossyrollinglift_rotate";
        inline static const uint8 ms_StepCount = 4;
        inline static csl::math::Vector3 ms_StepOffset = { 0.0f, 0.0f, 25.0f };
        inline static csl::math::Vector3 ms_CollisionSize = { 3.0f, 2.5f, 7.5f };

    public:
        csl::ut::InplaceObjectMoveArray<fnd::HFrame, ms_StepCount> Frames{ GetAllocator() };
        uint8 StepCount{ ms_StepCount };
        bool IsEventDriven{};

    public:
        ObjRotateLift() : CSetObjectListener()
        {
            SetObjectCategory(4);
        }

    protected:
        void AddCallback(GameDocument* in_pDocument) override
        {
            fnd::GOComponent::Create<fnd::GOCVisualContainer>(*this);
            fnd::GOComponent::Create<game::GOCSound>(*this);
            fnd::GOComponent::Create<game::GOCCollider>(*this);
            fnd::GOComponent::Create<game::GOCMotorRotate>(*this);
            
            fnd::GOComponent::BeginSetup(*this);

            auto* pInfo = ObjUtil::GetObjectInfo<ObjRotateLiftInfo>(*in_pDocument);
            auto* pParam = GetAdapter()->GetData<SRotateLiftParam>();
            IsEventDriven = pParam->isEventDriven;

            StepCount = ms_StepCount;
            Frames.resize(ms_StepCount);
            
            if (auto* pTransform = GetComponent<fnd::GOCTransform>())
            {
                csl::math::Quaternion rotation = GetAdapter()->GetRotation();
                for (size_t i = 0; i < StepCount; i++)
                {
                    auto position = math::Vector3RotateX(MATHF_PI * i / 2, ms_StepOffset);
                    Frames[i].SetLocalTranslation(position);
                    Frames[i].SetLocalRotation(rotation);
                    Frames[i].ResetFlag(32);
                    pTransform->Frame.AddChild(&Frames[i]);
                }
            }

            if (auto* pVisualContainer = GetComponent<fnd::GOCVisualContainer>())
            {
                pVisualContainer->Setup({ (uint)(StepCount + 1) });

                for (size_t i = 0; i < StepCount; i++)
                {
                    auto* pVisualModel = fnd::GOComponent::CreateSingle<fnd::GOCVisualModel>(*this);
                    pVisualContainer->Add(pVisualModel);

                    fnd::GOCVisualModel::Description description{};
                    description.Model = pInfo->ModelContainer.Models[0];
                    description.pParent = &Frames[i];

                    pVisualModel->Setup(description);
                }

                auto* pVisualModel = fnd::GOComponent::CreateSingle<fnd::GOCVisualModel>(*this);
                pVisualContainer->Add(pVisualModel);
                
                fnd::GOCVisualModel::Description description{};
                description.Model = pInfo->ModelContainer.Models[1];
                
                pVisualModel->Setup(description);
                pVisualModel->SetLocalRotation(csl::math::Quaternion(Eigen::AngleAxisf(MATHF_PI / 2.0f, csl::math::Vector3::UnitY())));
            }

            game::GOCSound::SimpleSetup(this, 1, 0);

            if (auto* pCollider = GetComponent<game::GOCCollider>())
            {
                pCollider->Setup({ StepCount });
                
                for (size_t i = 0; i < StepCount; i++)
                {
                    game::ColliBoxShapeCInfo collisionInfo{};
                    collisionInfo.ShapeType = game::CollisionShapeType::ShapeType::eShapeType_Box;
                    collisionInfo.MotionType = game::PhysicsMotionType::MotionType::eMotionType_Value2;
                    collisionInfo.Flags = 14;
                    collisionInfo.Unk2 |= 0x100;
                    collisionInfo.Unk3 = 0x4003;
                    collisionInfo.Size = ms_CollisionSize;
                    collisionInfo.pParent = &Frames[i];

                    pCollider->CreateShape(collisionInfo);
                }
            }
            
            if (auto* pMotor = GetComponent<game::GOCMotorRotate>())
            {
                game::GOCMotorRotate::Description description{ csl::math::Vector3::UnitX().eval(), pParam->omega, pParam->offset, pParam->useGlobalTime };
                
                pMotor->Setup(description);
                if (IsEventDriven)
                    pMotor->RequestEnable(false);
            }

            if (auto* pSound = GetComponent<game::GOCSound>())
                pSound->Play3D(ms_pSoundName, 0.0f);

            fnd::GOComponent::EndSetup(*this);
        }

        bool ProcessMessage(fnd::Message& in_rMessage) override
        {
            if (PreProcessMessage(in_rMessage))
                return true;

            switch (in_rMessage.GetType())
            {
            case xgame::MsgNotifyObjectEvent::MessageID:				return ProcMsgNotifyObjectEvent(static_cast<xgame::MsgNotifyObjectEvent&>(in_rMessage));
            default:													return CSetObjectListener::ProcessMessage(in_rMessage);
            }
        }
        
        bool ProcMsgNotifyObjectEvent(xgame::MsgNotifyObjectEvent& in_rMessage)
        {
            if (!IsEventDriven)
                return true;

            if (auto* pMotor = GetComponent<game::GOCMotorRotate>())
            {
                if (in_rMessage.GetEventType() == 1)
                    pMotor->RequestEnable(true);
                else if (in_rMessage.GetEventType() == 2)
                    pMotor->RequestEnable(false);
            }

            return true;
        }
    };
}