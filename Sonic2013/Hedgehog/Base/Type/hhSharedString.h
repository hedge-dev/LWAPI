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

        CSharedString(const char* data)
        {
            m_data.Set(data, data ? strlen(data) : 0);
        }

        const char* c_str() const
        {
            return m_data.Get();
        }

        int compare(const CSharedString& other) const
        {
            return strcmp(c_str(), other.c_str());
        }

        CSharedString& operator=(const CSharedString& other)
        {
            m_data.Unset();
            m_data.Set(other.m_data);
            return *this;
        }

        CSharedString& operator=(const char* other)
        {
            m_data.Unset();
            m_data.Set(other, other ? strlen(other) : 0);
            return *this;
        }

        bool operator>(const CSharedString& other) const
        {
            return compare(other) > 0;
        }

        bool operator>=(const CSharedString& other) const
        {
            return compare(other) >= 0;
        }

        bool operator<(const CSharedString& other) const
        {
            return compare(other) < 0;
        }

        bool operator<=(const CSharedString& other) const
        {
            return compare(other) <= 0;
        }

        bool operator==(const CSharedString& other) const
        {
            return compare(other) == 0;
        }

        bool operator!=(const CSharedString& other) const
        {
            return !(*this == other);
        }

        bool operator==(const char* other) const
        {
            return strcmp(c_str(), other) == 0;
        }

        bool operator!=(const char* other) const
        {
            return !(*this == other);
        }
    };
}