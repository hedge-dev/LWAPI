#pragma once

namespace app
{
	class SyncTimer : public fnd::ReferencedObject, csl::fnd::SingletonPointer<SyncTimer>
	{
	public:
        inline static FUNCTION_PTR(void, __thiscall, ms_fpReset, ASLR(0x004ACC70), void* This);
        inline static FUNCTION_PTR(void, __thiscall, ms_fpSetFPS, ASLR(0x004ACCD0), void* This, float fps);
        inline static FUNCTION_PTR(float, __thiscall, ms_fpCalcFPS, ASLR(0x004ACD40), void* This);
        inline static FUNCTION_PTR(void, __thiscall, ms_fpSync, ASLR(0x004ACE10), void* This);

        void Reset()
        {
            ms_fpReset(this);
        }

        void Sync()
        {
            ms_fpSync(this);
        }

        void SetFPS(float fps)
        {
            ms_fpSetFPS(this, fps);
        }

        float CalcFPS()
        {
            return ms_fpCalcFPS(this);
        }
	};
}

inline DEFINE_SINGLETONPTR(app::SyncTimer, ASLR(0x00FD7338));