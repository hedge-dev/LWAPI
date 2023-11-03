#pragma once

namespace app::game
{
	class GOCAnimationSingle;
}

namespace app::fnd
{
	struct MatAnimBlenderDesc;
	struct TexSrtBlenderDesc;
	struct MorphTargetDesc;
	struct MatAnimDesc;
	struct TexSrtDesc;
	class MatAnimBlenderHH;
	class TexSrtBlenderHH;
	class TexSrtControlHH;
	class TexSrtControl;

	class GOCVisualModel : public GOCVisualTransformed
	{
	public:
		enum class LightQualityType : signed char
		{
			eLightQualityType_Value0,
			eLightQualityType_Value1,
			eLightQualityType_Value2,
			eLightQualityType_Max
		};

		typedef uint NodeSpace;

		class Description
		{
		public:
			hh::gfx::res::ResModel Model{};
			hh::gfx::res::ResSkeleton Skeleton{};
			int Unk1{}; // some kind of flags
			uint Unk2{};
			csl::ut::Enum<LightQualityType, signed char> LightQualityType{ LightQualityType::eLightQualityType_Max };
			HFrame* pParent{}; // parent?
			float ZOffset{};
			void* pUnk3{}; // GI texture?
			int Unk4{};
			int Unk5{};
			uint Unk6{(uint)-1};
			int Unk7{};
			int Unk8{};
			int Unk9{};
			int Unk10{};
		};
		
	private:
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpSetup, ASLR(0x00495850), GOCVisualModel*, const Description&);
		inline static FUNCTION_PTR(TexSrtBlenderHH*, __thiscall, ms_fpSetTexSrtBlender, ASLR(0x00495930), GOCVisualModel*, const TexSrtBlenderDesc&);
		inline static FUNCTION_PTR(MatAnimBlenderHH*, __thiscall, ms_fpSetMatAnimBlender, ASLR(0x00495A70), GOCVisualModel*, const MatAnimBlenderDesc&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetMaterialColor, ASLR(0x00495140), GOCVisualModel*, const float*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetMaterialAnimation, ASLR(0x004959D0), GOCVisualModel*, const MatAnimDesc&);
		inline static FUNCTION_PTR(TexSrtControl*, __thiscall, ms_fpSetTexSrtAnimation, ASLR(0x00495890), GOCVisualModel*, const TexSrtDesc&);
		inline static FUNCTION_PTR(TexSrtControl*, __thiscall, ms_fpGetTexSrtControl, ASLR(0x004954C0), const GOCVisualModel*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAttachAnimation, ASLR(0x004951B0), GOCVisualModel*, game::GOCAnimationSingle*);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetNodeTransform, ASLR(0x004951F0), const GOCVisualModel*, NodeSpace, const char*, app::math::Transform*);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetNodeTransformByIndex, ASLR(0x004951D0), const GOCVisualModel*, NodeSpace, int, app::math::Transform*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetNodeTransform, ASLR(0x00495240), GOCVisualModel*, NodeSpace, const char*, const app::math::Transform&);
		inline static FUNCTION_PTR(hh::gfx::res::ResSkeleton, __thiscall, ms_fpGetSkeletonResource, ASLR(0x004952A0), GOCVisualModel*, hh::gfx::res::ResSkeleton);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCopyPose, ASLR(0x004952C0), GOCVisualModel*, const GOCVisualModel&);
		inline static GOComponentClass* ms_pGOCVisualModelStaticClass = reinterpret_cast<GOComponentClass*>(ASLR(0x0FD4238));

	public:
		INSERT_PADDING(32) {};
		GOCVisualModelImpl Impl{ GetAllocator() };

		static GOComponentClass* staticClass()
		{
			return ms_pGOCVisualModelStaticClass;
		}

		void GetMatrix(csl::math::Matrix34* out_pMatrix)
		{
			Impl.GetMatrix(out_pMatrix);
		}

		const csl::math::Aabb& GetBounds() 
		{
			return Impl.GetBounds();
		}

		void SetBounds(const csl::math::Aabb& in_rBounds)
		{
			Impl.SetBounds(in_rBounds);
		}

		void ChangeModel(const Description& in_rDescription) 
		{
			Impl.ChangeModel(*this, reinterpret_cast<const GOCVisualModelImpl::Description&>(in_rDescription));
		}

		bool Setup(const Description& in_rDescription)
		{
			return ms_fpSetup(this, in_rDescription);
		}

		void SetPoseUpdateFlag(bool in_update)
		{
			Impl.SetPoseUpdateFlag(*this, in_update);
		}

		TexSrtBlenderHH* SetTexSrtBlender(const TexSrtBlenderDesc& in_rDescription)
		{
			return ms_fpSetTexSrtBlender(this, in_rDescription);
		}

		MatAnimBlenderHH* SetMatAnimBlender(const MatAnimBlenderDesc& in_rDescription)
		{
			return ms_fpSetMatAnimBlender(this, in_rDescription);
		}

		void SetMaterialColor(const float* in_pColor)
		{
			ms_fpSetMaterialColor(this, in_pColor);
		}

		void SetMaterialAnimation(const MatAnimDesc& in_rDescription)
		{
			ms_fpSetMaterialAnimation(this, in_rDescription);
		}

		TexSrtControl* SetTexSrtAnimation(const TexSrtDesc& in_rDescription)
		{
			return ms_fpSetTexSrtAnimation(this, in_rDescription);
		}

		TexSrtControl* GetTexSrtControl() const
		{
			return ms_fpGetTexSrtControl(this);
		}

		void AttachAnimation(game::GOCAnimationSingle* in_pAnimation)
		{
			Impl.AttachAnimation(this, in_pAnimation);
		}

		void DetachAnimation(game::GOCAnimationSingle* in_pAnimation)
		{
			Impl.DetachAnimation(in_pAnimation);
		}

		void DetachAnimation()
		{
			Impl.DetachAnimation();
		}

		hh::gfx::AnimMorphTargetControl* SetMorphAnimation(const MorphTargetDesc& in_rDescription);

		bool GetNodeTransform(NodeSpace in_nodeSpace, const char* in_pNodeName, app::math::Transform* out_pTransform) const
		{
			return ms_fpGetNodeTransform(this, in_nodeSpace, in_pNodeName, out_pTransform);
		}

		bool GetNodeTransform(NodeSpace in_nodeSpace, int in_nodeIndex, app::math::Transform* out_pTransform) const
		{
			return ms_fpGetNodeTransformByIndex(this, in_nodeSpace, in_nodeIndex, out_pTransform);
		}

		void SetNodeTransform(NodeSpace in_nodeSpace, const char* in_pNodeName, const app::math::Transform& in_transform)
		{
			ms_fpSetNodeTransform(this, in_nodeSpace, in_pNodeName, in_transform);
		}

		hh::gfx::res::ResModel GetModelResource()
		{
			return Impl.GetModelResource();
		}

		hh::gfx::res::ResSkeleton GetSkeletonResource()
		{
			return Impl.GetSkeletonResource();
		}

		void CopyPose(const GOCVisualModel& in_rOther)
		{
			return ms_fpCopyPose(this, in_rOther);
		}
	};

	struct MatAnimBlenderDesc
	{
		size_t Count;
	};

	struct MatAnimDesc
	{
		hh::gfx::res::ResAnimMaterial Animation{};
		size_t Unk;
	};

	struct TexSrtBlenderDesc
	{
		size_t Count;
	};

	struct TexSrtDesc
	{
		hh::gfx::res::ResAnimTexSrt Animation{};
		size_t Unk;
	};

	// This is made up, the API doesn't exist in the game
	struct MorphTargetDesc
	{
		hh::gfx::res::ResAnimMorphTarget Animation{};
	};

	class TexSrtControl
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetSpeed, ASLR(0x00496D40), TexSrtControl*, float);

	public:
		void SetSpeed(float in_speed)
		{
			ms_fpSetSpeed(this, in_speed);
		}
	};

	class TexSrtBlenderHH
	{
		typedef TexSrtDesc TexSrtControlDesc;

	private:
		inline static FUNCTION_PTR(TexSrtControlHH*, __thiscall, ms_fpCreateControl, ASLR(0x00496B40), void*, const TexSrtControlDesc&);

	public:
		TexSrtControlHH* CreateControl(const TexSrtControlDesc& in_description)
		{
			return ms_fpCreateControl(this, in_description);
		}
	};

	class MatAnimBlenderHH
	{
		class MatAnimControlHH;
		typedef MatAnimDesc MatAnimControlDesc;

	private:
		inline static FUNCTION_PTR(MatAnimControlHH*, __thiscall, ms_fpCreateControl, ASLR(0x004965A0), void*, const MatAnimControlDesc&);

	public:
		MatAnimControlHH* CreateControl(const MatAnimControlDesc& in_description)
		{
			return ms_fpCreateControl(this, in_description);
		}
	};
}