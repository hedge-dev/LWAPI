#pragma once

namespace app::xgame
{
	class GameScoreManager : public fnd::GameService
	{
	public:
		INSERT_PADDING(40);
	
	private:
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEFED0));
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetTotalScore, ASLR(0x00955CF0), GameScoreManager*, int);

	public:
		void SetTotalScore(int in_score)
		{
			ms_fpSetTotalScore(this, in_score);
		}

		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}
	};
}