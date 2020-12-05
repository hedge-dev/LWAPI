#pragma once

namespace app::fnd
{
	class GOCVisualModel : GOComponent
	{
	public:
		class Description
		{
		public:
			inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x00495480), void* This);
			hh::gfx::ResModel* model;
			int field_04;
			int field_08;
			int field_0C;
			int field_10;
			int field_14;
			float field_18;
			int field_1C;
			int field_20;
			int field_24;
			int field_28;
			int field_2C;
			int field_30;
			int field_34;
			int field_38;
			
			Description()
			{
				ms_fpCtor(this);
			}
		};

	private:
		INSERT_PADDING(260);
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