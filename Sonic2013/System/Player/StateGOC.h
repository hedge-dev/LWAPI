#pragma once

namespace app::Player
{
	class CStateGOC : public CGOComponent
	{
		inline static const char* ms_pStaticId = (char*)ASLR(0x00DF77D8);

	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpChangeState, ASLR(0x0085B400), CStateGOC*, int);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpChangeStateAlways, ASLR(0x0085B450), CStateGOC*, int);
		
		void* m_Unk1{};
		void* m_Unk2{};
		INSERT_PADDING(40) {}; // HsmImpl
		INSERT_PADDING(12) {}; // Effect Handle
		app::fnd::SoundHandle m_SoundHandle{};
		CPlayer* m_pPlayer{};
		INSERT_PADDING(96) {}; // A lot of stuff

		void ChangeState(int state)
		{
			ms_fpChangeState(this, state);
		}

		void ChangeStateAlways(int state)
		{
			ms_fpChangeStateAlways(this, state);
		}

		void ChangeAnimation(const char* pAnim)
		{
			m_pPlayer->GetVisualGOC()->ChangeAnimation(pAnim);
		}

		void ChangeVisual(BodyMode mode)
		{
			m_pPlayer->GetVisualGOC()->ChangeVisual(mode);
		}
		
		static const char* staticID()
		{
			return ms_pStaticId;
		}
	};
}