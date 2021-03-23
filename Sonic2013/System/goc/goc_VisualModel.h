#pragma once

namespace app::game
{
	class GOCAnimationSingle;
}

namespace app::fnd
{
	class GOCVisualModel : public GOCVisualTransformed
	{
	public:
		class Description
		{
		public:
			hh::gfx::res::ResModel* m_pModel;
			hh::gfx::res::ResSkeleton* m_pSkeleton{};
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
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpSetup, ASLR(0x00495850), void* This, const Description& description);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAttachAnimation, ASLR(0x004951B0), GOCVisualModel*, game::GOCAnimationSingle*);
		
		static GOComponentClass* staticClass()
		{
			return ms_pGOCVisualModelStaticClass;
		}

		bool Setup(const Description& description)
		{
			return ms_fpSetup(this, description);
		}

		void AttachAnimation(game::GOCAnimationSingle* pAnimation)
		{
			ms_fpAttachAnimation(this, pAnimation);
		}
	};
}