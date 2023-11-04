#pragma once

namespace app::xgame
{
	class GameScoreManager : public fnd::GameService
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetTotalScore, ASLR(0x00955CF0), GameScoreManager*, int);
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEFED0));

	public:
		INSERT_PADDING(40);

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