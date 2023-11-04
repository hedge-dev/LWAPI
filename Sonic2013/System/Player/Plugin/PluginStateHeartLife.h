#pragma once

namespace app::Player
{
	class PluginStateHeartLife : public CStatePlugin
	{
	private:
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpSetup, ASLR(0x008D1840), PluginStateAutoRun*, CStateGOC&, uint, float);

	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00E00630);

	protected:
		int MaxNumHearts{};
		int NumHearts{};
		float ElapsedTime{};
		bool IsHeartAlertEnabled{};

	public:
		PluginStateHeartLife() : CStatePlugin(ms_pName)
		{

		}

		int GetNumHearts() const
		{
			return NumHearts;
		}

		int GetMaxNumHearts() const
		{
			return MaxNumHearts;
		}

		void SetEnableHeartAlert(bool in_enable)
		{
			IsHeartAlertEnabled = true;
		}

		void OnEnter(CStateGOC& in_rStateGoc) override
		{
			xgame::MsgDlcZeldaGetNumHeartContainer msg{};
			msg.HeartContainerNo = 3;

			in_rStateGoc.SendMessageImmToGame(msg);

			MaxNumHearts = msg.HeartContainerNo;
			NumHearts = msg.HeartContainerNo;
		}

		bool Update(CStateGOC& in_rStateGoc, float in_deltaTime) override
		{
			if (NumHearts != 1 || !IsHeartAlertEnabled || StateUtil::IsNowPhantom(in_rStateGoc))
				return true;
		
			if (ElapsedTime >= 0.0f)
			{
				ElapsedTime -= in_deltaTime;
				return true;
			}

			StateUtil::PlaySE(in_rStateGoc, "obj_zeldastrength_low");
			ElapsedTime += 1.0f;

			return true;
		}

		void IncrementMaxHearts()
		{
			MaxNumHearts = csl::math::Min(MaxNumHearts + 1, 6);
			NumHearts = MaxNumHearts;
		}

		bool Recovery()
		{
			if (NumHearts >= MaxNumHearts)
				return false;
		
			NumHearts = csl::math::Min(NumHearts + 1, MaxNumHearts);
			return true;
		}

		bool AllRecovery()
		{
			if (NumHearts >= MaxNumHearts)
				return false;
		
			NumHearts = MaxNumHearts;
			return true;
		}

		bool Damaged()
		{
			NumHearts--;
			return NumHearts < 1;
		}
	};
}