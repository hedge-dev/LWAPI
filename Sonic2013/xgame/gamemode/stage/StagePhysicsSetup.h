#pragma once

namespace app::xgame
{
	class StagePhysicsSetup
	{
	private:
		inline static FUNCTION_PTR(void, __cdecl, ms_fpSetupWorld, ASLR(0x00933D60), GameDocument*);

	public:
		static void SetupWorld(GameDocument* in_pDocument)
		{
			ms_fpSetupWorld(in_pDocument);
		}
	};
}