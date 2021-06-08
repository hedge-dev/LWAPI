#pragma once

namespace app
{
	class GOCEnemyTarget : fnd::GOComponent
	{
	public:
		class Description
		{
		public:
			bool enabled;
		};
		
		inline static fnd::GOComponentClass* ms_pGOCEnemyTargetStaticClass = reinterpret_cast<fnd::GOComponentClass*>(ASLR(0x00FE7608));
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetup, ASLR(0x00726510), GOCEnemyTarget* This, Description& description);
		
		static fnd::GOComponentClass* staticClass()
		{
			return ms_pGOCEnemyTargetStaticClass;
		}

		void Setup(Description& description)
		{
			ms_fpSetup(this, description);
		}
	};
}