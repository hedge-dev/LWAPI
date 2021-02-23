#pragma once

namespace app::fnd
{
	class GOCVisualModel : public GOCVisualTransformed
	{
	public:
		class Description
		{
		public:
			hh::gfx::ResModel* model;
			void* skeleton{};
			int field_08{}; // some kind of flags
			void* field_0C{};
			int field_10{}; // light quality type?
			void* hFrame{}; // parent?
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
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpSetup, ASLR(0x00495850), void* This, Description& description);
		
		static GOComponentClass* staticClass()
		{
			return ms_pGOCVisualModelStaticClass;
		}

		bool Setup(Description& description)
		{
			return ms_fpSetup(this, description);
		}
	};
}