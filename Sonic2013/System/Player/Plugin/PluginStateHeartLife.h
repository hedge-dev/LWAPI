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
		int m_MaxNumHearts{};
		int m_NumHearts{};
		float m_ElapsedTime{};
		bool m_IsHeartAlertEnabled{};

	public:
		PluginStateHeartLife() : CStatePlugin(ms_pName)
		{

		}

		int GetNumHearts() const
		{
			return m_NumHearts;
		}

		int GetMaxNumHearts() const
		{
			return m_MaxNumHearts;
		}

		void SetEnableHeartAlert(bool in_enable)
		{
			m_IsHeartAlertEnabled = true;
		}

		void OnEnter(CStateGOC& in_rStateGoc) override
		{
			xgame::MsgDlcZeldaGetNumHeartContainer msg{};
			msg.HeartContainerNo = 3;

			in_rStateGoc.SendMessageImmToGame(msg);

			m_MaxNumHearts = msg.HeartContainerNo;
			m_NumHearts = msg.HeartContainerNo;
		}

		bool Update(CStateGOC& in_rStateGoc, float in_deltaTime) override
		{
			if (m_NumHearts != 1 || !m_IsHeartAlertEnabled || StateUtil::IsNowPhantom(in_rStateGoc))
				return true;
		
			if (m_ElapsedTime >= 0.0f)
			{
				m_ElapsedTime -= in_deltaTime;
				return true;
			}

			StateUtil::PlaySE(in_rStateGoc, "obj_zeldastrength_low");
			m_ElapsedTime += 1.0f;

			return true;
		}

		void IncrementMaxHearts()
		{
			m_MaxNumHearts = csl::math::Min(m_MaxNumHearts + 1, 6);
			m_NumHearts = m_MaxNumHearts;
		}

		bool Recovery()
		{
			if (m_NumHearts >= m_MaxNumHearts)
				return false;
		
			m_NumHearts = csl::math::Min(m_NumHearts + 1, m_MaxNumHearts);
			return true;
		}

		bool AllRecovery()
		{
			if (m_NumHearts >= m_MaxNumHearts)
				return false;
		
			m_NumHearts = m_MaxNumHearts;
			return true;
		}

		bool Damaged()
		{
			m_NumHearts--;
			return m_NumHearts < 1;
		}
	};
}