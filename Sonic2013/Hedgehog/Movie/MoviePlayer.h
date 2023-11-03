#pragma once

namespace app::fnd
{
	class CMoviePlayer : public ReferencedObject
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpPlay, ASLR(0x0049B2A0), CMoviePlayer*, const char*, int, bool, bool, bool);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpPlay1, ASLR(0x0049AEF0), CMoviePlayer*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpPause, ASLR(0x0049AB30), CMoviePlayer*, bool);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDraw, ASLR(0x0049C030), CMoviePlayer*, bool);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDrawPrepare, ASLR(0x0049BEF0), CMoviePlayer*);

	public:
		INSERT_PADDING(496){}; // lmao

		CMoviePlayer() = delete;

		void Play()
		{
			ms_fpPlay1(this);
		}

		void Pause(bool in_pause)
		{
			ms_fpPause(this, in_pause);
		}

		void Play(const char* in_pName, int in_subTrack, bool in_play, bool in_loop, bool in_useA8R8G8B8)
		{
			ms_fpPlay(this, in_pName, in_subTrack, in_play, in_loop, in_useA8R8G8B8);
		}

		void Draw(bool in_a2)
		{
			ms_fpDraw(this, in_a2);
		}

		void DrawPrepare()
		{
			ms_fpDrawPrepare(this);
		}

		inline static CMoviePlayer* Create(const char* in_pName, int in_subTrack, bool in_play, bool in_loop, bool in_useA8R8G8B8)
		{
			auto* pPlayer = CMovieSystem::GetInstance()->CreatePlayer();
			if (pPlayer)
			{
				pPlayer->Play(in_pName, in_subTrack, in_play, in_loop, in_useA8R8G8B8);
			}

			return pPlayer;
		}
	};
}