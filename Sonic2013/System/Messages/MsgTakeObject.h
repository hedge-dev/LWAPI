#pragma once

namespace app::xgame
{
	class MsgTakeObject : public fnd::Message
	{
	public:
		enum EType
		{
			eType_Ring,
			eType_DroppedRing,
			eType_SuperRing,
			eType_OneUp,
			eType_RedRing,
			eType_SpeedUp,
			eType_SlowDown,
			eType_Invincibility,
			eType_Warp,
			eType_Barrier,
			eType_WaterBarrier,
			eType_ThunderBarrier,
			eType_RedRingRadar,
			eType_StealRing,
			eType_SwapRing,
			eType_PhantomBomb,
			eType_YoshiOneUp,
			eType_YoshiCoin,
			eType_ZeldaOneUp
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

		void SetShapeUserID(uint userID)
		{
			m_UserID = userID;
			m_HasUserID = 1;
		}
	};
}