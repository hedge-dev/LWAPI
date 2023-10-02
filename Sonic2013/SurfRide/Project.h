#pragma once

namespace SurfRide
{
    struct SRS_SCENE;
    class Scene;

    struct SRS_PROJECT
    {
        const char* pName{};
        short SceneCount{};
        INSERT_PADDING(2) {};
        short TextureListCount{};
        short FontCount{};
        SRS_SCENE* pScenes{};
        void* pTextureLists{}; // SRS_TEXTURELIST
        void* pFonts{}; // SRS_FONT
        SRS_CAMERA Camera{};
        int StartFrame{};
        int EndFrame{};
        float FrameRate{};
        void* pUserData{};
    };

    class Project : public Base
    {
    public:
        Camera Camera{};
        SRS_PROJECT* pBinaryProject{};
        int RefCount{};
        void* pTextureLists{};
        ReferenceCount<Scene>* prcScenes{};
        int SceneCount{};
        ReferenceCount<BinaryData> rcBinaryData{};
        bool OwnsBinaryData{};

        void IncrementReferenceCount()
        {
            RefCount++;
        }

        void DecrementReferenceCount()
        {
            RefCount--;
        }

        int GetReferenceCount()
        {
            return RefCount;
        }

        void DeleteData()
        {

        }

        void Cleanup()
        {
            if (OwnsBinaryData)
                DeleteData();
        }

        const char* GetName() const
        {
            return pBinaryProject->pName;
        }

        const SurfRide::ReferenceCount<Scene> GetScene(const char* in_pSceneName) const;
    };
}