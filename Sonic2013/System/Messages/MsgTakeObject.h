#pragma once

namespace app::xgame
{
	class MsgTakeObject : public fnd::Message
	{
	public:
		enum EType
		{
			eType_Ring
		};
		
		inline const static unsigned int MessageID = 0x6008;
		EType m_Type;
		uint m_Unk1{static_cast<uint>(-1)};
		bool m_Taken{};
		bool m_HasUserID{};
		uint m_UserID{};
		
		MsgTakeObject(EType type) : Message(MessageID), m_Type(type)
		{
			
		}

		Message* Clone() override
		{
			return new MsgTakeObject(*this);
		}

		bool IsValidUserID() const
		{
			return m_HasUserID;
		}
	};
}