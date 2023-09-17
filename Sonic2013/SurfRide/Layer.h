#pragma once

namespace SurfRide
{
	class Layer;
	class Transform;
	class SRS_TRS_BASE;
	class SRS_MOTION;
	class SRS_TRACK;
	class DrawInterface;
	class SRS_CELL3D;
	class TextureList;

	struct SRS_CASTNODE;

	class Cast : public Base
	{
	public:
		virtual Color GetLocalMaterialColor() const;
		virtual Color GetGlobalMaterialColor() const;
		virtual void SetLocalMaterialColor(const Color& in_rColor);
		virtual Color GetLocalIlluminationColor() const;
		virtual Color GetGlobalIlluminationColor() const;
		virtual void SetLocalIlluminationColor(const Color& in_rColor);
		virtual bool GetLocalDisplayFlag() const;
		virtual bool GetGlobalDIsplayFlag() const;
		virtual void SetLocalDisplayFlag(bool in_displayFlag);
		virtual ~Cast() = default;
		virtual void CalcMotion(float in_unk, float in_unk2, bool in_unk3, bool in_unk4, const SRS_MOTION* in_pMotion);
		virtual void MakeCellData(bool in_unk, Transform* in_pTransform, void* in_pUnk2);
		virtual void Update(float in_deltaTime, const Transform* in_pTransform, const Cast* in_pCast, Transform* in_pTransform2, void* in_pUnk);
		virtual void UpdateParentsAndThisTransformRecursively();
		virtual void UpdateParentsTransformRecursively();
		virtual void UpdateThis(float in_deltaTime, const Transform* in_pTransform, const Cast* in_pCast, Transform* in_pTransform2, void* in_pUnk);
		virtual void Draw(DrawInterface* in_pInterface, Transform* in_pTransform, void* in_pUnk);
		virtual Transform* GetTransform();
		virtual void CalcTrackTypeWidth(float in_unk, const SRS_TRACK* in_pTrack);
		virtual void CalcTrackTypeHeight(float in_unk, const SRS_TRACK* in_pTrack);
		virtual void CalcTrackTypeCropIndex0(float in_unk, const SRS_TRACK* in_pTrack);
		virtual void CalcTrackTypeCropIndex1(float in_unk, const SRS_TRACK* in_pTrack);
		virtual int GetCellCount() const;
		virtual void InitializeTransformFromLayerBuffer(Transform* in_pTransform);
		virtual void CopyTransformToLayerBuffer(Transform* in_pTransform, Transform* out_pTransform, bool in_unk);
		virtual void CopyCellToLayerBuffer(void* in_pCell, void* out_pCell, uint in_unk);
		virtual void* GetCell() const;
		virtual void EntryStateCallBack(void (*)(const SRS_CELL3D& in_rCell, TextureList** in_ppTextureList));
		virtual void DeleteStateCallBack();

		INSERT_PADDING(4);
		Transform* pTransform{};
		SRS_TRS_BASE* pBinaryTransform{};
		INSERT_PADDING(4); // ReferenceCount<Blur>;
		INSERT_PADDING(4); // ReferenceCount<Reflect>;
		INSERT_PADDING(4);
		SRS_CASTNODE* pCastNode{};
		int RefCount{};
		Layer* pParentLayer{};
		INSERT_PADDING(8);
		ReferenceCount<Cast> rcUnk1{};
		ReferenceCount<Cast> rcUnk2{};
		ReferenceCount<Cast> rcUnk3{};
		int Flags{};
		ReferenceCount<BinaryData> rcBinaryData{};
		INSERT_PADDING(1);
		bool OwnsBinaryData{};
		INSERT_PADDING(6);

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
			SrFree(this);
		}

		bool Cleanup()
		{
			if (OwnsBinaryData)
				DeleteData();
		}
	};

	struct SRS_LAYER
	{
		const char* pName{};
		int ID{};
		int Flags{};
		int CastCount{};
		SRS_CASTNODE* pCasts{};
		void* pCells{};
		int AnimationCount{};
		SRS_ANIMATION* pAnimations{};
		int CurrentAnimationIndex{};
		void* pUserData{};
	};

	class Layer : public Base
	{
	public:
		SRS_LAYER* pBinaryLayer{};
		int RefCount{};
		Scene* pOwner{};
		ReferenceCount<Cast>* prcCasts{};
		int CastCount{};
		INSERT_PADDING(12) {};
		INSERT_PADDING(4) {}; // ReferenceCount<Cast> rcCastBegin{};
		INSERT_PADDING(4) {}; // ReferenceCount<Cast> rcCastEnd{};
		int CurrentAnimationIndex{};
		float Unk8{};
		float Unk9{};
		float Unk10{};
		float AnimationFrameCount{};
		INSERT_PADDING(8) {};
		int Flags{};
		void* pBinaryData{};
		bool OwnsBinaryData{};
		bool Unk1{};
		bool Unk2{};
		bool Unk3{};
		bool Unk4{};
		bool IsAnimationEnd{};
		bool Unk6{};
		int Unk7{};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x00C639C0), Layer*, SRS_LAYER*, Scene*, void** in_pBinaryData);

	public:
		Layer(SRS_LAYER* in_pBinaryLayer, Scene* in_pScene, void** in_pBinaryData)
		{
			ms_fpCtor(this, in_pBinaryLayer, in_pScene, in_pBinaryData);
		}

		Layer()
		{

		}

		const char* GetName() const
		{
			return pBinaryLayer->pName;
		}

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

		SRS_ANIMATION* GetAnimation()
		{
			if (pBinaryLayer->pAnimations)
				pBinaryLayer->pAnimations[CurrentAnimationIndex];

			return pBinaryLayer->pAnimations;
		}

		int GetAnimationID() const
		{
			return pBinaryLayer->pAnimations[CurrentAnimationIndex].ID;
		}

		int GetAnimationID(const char* in_pAnimationName) const
		{
			if (!pBinaryLayer->AnimationCount)
				return -1;
		
			for (size_t i = 0; i < pBinaryLayer->AnimationCount; i++)
			{
				if (strcmp(pBinaryLayer->pAnimations[i].pName, in_pAnimationName) == 0)
					return pBinaryLayer->pAnimations[i].ID;
			}

			return -1;
		}

		void SetHideFlag(bool in_hide)
		{
			if (in_hide)
				Flags |= 0x100;
			else
				Flags &= ~0x100;
		}

		void SetRepeatFlag(bool in_repeat)
		{
			Unk3 = in_repeat;
			Unk4 = in_repeat;
		}

		void SetCurrentFrame(float in_frame)
		{
			Unk8 = in_frame;
			Unk9 = in_frame;
			Unk1 = true;
			IsAnimationEnd = false;
		}
	};
}