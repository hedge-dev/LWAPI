#pragma once
#pragma warning(disable:4996)

namespace app
{
    class RcInfoBase : public CObjInfo
    {
    private:
        inline static const char* ms_pCommonPacfileName = "RcCommon.pac";
        inline static const char* ms_pSoundSheetName = "sound/se_radio_control.acb";
        inline static const char* ms_pModelName = "chr_pha_Asteroid";
        inline static const char* ms_pSkeletonName = "chr_pha_Asteroid";
        inline static const char* ms_pAnimationScriptName = "phantom_asteroid";
        inline static const char* ms_pVariantIds = "12345";

    public:
        byte Variant{};
        csl::ut::FixedString<32> PacfileName{};
        csl::ut::FixedString<32> VariantPacfileName{};

        RcInfoBase(byte in_variant, const char* in_pPacfileName) : CObjInfo(), Variant(in_variant), PacfileName(in_pPacfileName)
        {
            char pExtensionlessName[64]{};
            strncpy(pExtensionlessName, in_pPacfileName, strlen(in_pPacfileName) - 4);

            char pVariantId[4]{};
            strncpy(pVariantId, "1", 2);

            if (Variant <= 4)
                *pVariantId = ms_pVariantIds[Variant];

            char buffer[64]{};
            csl::fnd::Snprintf(buffer, sizeof(buffer), "%s%s.pac", pExtensionlessName, pVariantId);

            VariantPacfileName = buffer;
        }

    protected:
        void Load(CObjInfoFileLoader& in_rLoader) override
        {
            in_rLoader.Load(ms_pCommonPacfileName, -1);
            in_rLoader.Load(PacfileName.c_str(), -1);
            in_rLoader.Load(VariantPacfileName, -1);
            in_rLoader.Load(ms_pSoundSheetName, -1);
        }

    public:
        const char* GetInfoName() override
        {
            return "RcInfoBase";
        }
    };
}