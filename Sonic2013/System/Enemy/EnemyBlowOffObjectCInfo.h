#pragma once

namespace app
{
    class EnemyBlowOffObjectCInfo
    {
    public:
        enum EffectSize : uint8
        {
            eEffectSize_Normal,
            eEffectSize_Medium,
            eEffectSize_Large,
            eEffectSize_Yoshi,
            eEffectSize_ZeldaKeese,
            eEffectSize_ZeldaStalBabyHead,
            eEffectSize_ZeldaDekunuts,
            eEffectSize_MAXNUM
        };

        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        hh::gfx::res::ResAnimSkeleton Animation{};
        csl::math::Matrix34 TrsMatrix{};
        csl::math::Vector3 Offset{};
        float CollisionRadius{};
        float Unk3{};
        float Scale{ 1.0f };
        csl::ut::Enum<EffectSize, byte> Size{};
        csl::math::Vector3 Unk6{};
        size_t PlayerNo{ static_cast<size_t>(-1) };
        GameObjectHandle<GameObject> Owner{};

        void SetParamByMessage(const xgame::MsgKick& in_rMessage)
        {
            Unk6 = in_rMessage.Unk3;
            PlayerNo = in_rMessage.PlayerNo;
        }
    };
}