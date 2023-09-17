#pragma once

namespace app::enemy
{
    enum EffectSize : uint8
    {
        eEffectSize_Normal,
        eEffectSize_Medium,
        eEffectSize_Large,
        eEffectSize_MAXNUM
    };

    enum SoundType : uint8
    {
        eSoundType_ExplosionCommon,
        eSoundType_ExplosionMid,
        eSoundType_ExplosionYoshiCommon,
        eSoundType_ExplosionKeese,
        eSoundType_ExplosionZeldaCommon,
        eSoundType_MAXNUM
    };

    class DeadEffectCInfo
    {
    public:
        GameObjectHandle<GameObject> Owner{};
        size_t AttackType{};
        int Unk1{ 1 };
        uint PlayerNo{ static_cast<uint>(-1) };
        csl::math::Matrix34 Mtx{};
        csl::ut::Enum<EffectSize, byte> EffectSize{};
        csl::ut::Enum<SoundType, byte> SoundType{};
        csl::ut::Bitset<uint16> Flags{ 1, 2 };

        void SetMsgDamage(const xgame::MsgDamage& in_rMessage)
        {
            AttackType = in_rMessage.AttackType;
            PlayerNo = in_rMessage.PlayerNo;

            switch (in_rMessage.m_Bonus.m_Unk1)
            {
            case 0:
            case 1:
            case 3:
                Unk1 = csl::math::Min<uint>(in_rMessage.m_Bonus.m_Unk1, 6);
                break;
            case 4:
                Unk1 = 1;
                break;
            }
        }

        void SetTransform(const csl::math::Matrix34& in_rMtx)
        {
            Mtx = in_rMtx;
            Flags.set(0);
        }

        void SetYoshiIsland()
        {
            Flags.reset(1);
            Flags.reset(2);
            Flags.set(4);
            SoundType = 2;
        }

        void SetZeldaKeese()
        {
            Flags.reset(1);
            Flags.set(5);
            SoundType = 3;
        }

        void SetZeldaStalBaby()
        {
            Flags.reset(1);
            Flags.set(6);
            SoundType = 4;
        }

        void SetZeldaStalBabyHead()
        {
            Flags.reset(1);
            Flags.set(7);
            SoundType = 4;
        }
        
        void SetZeldaDekunuts()
        {
            Flags.reset(1);
            Flags.set(8);
            SoundType = 5;
        }
    };
}