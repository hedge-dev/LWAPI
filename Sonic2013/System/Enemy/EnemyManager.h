#pragma once

namespace app
{
    class ObjPopupItem;
    class ObjZeldaPopupItem;

    enum ZeldaPopupItemType : uint8
    {
        eZeldaPopupItemType_RupeeGreen,
        eZeldaPopupItemType_RupeeBlue,
        eZeldaPopupItemType_RupeeRed,
        eZeldaPopupItemType_RupeePurple,
        eZeldaPopupItemType_RupeeGold,
        eZeldaPopupItemType_Heart,
    };

    namespace zelda_popupitem
    {
        struct ZeldaPopupItemCinfo
        {
        public:
            csl::math::Matrix34 Matrix{};
            ZeldaPopupItemType Type{};
            uint PlayerNo{};

            ZeldaPopupItemCinfo(csl::math::Matrix34 in_matrix, ZeldaPopupItemType in_type, uint in_playerNo)
            {
                Matrix = in_matrix;
                Type = in_type;
                PlayerNo = in_playerNo;
            }
        };

        inline static ObjZeldaPopupItem* CreateZeldaPopupItem(csl::fnd::IAllocator*, GameDocument& in_rDocument, const ZeldaPopupItemCinfo& in_rCreateInfo);
    }

    namespace popup_item
    {
        enum EType : uint8
        {
            eType_Ring,
            eType_SuperRing,
            eType_OneUp,
            eType_SpeedUp,
            eType_Invincible,
            eType_SlowDown,
            eType_Missile,
            eType_Warp,
            eType_StealRing,
            eType_ThunderBarrier,
            eType_ChangeRing,
            eType_PhantomLaser,
            eType_PhantomEagle,
            eType_PhantomAsteroid,
            eType_PhantomDrill,
            eType_PhantomRocket,
            eType_PhantomRhythm,
            eType_PhantomHover,
            eType_PhantomQuake
        };
        
        struct SParam
        {
            int PlayerActorID{};
            EType Type{};
            float Unk2{ 130.0f };
            float Unk3{ 550.0f };
            float Unk4{ 0.15f };
            int Unk5{ 1 };
            csl::math::Vector3 Position{};
            csl::math::Quaternion Rotation{};
            char Unk6{};
        };

        inline static ObjPopupItem* Create(GameDocument& in_rDocument, const SParam& in_rParam);
    }

    class EnemyManager : fnd::GameService
    {
    private:
        inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEE344));
        inline static const char* ms_pEffectSizes[] = { "ef_en_com_yh1_explo1", "ef_en_com_wt1_explo_m", "ef_en_com_wt1_explo_l" };

    public:
        AnimalManager AnimalManager{};
        INSERT_PADDING(24); // EggPawnManager EggPawnManager{};
        INSERT_PADDING(16); // csl::ut::LinkList<EffectInfo> Effects{};
        Effect::CEffectManager* pEffectManager{};
        csl::ut::Bitset<uint8> Unk2{ 0 };

        EnemyManager() : fnd::GameService(0)
        {

        }

        void CreateDeadEffect(const enemy::DeadEffectCInfo& in_rCreateInfo)
        {
            if (!pEffectManager)
                return;
        
            csl::math::Matrix34 effectMtx{};
            Effect::CEffectHandle<hh::eff::CEffectInstance> effectHandle{};

            if (in_rCreateInfo.Flags.test(0))
            {
                effectMtx = in_rCreateInfo.Mtx;
            }
            else
            {
                if (auto* pObject = in_rCreateInfo.Owner.Get())
                    effectMtx = pObject->GetComponent<fnd::GOCTransform>()->m_Frame.m_Unk3.m_Mtx;
            }

            if (in_rCreateInfo.Flags.test(3))
            {
                pEffectManager->CreateEffect(&effectHandle, "ef_en_gbe_wt1_explo1", effectMtx, 0);
            }
            else if (in_rCreateInfo.Flags.test(4))
            {
                pEffectManager->CreateEffect(&effectHandle, "ef_dl2_com_dead", effectMtx, 0);
            }
            else if (in_rCreateInfo.Flags.test(5))
            {
                pEffectManager->CreateEffect(&effectHandle, "ef_dl3_keese_dead", effectMtx, 0);
            }
            else if (!in_rCreateInfo.Flags.test(6))
            {
                if (in_rCreateInfo.Flags.test(7))
                {
                    pEffectManager->CreateEffect(&effectHandle, "ef_dl3_stalbaby_dead_head", effectMtx, 0);
                }
                else if (in_rCreateInfo.Flags.test(8))
                {
                    pEffectManager->CreateEffect(&effectHandle, "ef_dl3_dekunuts_dead", effectMtx, 0);
                }
                else
                {
                    pEffectManager->CreateEffect(&effectHandle, ms_pEffectSizes[(uint8)in_rCreateInfo.EffectSize], effectMtx, 0);
                }
            }

            csl::math::Vector3 soundPos = effectMtx.GetTransVector();
            switch ((enemy::SoundType)in_rCreateInfo.SoundType)
            {
            case enemy::SoundType::eSoundType_ExplosionMid:
            {
                ObjUtil::PlaySE("enm_mid_explosion", soundPos, { HH_SOUND_DEVICE_AUTO });
                break;
            }
            case enemy::SoundType::eSoundType_ExplosionYoshiCommon:
            {
                ObjUtil::PlaySE("enm_yossycmn_explosion", soundPos, { HH_SOUND_DEVICE_AUTO });
                break;
            }
            case enemy::SoundType::eSoundType_ExplosionKeese:
            {
                ObjUtil::PlaySE("enm_keese_explosion", soundPos, { HH_SOUND_DEVICE_AUTO });
                break;
            }
            case enemy::SoundType::eSoundType_ExplosionZeldaCommon:
            {
                ObjUtil::PlaySE("enm_zeldacmn_explosion", soundPos, { HH_SOUND_DEVICE_AUTO });
                break;
            }
            case enemy::SoundType::eSoundType_ExplosionDekunuts:
            {
                break;
            }
            default:
            {
                ObjUtil::PlaySE("enm_cmn_explosion", soundPos, { HH_SOUND_DEVICE_AUTO });
                break;
            }
            }

            if (in_rCreateInfo.Flags.test(2) && in_rCreateInfo.PlayerNo >= 0 && AttackType::And(in_rCreateInfo.AttackType, 32))
            {
                if (in_rCreateInfo.Flags.test(5) || in_rCreateInfo.Flags.test(6) || in_rCreateInfo.Flags.test(8))
                {
                    csl::math::Matrix34 popupMtx{};
                    if (auto* pPlayerInfo = ObjUtil::GetPlayerInformation(*pEffectManager->m_pOwnerDocument, in_rCreateInfo.PlayerNo))
                        popupMtx = math::Matrix34AffineTransformation(pPlayerInfo->Position, pPlayerInfo->Rotation);

                    zelda_popupitem::ZeldaPopupItemCinfo createInfo
                    {
                        popupMtx,
                        ZeldaPopupItemType::eZeldaPopupItemType_Heart,
                        in_rCreateInfo.PlayerNo
                    };
                    zelda_popupitem::CreateZeldaPopupItem(GetAllocator(), *pEffectManager->m_pOwnerDocument, createInfo);
                }
                else
                {
                    popup_item::SParam param{};
                    param.Unk2 = 20.f;
                    param.Unk4 = 0.3f;
                    popup_item::Create(*pEffectManager->m_pOwnerDocument, param);
                }
            }

            if (!Unk2.test(0) || !in_rCreateInfo.Flags.test(1))
                return;

            for (size_t i = 0; i < in_rCreateInfo.Unk1; i++)
            {
                if (!i) continue;
            
                float scalar = (i / in_rCreateInfo.Unk1 * MATHF_PI) * 2.0f;
                csl::math::Vector3 unk1(effectMtx.GetColumn(1) + (csl::math::Vector3(effectMtx.GetColumn(0) * sinf(scalar)) * 0.01f * 10.0f));
                unk1 += ((effectMtx.GetColumn(2) * cosf(scalar) * 0.01f * 10.0f));

                AnimalManager.CreateAnimal(*pEffectManager->m_pOwnerDocument, effectMtx, unk1);
            }
        }

        static fnd::GameServiceClass& staticClass()
        {
            return *ms_pStaticClass;
        }
    };
}