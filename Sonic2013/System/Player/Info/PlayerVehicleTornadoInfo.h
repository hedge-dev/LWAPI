#pragma once

namespace app::Player
{
    class VehicleTornadoInfo : public CObjInfo
    {
    private:
        inline static const char* ms_pPackfileName = "Tornado.pac";
        inline static const char* ms_pModelName = "w2_obj_tornado";
        inline static const char* ms_pShadowModelName = "w2_obj_tornado";
        inline static const char* ms_pSkeletonName = "w2_obj_tornado";
        inline static const char* ms_pAnimationScriptName = "tornado";

    public:
        hh::gfx::res::ResModel Model{};
        hh::gfx::res::ResSkeleton Skeleton{};
        animation::AnimationResContainer AnimationContainer{ *m_pAllocator };
        res::ResShadowModel ShadowModel{};

        VehicleTornadoInfo() {}

    protected:
        void Load(CObjInfoFileLoader& in_rLoader) override
        {
            in_rLoader.Load(ms_pPackfileName, 0x4001);
        }

        void Initialize(GameDocument& in_rDocument) override
        {
            auto packFile = ObjUtil::GetPackFile(ms_pPackfileName);

            Model = ObjUtil::GetModelResource(ms_pModelName, packFile);
            Skeleton = ObjUtil::GetSkeletonResource(ms_pSkeletonName, packFile);

            auto animScript = ObjUtil::GetAnimationScriptResource(ms_pAnimationScriptName, packFile);
            animation::AnimationResContainer::LoadInfo animLoadInfo{ animScript, Skeleton, nullptr };
            AnimationContainer.LoadFromBuffer(animLoadInfo, packFile);

            ShadowModel = ObjUtil::GetShadowModel(ms_pShadowModelName, packFile);
        }

        const char* GetInfoName() override
        {
            return "VehicleTornadoInfo";
        }
    };
}