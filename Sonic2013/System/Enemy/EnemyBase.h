#pragma once

namespace app
{
    class EnemyBase : public CSetObjectListener
    {
    private:
        inline static FUNCTION_PTR(void, __thiscall, ms_fpCreateEnemyBlowOffObject, ASLR(0x006720D0), void* pThis, EnemyBlowOffObjectCInfo&);

    public:
        fnd::HFrame Unk1{};

        EnemyBase() : CSetObjectListener()
        {
            SetObjectCategory(7);
            AddProperty(0x4001, { 3 });
        }

        void CreateCenterPositionFrame(const csl::math::Vector3& in_rCenterPosition)
        {
            GetComponent<fnd::GOCTransform>()->Frame.AddChild(&Unk1);
            Unk1.SetLocalTranslation(in_rCenterPosition);
        }

        fnd::HFrame* GetCenterPositionFrame() const
        {
            if (!Unk1.pParent)
                return &GetComponent<fnd::GOCTransform>()->Frame;
        
            return const_cast<fnd::HFrame*>(&Unk1);
        }

        void SendTouchDamage(xgame::MsgHitEventCollision& in_rMessage)
        {
            xgame::MsgDamage msgDamage{ 3, 8, 1, in_rMessage, {0.0f, 0.0f, 0.0f} };
            SendMessageImm(in_rMessage.Sender, msgDamage);
        }

        void CreateDeadEffect(enemy::DeadEffectCInfo in_rCreateInfo)
        {
            GetService<EnemyManager>()->CreateDeadEffect(in_rCreateInfo);
        }

        void CreateEnemyBlowOffObject(EnemyBlowOffObjectCInfo in_rCreateInfo)
        {
            in_rCreateInfo.Owner = this;
            EnemyBlowOffObject::Create(GetAllocator(), *GetDocument(), in_rCreateInfo);

            xgame::MsgMissionEvent msg{};
            msg.Type = 7;
            msg.Unk1 = 1;

            ObjUtil::SendMessageImmToGameActor(*this, msg);
        }

        void ProcMission(xgame::MsgDamage& in_rMessage)
        {
            xgame::MsgMissionEvent msgMission{};

            if (AttackType::IsDamaged(in_rMessage.AttackType, 0xA))
                msgMission.Type = 33;
            else if (AttackType::IsDamaged(in_rMessage.AttackType, 0x40))
                msgMission.Type = 34;
            else if (AttackType::IsDamaged(in_rMessage.AttackType, 0x100))
                msgMission.Type = 35;
            else if (AttackType::IsDamaged(in_rMessage.AttackType, 0x1000000))
                msgMission.Type = 36;
            else if (AttackType::IsDamaged(in_rMessage.AttackType, 0x800000))
                msgMission.Type = 37;
            else if (AttackType::IsDamaged(in_rMessage.AttackType, 0x2000000))
                msgMission.Type = 38;
            else if (AttackType::IsDamaged(in_rMessage.AttackType, 0x4000000))
                msgMission.Type = 39;
            else if (AttackType::IsDamaged(in_rMessage.AttackType, 0x8000000))
                msgMission.Type = 40;
            else
                msgMission.Type = 32;

            msgMission.Unk1 = 1;
            ObjUtil::SendMessageImmToGameActor(*this, msgMission);
        }

        void ProcMission()
        {
            xgame::MsgMissionEvent msg{};
            msg.Type = 32;
            msg.Unk1 = 1;
            
            ObjUtil::SendMessageImmToGameActor(*this, msg);
        }

        bool ProcessMessage(fnd::Message& in_rMessage) override
        {
            if (PreProcessMessage(in_rMessage))
                return true;

            switch (in_rMessage.GetType())
            {
            case xgame::MsgPLGetHomingTargetInfo::MessageID:		return ProcMsgPLGetHomingTargetInfo(static_cast<xgame::MsgPLGetHomingTargetInfo&>(in_rMessage));
            case xgame::MsgPLKickTargetting::MessageID:				return ProcMsgPLKickTargetting(static_cast<xgame::MsgPLKickTargetting&>(in_rMessage));
            default:												return CSetObjectListener::ProcessMessage(in_rMessage);
            }
        }

        bool ProcMsgPLGetHomingTargetInfo(xgame::MsgPLGetHomingTargetInfo& in_rMessage) const
        {
            in_rMessage.CursorPosition = GetCenterPositionFrame()->Unk3.GetTranslation();
            in_rMessage.Flags.set(3);

            return true;
        }

        bool ProcMsgPLKickTargetting(xgame::MsgPLKickTargetting& in_rMessage) const
        {
            in_rMessage.Success = true;

            return true;
        }
    };
}
