#pragma once

namespace app
{
	class SyncTimer : public fnd::ReferencedObject, csl::fnd::SingletonPointer<SyncTimer>
	{
	private:
        inline static FUNCTION_PTR(void, __thiscall, ms_fpReset, ASLR(0x004ACC70), SyncTimer*);
        inline static FUNCTION_PTR(void, __thiscall, ms_fpSetFPS, ASLR(0x004ACCD0), SyncTimer*, float);
        inline static FUNCTION_PTR(float, __thiscall, ms_fpCalcFPS, ASLR(0x004ACD40), SyncTimer*);
        inline static FUNCTION_PTR(void, __thiscall, ms_fpSync, ASLR(0x004ACE10), SyncTimer*);

    public:
        void Reset()
        {
            ms_fpReset(this);
        }

        void Sync()
        {
            ms_fpSync(this);
        }

        void SetFPS(float in_fps)
        {
            ms_fpSetFPS(this, in_fps);
        }

        float CalcFPS()
        {
            return ms_fpCalcFPS(this);
        }
	};
}

inline DEFINE_SINGLETONPTR(app::SyncTimer, ASLR(0x00FD7338));