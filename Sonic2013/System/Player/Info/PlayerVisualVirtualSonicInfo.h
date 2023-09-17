#pragma once

namespace app::Player
{
    class VirtualSonicInfo : public CObjInfo
    {
    private:
        inline static const char* ms_pPackfileNames[] = { "Virtualsonic1p.pac", "Virtualsonic2p.pac" };
        inline static const char* ms_pModelNames[] = { "chr_virtualsonic_1p", "chr_virtualsonic_2p" };
        inline static const char* ms_pSpinModelNames[] = { "chr_sonic_spin_1p", "chr_sonic_spin_2p" };
        inline static const char* ms_pAntennaModelNames[] = { "chr_virtualsonic_antenna", "chr_virtualsonic_antenna" };

    public:
        inline static const size_t ms_ModelCount = ARRAYSIZE(ms_pModelNames);
        inline static const size_t ms_SpinModelCount = ARRAYSIZE(ms_pSpinModelNames);
        inline static const size_t ms_AntennaModelCount = ARRAYSIZE(ms_pAntennaModelNames);

        csl::ut::FixedArray<hh::gfx::res::ResModel, ms_ModelCount> Models{};
        csl::ut::FixedArray<hh::gfx::res::ResModel, ms_SpinModelCount> SpinModels{};
        csl::ut::FixedArray<hh::gfx::res::ResModel, ms_AntennaModelCount> AntennaModels{};

        VirtualSonicInfo() {}

    protected:
        void Load(CObjInfoFileLoader& in_rLoader) override
        {
            in_rLoader.Load(ms_pPackfileNames[0], 0x4001);
            in_rLoader.Load(ms_pPackfileNames[1], 0x4001);
        }

        void Initialize(GameDocument& in_rDocument) override
        {
            auto packFileP1 = ObjUtil::GetPackFile(ms_pPackfileNames[0]);
            auto packFileP2 = ObjUtil::GetPackFile(ms_pPackfileNames[1]);

            Models[0] = ObjUtil::GetModelResource(ms_pModelNames[0], packFileP1);
            Models[1] = ObjUtil::GetModelResource(ms_pModelNames[1], packFileP2);

            SpinModels[0] = ObjUtil::GetModelResource(ms_pSpinModelNames[0], packFileP1);
            SpinModels[1] = ObjUtil::GetModelResource(ms_pSpinModelNames[1], packFileP2);

            AntennaModels[0] = ObjUtil::GetModelResource(ms_pAntennaModelNames[0], packFileP1);
            AntennaModels[1] = ObjUtil::GetModelResource(ms_pAntennaModelNames[1], packFileP2);
        }

        const char* GetInfoName() override
        {
            return "VirtualSonicInfo";
        }
    };
}