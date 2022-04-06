#pragma once

namespace app::fnd
{
	class CMoviePlayer;
	class CMovieSystem : public ReferencedObject, public csl::fnd::SingletonPointer<CMovieSystem>
	{
	public:
		csl::ut::MoveArray<CMoviePlayer*> m_Players{ GetAllocator() };
		csl::fnd::IAllocator* m_pPlayerAllocator{ GetAllocator() };
		float m_MainVolume{ 1 };
		csl::ut::FixedString<256> m_Root{};

		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x0049C530), CMovieSystem*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetSystemPause, ASLR(0x0049C500), CMovieSystem*, bool);
		inline static FUNCTION_PTR(CMoviePlayer*, __thiscall, ms_fpCreatePlayer, ASLR(0x0049C770), CMovieSystem*);

		void Update()
		{
			ms_fpUpdate(this);
		}

		void SetSystemPause(bool in_pause)
		{
			ms_fpSetSystemPause(this, in_pause);
		}

		CMoviePlayer* CreatePlayer()
		{
			return ms_fpCreatePlayer(this);
		}
	};
}

DEFINE_SINGLETONPTR(app::fnd::CMovieSystem, ASLR(0x00FD3CB4));