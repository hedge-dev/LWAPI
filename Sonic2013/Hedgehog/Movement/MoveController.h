#pragma once

namespace app::game
{
	class GOCMovement;
	enum MoveControllerType : uint8
	{
		eMoveControllerType_0,
		eMoveControllerType_AddVelocityFreefall,
		eMoveControllerType_VelocityReference,
		eMoveControllerType_PopupScreen,
		eMoveControllerType_Popup,
		eMoveControllerType_Straight = 5,
		eMoveControllerType_Dice = 5,
		eMoveControllerType_Bound,
		eMoveControllerType_Hopping,
		eMoveControllerType_RotateToTarget,
		eMoveControllerType_RailTruck,
		eMoveControllerType_CharacterRigidBody,
		eMoveControllerType_EnemyBatabata,
		eMoveControllerType_EnemyBatabataFV,
		eMoveControllerType_EnemyBatabataSV,
		eMoveControllerType_EnemyBatabataCY,
		eMoveControllerType_EnemyBatabataGR,
		eMoveControllerType_EnemyBatabataSP,
		eMoveControllerType_EnemyRoadRunner,
		eMoveControllerType_EnemyGola,
		eMoveControllerType_EnemyGolaSpike,
		eMoveControllerType_EnemyBasaran,
		eMoveControllerType_EnemyBasaranVampire,
		eMoveControllerType_EnemyBeeton,
		eMoveControllerType_EnemyValkeen,
		eMoveControllerType_EnemyEggPawn,
		eMoveControllerType_BossFruitMasterShot = 25,
		eMoveControllerType_BossEnemyKokekoShot = 25,
		eMoveControllerType_EnemyBalloonFish,
		eMoveControllerType_EnemyUnidas,
		eMoveControllerType_EnemyFlyingPod,
		eMoveControllerType_EnemySeaDoraFV,
		eMoveControllerType_EnemySeaDoraSV,
		eMoveControllerType_EnemyMogurinFV = 32,
		eMoveControllerType_EnemyMogurinSV,
		eMoveControllerType_EnemyPenPen,
		eMoveControllerType_EnemyMantaRay,
		eMoveControllerType_EnemyGroundAntlion,
		eMoveControllerType_EnemyPonPon,
		eMoveControllerType_EnemyZakinSentinel,
		eMoveControllerType_EnemyTonberFV,
		eMoveControllerType_EnemyOctar,
		eMoveControllerType_EnemyValkeenDiving,
		eMoveControllerType_EnemyKamakillerShot,
		eMoveControllerType_EnemyHeadfishBoat,
		eMoveControllerType_EnemyBalloonFishSv,
		eMoveControllerType_EnemyBalloonFishSky,
		eMoveControllerType_EnemyEggPawnParaSV,
		eMoveControllerType_EnemyEggPawnParaFall,
		eMoveControllerType_EnemyDosun,
		eMoveControllerType_SuckedPixie,
		eMoveControllerType_EnemyKeese,
		eMoveControllerType_EnemyBlowOffObject,
		eMoveControllerType_ObjAnimal,
		eMoveControllerType_ObjReleaseAnimal,
		eMoveControllerType_MidBossMMMoon = 54,
		eMoveControllerType_DlcBossMMMoon = 54,
		eMoveControllerType_MidBossMoonMaster,
		eMoveControllerType_MidBossGanmen,
		eMoveControllerType_MidBossGanmenMaster,
		eMoveControllerType_BossGanmenTornado,
		eMoveControllerType_MidBossFMObj,
		eMoveControllerType_MidBossDMDragonShot,
		eMoveControllerType_BossMoonMaster,
		eMoveControllerType_BossGanmenMaster,
		eMoveControllerType_BossOwlMaster,
		eMoveControllerType_BossDragonMaster,
		eMoveControllerType_RushBossOwlMaster,
		eMoveControllerType_RushBossPopoesMaster,
		eMoveControllerType_RushBossDragonMaster,
		eMoveControllerType_RushBossDragonMasterGiant,
		eMoveControllerType_LastBoss,
		eMoveControllerType_DlcBossGanmen,
		eMoveControllerType_DlcBossGanmenMaster,
		eMoveControllerType_DlcBossMoonMaster = 73,
		eMoveControllerType_DlcBossFMObj,
		eMoveControllerType_ObjStompingMoai,
		eMoveControllerType_ObjMiniCactusBall,
		eMoveControllerType_ObjBigWindmill,
		eMoveControllerType_ObjSandWormVenom,
		eMoveControllerType_ObjFruitsCommon = 83,
		eMoveControllerType_ObjFruitsPath,
		eMoveControllerType_ObjFruitsPursue,
		eMoveControllerType_ObjFruitsStomp,
		eMoveControllerType_ObjFruitsRetreat,
		eMoveControllerType_ObjWhirlingWaves,
		eMoveControllerType_NeedleDrum,
		eMoveControllerType_RailTruckFallTurn,
		eMoveControllerType_ObjOilBall,
		eMoveControllerType_ObjOilBallJump,
		eMoveControllerType_ObjOilBallCurveJump,
		eMoveControllerType_ObjBlowFloor,
		eMoveControllerType_ObjRotatingDoughnuts,
		eMoveControllerType_ObjSnowManBallPop,
		eMoveControllerType_ObjSnowManBallFall,
		eMoveControllerType_ObjSnowManBallRoll,
		eMoveControllerType_ObjDamageSunflower = 100,
		eMoveControllerType_ObjJellyBerryBullet,
		eMoveControllerType_ObjMoveThornSand,
		eMoveControllerType_ObjBilliardBall,
		eMoveControllerType_ObjPillboxLargeShot = 105,
		eMoveControllerType_ToTouchPoint,
		eMoveControllerType_MinigameBall,
		eMoveControllerType_MinigameRotate,
		eMoveControllerType_MinigameBalloonPoints,
		eMoveControllerType_MinigameBalloonDescent,
		eMoveControllerType_MinigameBalloonRepeat,
		eMoveControllerType_MinigameBalloonLinear,
		eMoveControllerType_CoconutCannonBig,
		eMoveControllerType_ObjCocco,
		eMoveControllerType_ObjGolonRock,
		eMoveControllerType_MoveRcFollow,
		eMoveControllerType_MoveRcNormal,
		eMoveControllerType_MoveRcBankController,
		eMoveControllerType_MoveRcAppear,
		eMoveControllerType_MoveRcDisappear,
		eMoveControllerType_MoveRcKnockBack,
		eMoveControllerType_MoveRcStun,
		eMoveControllerType_MoveRcHold,
		eMoveControllerType_MoveRcBalloonLift,
		eMoveControllerType_MoveRcBalloonPop,
		eMoveControllerType_MoveRcOmochaoDash,
		eMoveControllerType_MoveRcHovercraft,
		eMoveControllerType_MAX
	};

	class MoveController
	{
	public:
		enum FlagType : uint8
		{
			eFlagType_0,
			eFlagType_1,
			eFlagType_2,
			eFlagType_3,
			eFlagType_4,
			eFlagType_5,
			eFlagType_6,
			eFlagType_7,
		};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpResetFlag, ASLR(0x04C3DE0), MoveController*, FlagType);

	public:
		csl::ut::Enum<MoveControllerType, uint8> Type{};
		GOCMovement* pMovement{};
		csl::ut::Bitset<uint8> Flags{};
		
		MoveController(MoveControllerType in_type)
		{
			Type = in_type;
			SetFlag(FlagType::eFlagType_1);
		}

		virtual const csl::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const
		{
			return nullptr;
		}

		virtual void Update(const fnd::SUpdateInfo& in_rUpdateInfo)
		{
			return;
		}
		
		virtual void OnEnter()
		{
			return;
		}
		
		virtual void OnLeave()
		{
			return;
		}
		
		virtual ~MoveController() = default;

		void SetFlag(FlagType in_flag)
		{
			Flags.set(in_flag);
			if (in_flag == FlagType::eFlagType_1 && TestFlag(FlagType::eFlagType_0))
				OnEnter();
		}
		
		bool TestFlag(FlagType in_flag)
		{
			return Flags.test(in_flag);
		}

		void ResetFlag(FlagType in_flag)
		{
			Flags.reset(in_flag);
			if (in_flag == FlagType::eFlagType_1 && TestFlag(FlagType::eFlagType_0))
				OnLeave();
		}

		GOCMovement* GetOwnerMovement() const
		{
			return pMovement;
		}

		void SetOwnerMovement(GOCMovement* in_pMovement)
		{
			pMovement = in_pMovement;
		}

		MoveControllerType GetType()
		{
			return Type;
		}
	};

	namespace detail_movement
	{
		static void ResetUpdateFlag(MoveController* in_pController)
		{
			in_pController->ResetFlag(MoveController::FlagType::eFlagType_1);
		}
		
		static void SetUpdateFlag(MoveController* in_pController)
		{
			in_pController->SetFlag(MoveController::FlagType::eFlagType_1);
		}

		static void CallOnEnter(MoveController* in_pController)
		{
			if (in_pController->TestFlag(MoveController::FlagType::eFlagType_1))
				in_pController->OnEnter();
		}

		static void CallEndSetup(MoveController* in_pController)
		{
			in_pController->SetFlag(MoveController::FlagType::eFlagType_0);
		}
	}
}