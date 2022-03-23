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

	class GOCVisualModel : public GOCVisualTransformed
	{
	public:
		typedef uint NodeSpace;

		class Description
		{
		public:
			hh::gfx::res::ResModel m_Model{};
			hh::gfx::res::ResSkeleton m_Skeleton{};
			int field_08{}; // some kind of flags
			void* field_0C{};
			int field_10{}; // light quality type?
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

	private:
		INSERT_PADDING(128);
		
	public:
		inline static GOComponentClass* ms_pGOCVisualModelStaticClass = reinterpret_cast<GOComponentClass*>(ASLR(0x0FD4238));
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpSetup, ASLR(0x00495850), void* This, const Description&);
		inline static FUNCTION_PTR(TexSrtBlenderHH*, __thiscall, ms_fpSetTexSrtBlender, ASLR(0x00495930), void*, const TexSrtBlenderDesc&);
		inline static FUNCTION_PTR(MatAnimBlenderHH*, __thiscall, ms_fpSetMatAnimBlender, ASLR(0x00495A70), void*, const MatAnimBlenderDesc&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetMaterialAnimation, ASLR(0x004959D0), void*, const MatAnimDesc&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetTexSrtAnimation, ASLR(0x00495890), void*, const TexSrtDesc&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAttachAnimation, ASLR(0x004951B0), void*, game::GOCAnimationSingle*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpGetNodeTransform, ASLR(0x004951F0), const void*, NodeSpace, const char*, csl::math::Transform*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetNodeTransform, ASLR(0x00495240), void*, NodeSpace, const char*, const csl::math::Transform&);

		static GOComponentClass* staticClass()
		{
			return ms_pGOCVisualModelStaticClass;
		}

		bool Setup(const Description& description)
		{
			return ms_fpSetup(this, description);
		}

		TexSrtBlenderHH* SetTexSrtBlender(const TexSrtBlenderDesc& description)
		{
			return ms_fpSetTexSrtBlender(this, description);
		}

		MatAnimBlenderHH* SetMatAnimBlender(const MatAnimBlenderDesc& description)
		{
			return ms_fpSetMatAnimBlender(this, description);
		}

		void SetMaterialAnimation(const MatAnimDesc& description)
		{
			ms_fpSetMaterialAnimation(this, description);
		}

		void SetTexSrtAnimation(const TexSrtDesc& description)
		{
			ms_fpSetTexSrtAnimation(this, description);
		}

		void AttachAnimation(game::GOCAnimationSingle* pAnimation)
		{
			ms_fpAttachAnimation(this, pAnimation);
		}

		void GetNodeTransform(NodeSpace nodeSpace, const char* pNodeName, csl::math::Transform* pTransform) const
		{
			ms_fpGetNodeTransform(this, nodeSpace, pNodeName, pTransform);
		}

		void SetNodeTransform(NodeSpace nodeSpace, const char* pNodeName, const csl::math::Transform& rTransform)
		{
			ms_fpSetNodeTransform(this, nodeSpace, pNodeName, rTransform);
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

	class TexSrtBlenderHH
	{
		class TexSrtControlHH;
		typedef TexSrtDesc TexSrtControlDesc;

	public:
		inline static FUNCTION_PTR(TexSrtControlHH*, __thiscall, ms_fpCreateControl, ASLR(0x00496B40), void* This, const TexSrtControlDesc& description);

		TexSrtControlHH* CreateControl(const TexSrtControlDesc& description)
		{
			return ms_fpCreateControl(this, description);
		}
	};

	class MatAnimBlenderHH
	{
		class MatAnimControlHH;
		typedef MatAnimDesc MatAnimControlDesc;

	public:
		inline static FUNCTION_PTR(MatAnimControlHH*, __thiscall, ms_fpCreateControl, ASLR(0x004965A0), void* This, const MatAnimControlDesc& description);

		MatAnimControlHH* CreateControl(const MatAnimControlDesc& description)
		{
			return ms_fpCreateControl(this, description);
		}
	};
}