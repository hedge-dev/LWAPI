#pragma once

namespace hh::base
{
    class CSharedString
    {
    private:
        CCowData<char> m_data;

    public:
        CSharedString()
        {

        }

        CSharedString(const char* in_pData)
        {
            m_data.Set(in_pData, in_pData ? strlen(in_pData) : 0);
        }

        const char* c_str() const
        {
            return m_data.Get();
        }

        int compare(const CSharedString& in_rOther) const
        {
            return strcmp(c_str(), in_rOther.c_str());
        }

        CSharedString& operator=(const CSharedString& in_rOther)
        {
            m_data.Unset();
            m_data.Set(in_rOther.m_data);
            return *this;
        }

        CSharedString& operator=(const char* in_pOther)
        {
            m_data.Unset();
            m_data.Set(in_pOther, in_pOther ? strlen(in_pOther) : 0);
            return *this;
        }

        bool operator>(const CSharedString& in_rOther) const
        {
            return compare(in_rOther) > 0;
        }

        bool operator>=(const CSharedString& in_rOther) const
        {
            return compare(in_rOther) >= 0;
        }

        bool operator<(const CSharedString& in_rOther) const
        {
            return compare(in_rOther) < 0;
        }

        bool operator<=(const CSharedString& in_rOther) const
        {
            return compare(in_rOther) <= 0;
        }

        bool operator==(const CSharedString& in_rOther) const
        {
            return compare(in_rOther) == 0;
        }

        bool operator!=(const CSharedString& in_rOther) const
        {
            return !(*this == in_rOther);
        }

        bool operator==(const char* in_pOther) const
        {
            return strcmp(c_str(), in_pOther) == 0;
        }

        bool operator!=(const char* in_pOther) const
        {
            return !(*this == in_pOther);
        }
    };
}