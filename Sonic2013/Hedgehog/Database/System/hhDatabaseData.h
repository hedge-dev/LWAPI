#pragma once

// From https://github.com/blueskythlikesclouds/BlueBlur
namespace hh::db
{
    enum EDatabaseDataFlags : uint8_t
    {
        eDatabaseDataFlags_IsMadeOne = 0x1,
        eDatabaseDataFlags_IsMadeAll = 0x2,
        eDatabaseDataFlags_CreatedFromArchive = 0x4,
        eDatabaseDataFlags_IsMadeMakingOne = 0x8
    };

	class CDatabaseData : public base::CObject
	{
	public:
        uint8_t m_Flags; // see EDatabaseDataFlags
        base::CSharedString m_TypeAndName;

		virtual ~CDatabaseData() = default;
        virtual bool CheckMadeAll()
        {
            return true;
        }

        bool IsMadeAllInternal()
        {
            if ((m_Flags & eDatabaseDataFlags_IsMadeOne) == 0 || !CheckMadeAll())
                return false;

            m_Flags |= eDatabaseDataFlags_IsMadeAll;
            return true;
        }

        bool IsMadeAll()
        {
            return (m_Flags & eDatabaseDataFlags_IsMadeAll) != 0 || IsMadeAllInternal();
        }
	};
}