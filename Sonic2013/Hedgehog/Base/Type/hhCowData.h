#pragma once

// From https://github.com/blueskythlikesclouds/BlueBlur
namespace hh::base
{
    template<typename T>
    class CCowData
    {
        inline static const T* ms_memStatic = reinterpret_cast<const T*>(ASLR(0x00EB29B4));

    protected:
        class CData
        {
        public:
            size_t RefCountAndLength;
            T Data[1];
        };

        const T* m_ptr;

        bool IsMemStatic() const
        {
            return !m_ptr || m_ptr == ms_memStatic;
        }

        CData* GetData() const
        {
            return (CData*)((char*)m_ptr - offsetof(CData, Data));
        }

        void SetData(CData* in_pData)
        {
            m_ptr = (const T*)((char*)in_pData + offsetof(CData, Data));
        }

    public:
        const T* Get() const
        {
            return IsMemStatic() ? ms_memStatic : m_ptr;
        }

        void Unset()
        {
            if (!IsMemStatic() && (uint16_t)InterlockedDecrement(&GetData()->RefCountAndLength) == 0)
                __HH_FREE(GetData());

            m_ptr = ms_memStatic;
        }

        void Set(const CCowData& in_rOther)
        {
            m_ptr = in_rOther.m_ptr;

            if (!IsMemStatic())
                InterlockedIncrement(&GetData()->RefCountAndLength);
        }

        void Set(const T* in_pPtr, const size_t in_length)
        {
            Unset();

            if (!in_length)
                return;

            const size_t memSize = offsetof(CData, Data) + in_length * sizeof(T);
            const size_t memSizeAligned = (memSize + 0x10) & 0xFFFFFFF0;

            CData* pData = (CData*)__HH_ALLOC(memSizeAligned);
            pData->RefCountAndLength = (in_length << 16) | 1;

            if (in_pPtr)
            {
                memcpy(pData->Data, in_pPtr, in_length * sizeof(T));
                memset(&pData->Data[in_length], 0, memSizeAligned - memSize);
            }

            SetData(pData);
        }

        CCowData() : m_ptr(ms_memStatic)
        {

        }

        CCowData(CCowData&& in_rrOther) noexcept
        {
            m_ptr = in_rrOther.m_ptr;
            in_rrOther.m_ptr = ms_memStatic;
        }

        CCowData(const CCowData& in_rOther)
        {
            Set(in_rOther);
        }

        ~CCowData()
        {
            Unset();
        }
    };
}