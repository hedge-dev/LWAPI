#pragma once

namespace app::game
{
	class GOCAnimationSingle;
}

namespace app::fnd
{
	struct MatAnimBlenderDesc;
	struct TexSrtBlenderDesc;
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
			LightQualityType_VALUE0,
			LightQualityType_VALUE1,
			LightQualityType_VALUE2,
			LightQualityType_MAX
		};

		typedef uint NodeSpace;

		class Description
		{
		public:
			hh::gfx::res::ResModel m_Model{};
			hh::gfx::res::ResSkeleton m_Skeleton{};
			int field_08{}; // some kind of flags
			uint field_0C{};
			csl::ut::Enum<LightQualityType, signed char> m_LightQualityType{ LightQualityType::LightQualityType_MAX };
			HFrame* m_pParent{}; // parent?
			float zOffset{};
			void* field_1C{}; // GI texture?
			int field_20{};
			int field_24{};
			uint field_28{(uint)-1};
			int field_2C{};
			int field_30{};
			int field_34{};
			int field_38{};
		};

		INSERT_PADDING(32) {};
		GOCVisualModelImpl m_Impl{ GetAllocator() };
		
	public:
		inline static GOComponentClass* ms_pGOCVisualModelStaticClass = reinterpret_cast<GOComponentClass*>(ASLR(0x0FD4238));
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpSetup, ASLR(0x00495850), void* This, const Description&);
		inline static FUNCTION_PTR(TexSrtBlenderHH*, __thiscall, ms_fpSetTexSrtBlender, ASLR(0x00495930), void*, const TexSrtBlenderDesc&);
		inline static FUNCTION_PTR(MatAnimBlenderHH*, __thiscall, ms_fpSetMatAnimBlender, ASLR(0x00495A70), void*, const MatAnimBlenderDesc&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetMaterialColor, ASLR(0x00495140), void*, const float*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetMaterialAnimation, ASLR(0x004959D0), void*, const MatAnimDesc&);
		inline static FUNCTION_PTR(TexSrtControl*, __thiscall, ms_fpSetTexSrtAnimation, ASLR(0x00495890), void*, const TexSrtDesc&);
		inline static FUNCTION_PTR(TexSrtControl*, __thiscall, ms_fpGetTexSrtControl, ASLR(0x004954C0), const GOCVisualModel*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAttachAnimation, ASLR(0x004951B0), void*, game::GOCAnimationSingle*);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetNodeTransform, ASLR(0x004951F0), const void*, NodeSpace, const char*, app::math::Transform*);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetNodeTransformByIndex, ASLR(0x004951D0), const void*, NodeSpace, int, app::math::Transform*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetNodeTransform, ASLR(0x00495240), void*, NodeSpace, const char*, const app::math::Transform&);
		inline static FUNCTION_PTR(hh::gfx::res::ResSkeleton, __thiscall, ms_fpGetSkeletonResource, ASLR(0x004952A0), GOCVisualModel*, hh::gfx::res::ResSkeleton);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCopyPose, ASLR(0x004952C0), GOCVisualModel*, const GOCVisualModel&);

		static GOComponentClass* staticClass()
		{
			return ms_pGOCVisualModelStaticClass;
		}

		void GetMatrix(csl::math::Matrix34* out_matrix)
		{
			m_Impl.GetMatrix(out_matrix);
		}

		const csl::math::Aabb& GetBounds() 
		{
			return m_Impl.GetBounds();
		}

		void SetBounds(const csl::math::Aabb& in_bounds)
		{
			m_Impl.SetBounds(in_bounds);
		}

		void ChangeModel(const Description& in_description) 
		{
			m_Impl.ChangeModel(*this, reinterpret_cast<const GOCVisualModelImpl::Description&>(in_description));
		}

		bool Setup(const Description& in_description)
		{
			return ms_fpSetup(this, in_description);
		}

		TexSrtBlenderHH* SetTexSrtBlender(const TexSrtBlenderDesc& in_description)
		{
			return ms_fpSetTexSrtBlender(this, in_description);
		}

		MatAnimBlenderHH* SetMatAnimBlender(const MatAnimBlenderDesc& in_description)
		{
			return ms_fpSetMatAnimBlender(this, in_description);
		}

		void SetMaterialColor(const float* in_pColor)
		{
			ms_fpSetMaterialColor(this, in_pColor);
		}

		void SetMaterialAnimation(const MatAnimDesc& in_description)
		{
			ms_fpSetMaterialAnimation(this, in_description);
		}

		TexSrtControl* SetTexSrtAnimation(const TexSrtDesc& in_description)
		{
			return ms_fpSetTexSrtAnimation(this, in_description);
		}

		TexSrtControl* GetTexSrtControl() const
		{
			return ms_fpGetTexSrtControl(this);
		}

		void AttachAnimation(game::GOCAnimationSingle* in_pAnimation)
		{
			ms_fpAttachAnimation(this, in_pAnimation);
		}

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
			return m_Impl.GetModelResource();
		}

		hh::gfx::res::ResSkeleton GetSkeletonResource()
		{
			return m_Impl.GetSkeletonResource();
		}

		void CopyPose(const GOCVisualModel& in_rOther)
		{
			return ms_fpCopyPose(this, in_rOther);
		}
	};

	struct MatAnimBlenderDesc
	{
		size_t m_Count;
	};

	struct MatAnimDesc
	{
		hh::gfx::res::ResAnimMaterial m_Animation{};
		size_t m_Unk;
	};

	struct TexSrtBlenderDesc
	{
		size_t m_Count;
	};

	struct TexSrtDesc
	{
		hh::gfx::res::ResAnimTexSrt m_Animation{};
		size_t m_Unk;
	};

	class TexSrtControl
	{
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetSpeed, ASLR(0x00496D40), TexSrtControl*, float);

		void SetSpeed(float in_speed)
		{
			ms_fpSetSpeed(this, in_speed);
		}
	};

	class TexSrtBlenderHH
	{
		typedef TexSrtDesc TexSrtControlDesc;

	public:
		inline static FUNCTION_PTR(TexSrtControlHH*, __thiscall, ms_fpCreateControl, ASLR(0x00496B40), void* This, const TexSrtControlDesc& description);

		TexSrtControlHH* CreateControl(const TexSrtControlDesc& in_description)
		{
			return ms_fpCreateControl(this, in_description);
		}
	};

	class MatAnimBlenderHH
	{
		class MatAnimControlHH;
		typedef MatAnimDesc MatAnimControlDesc;

	public:
		inline static FUNCTION_PTR(MatAnimControlHH*, __thiscall, ms_fpCreateControl, ASLR(0x004965A0), void* This, const MatAnimControlDesc& description);

		MatAnimControlHH* CreateControl(const MatAnimControlDesc& in_description)
		{
			return ms_fpCreateControl(this, in_description);
		}
	};
}