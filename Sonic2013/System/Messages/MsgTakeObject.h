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
			eType_ChangeRing,
			eType_PhantomBomb,
			eType_YoshiOneUp,
			eType_YoshiCoin,
			eType_ZeldaOneUp
		};
		
		EType Type;
		uint ItemLevel{ static_cast<uint>(-1) };
		bool Taken{};
		bool HasUserID{};
		uint UserID{};
		
		inline const static unsigned int MessageID = 0x6008;

		MsgTakeObject(EType in_type) : Message(MessageID), Type(in_type)
		{

		}

		Message* Clone() override
		{
			return new MsgTakeObject(*this);
		}

		bool IsValidUserID() const
		{
			return HasUserID;
		}

		void SetShapeUserID(uint in_userID)
		{
			UserID = in_userID;
			HasUserID = 1;
		}

		void ResetShapeUserID()
		{
			UserID = 0;
			HasUserID = 0;
		}
	};
}