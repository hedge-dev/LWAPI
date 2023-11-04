#pragma once

namespace app::xgame
{
	class GameStatusBase : public fnd::ReferencedObject
	{
		const char* pName{};
		bool Unk1{};
	};

	class StageGameStatus : public fnd::ReferencedObject
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpResetForRestart, ASLR(0x00933B60), StageGameStatus*);
		inline static FUNCTION_PTR(GameStatusBase*, __thiscall, ms_fpGetStatus, ASLR(0x00933BF0), const StageGameStatus*, const char*);

	public:
		INSERT_PADDING(16);

		void ResetForRestart()
		{
			ms_fpResetForRestart(this);
		}

		GameStatusBase* GetStatus(const char* in_pName) const
		{
			return ms_fpGetStatus(this, in_pName);
		}

		template <typename T>
		T* GetStatus() const
		{
			return static_cast<T*>(GetStatus(T::ms_pName));
		}
	};
}