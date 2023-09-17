#pragma once

namespace app::game
{
    typedef uint8 MovementFlag;

    class GOCMovement : public fnd::GOComponent
    {
    private:
        inline static FUNCTION_PTR(MoveController*, __thiscall, ms_fpGetMoveController, ASLR(0x004C3850), const GOCMovement*, size_t);

    public:
        class ContextParam
        {
        public:
            csl::math::Vector3 Position{};
            csl::math::Quaternion Rotation{};
            csl::math::Vector3 Velocity{};
        };

        csl::ut::MoveArray<MoveController*> Controllers{ GetAllocator() };
        ContextParam ContextParameter{};
        csl::ut::Bitset<uint8> Flags{};

        GOCMovement() : GOComponent()
        {
            unk1 = 3;
            m_Flags.set(0, true);
        }

        virtual void OnGOCEventInside(int in_event, GameObject& in_rObject, void* in_pData) = 0;

        void OnGOCEvent(int in_event, GameObject& in_rObject, void* in_pData) override
        {
            if (!in_event)
            {
                Controllers.clear();
                ContextParameter.Velocity = *csl::math::Vector3::Zero;
                EnableMovementFlag(0);
                EnableMovementFlag(1);
                OnGOCEventInside(0, in_rObject, in_pData);
                return;
            }

            if (in_event == 1)
            {
                if (auto* pTransform = in_rObject.GetComponent<fnd::GOCTransform>())
                {
                    ContextParameter.Position = pTransform->m_Frame.m_Unk3.GetTranslation();
                    ContextParameter.Rotation = pTransform->m_Frame.m_Unk3.GetRotationQuaternion();
                    Flags.set(2);
                }

                for (auto* pMoveController : Controllers)
                {
                    detail_movement::CallEndSetup(pMoveController);
                    detail_movement::CallOnEnter(pMoveController);
                }
            }

            OnGOCEventInside(in_event, in_rObject, in_pData);
        }

        void EnableMovementFlag(MovementFlag in_flag)
        {
            Flags.set(in_flag);
        }

        void DisableMovementFlag(MovementFlag in_flag)
        {
            Flags.reset(in_flag);
        }

        ContextParam* GetContextParam()
        {
            return &ContextParameter;
        }

        const char* GetFamilyID() const override
        {
            return "GOCMovement";
        }

    private:
        // This is the original function name by Sonic Team.
        void ClaerMoveController(uint in_index)
        {
            detail_movement::ResetUpdateFlag(Controllers[in_index]);
            Controllers.remove(in_index);
        }

    public:
        inline void ClearMoveController(uint in_index) { ClaerMoveController(in_index); }

        void ClearContainer()
        {
            Controllers.clear();
        }

        MoveController* GetMoveController(size_t in_index) const
        {
            return ms_fpGetMoveController(this, in_index);
        }

        void ResetControllerUpdateFlag(uint in_controllerIndex)
        {
            if (auto* pMoveController = GetMoveController(in_controllerIndex))
                detail_movement::ResetUpdateFlag(pMoveController);
        }

        void ResetControllerUpdateFlagAll()
        {
            for (auto* pMoveController : Controllers)
                detail_movement::ResetUpdateFlag(pMoveController);
        }

        void SetControllerUpdateFlag(uint in_controllerIndex)
        {
            if (auto* pMoveController = GetMoveController(in_controllerIndex))
                detail_movement::SetUpdateFlag(pMoveController);
        }

        void SetControllerUpdateFlagAll()
        {
            for (auto* pMoveController : Controllers)
                detail_movement::SetUpdateFlag(pMoveController);
        }

        void SetupController(MoveController* in_pController)
        {
            in_pController->SetOwnerMovement(this);
            Controllers.push_back(in_pController);
            if (Flags.test(2))
            {
                in_pController->SetFlag(MoveController::FlagType::eFlagType_0);
                in_pController->OnEnter();
            }
        }
    };
}