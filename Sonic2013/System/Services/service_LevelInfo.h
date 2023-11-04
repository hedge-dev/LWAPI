#pragma once

namespace app
{
	namespace StageInfo
	{
		class SStageData;
	}

	struct SPlayerInfo
	{
		int PlayerNo{};
		uint ActorId{};
		int NumChallenges{};
		int RivalRingCount{};
		int NumHearts{};
		int MaxNumHearts{};
		float HorzVelocityLength{};
	};
	
	class CLevelInfo : public fnd::GameService
	{
	private:
		inline static FUNCTION_PTR(SPlayerInfo*, __thiscall, ms_fpGetPlayerInfo, ASLR(0x009125A0), CLevelInfo*, uint);
		inline static FUNCTION_PTR(int, __thiscall, ms_fpGetPlayerNo, ASLR(0x00912570), const CLevelInfo*, const uint);
		inline static FUNCTION_PTR(uint, __thiscall, ms_fpGetPlayerID, ASLR(0x00912520), const CLevelInfo*);
		inline static FUNCTION_PTR(uint, __thiscall, ms_fpGetPlayerID2, ASLR(0x00912550), const CLevelInfo*, const uint);
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEFD1C));

	public:
		inline static const uint DLCStageIndices[] = { 0, 17, 18, 19 };

		csl::ut::FixedArray<SPlayerInfo, 2> Players{};
		size_t PlayerNum{};
		csl::ut::FixedArray<size_t, 2> Cameras{};
		size_t UnkRc{};
		size_t HudActor{};
		size_t RcActor{};
		const char* Level{};
		csl::ut::Bitset<uint> StageFlags{};
		csl::ut::Bitset<uint> UnkFlags{};
		INSERT_PADDING(16){};
		Game::EPlayMode PlayMode{};

		size_t GetCameraActor(size_t i) const
		{
			if (i > PlayerNum)
				return 0;

			return Cameras[i];
		}

		[[nodiscard]] uint GetPlayerID() const
		{
			return ms_fpGetPlayerID(this);
		}
		
		[[nodiscard]] uint GetPlayerID(const uint playerNo) const
		{
			return ms_fpGetPlayerID2(this, playerNo);
		}

		int GetPlayerNo(uint actorID) const
		{
			return ms_fpGetPlayerNo(this, actorID);
		}

		int GetNumPlayers() const
		{
			if (PlayerNum != 2)
				return 1;
		
			return 2;
		}

		bool IsPlayer(uint in_actorId) const
		{
			return GetPlayerNo(in_actorId) >= 0;
		}

		SPlayerInfo* GetPlayerInfo(uint playerNum)
		{
			return ms_fpGetPlayerInfo(this, playerNum);
		}

		int GetDLCStageIndex()
		{
			if (StageFlags.test(17))
				return 1;
			
			if (StageFlags.test(18))
				return 2;
			
			if (StageFlags.test(19))
				return 3;

			return 0;
		}

		bool GetFlagRedRingObtained(int in_redRingNo) const
		{
			if (in_redRingNo >= 5)
				return false;
		
			return UnkFlags.test(in_redRingNo);
		}

		void SetFlagRedRingObtained(uint in_bit, bool in_enable)
		{
			UnkFlags.set(in_bit, in_enable);
		}

		void ReflectStageInfo(const StageInfo::SStageData& in_rStageData)
		{

		}

		void SetPlayMode(Game::EPlayMode in_playMode)
		{
			PlayMode = in_playMode;
			if (!PlayMode || PlayMode > 2)
				return;
		
			StageFlags.set(2, true);
			StageFlags.set(3, true);
			StageFlags.set(4, true);
		}

		void SetDLCStage(uint in_dlcIndex)
		{
			StageFlags.set(DLCStageIndices[in_dlcIndex]);
		}

		bool IsPlayingZeldaEvent()
		{
			return StageFlags.test(20);
		}

		void SetPlayingZeldaEvent(bool in_isZeldaEvent)
		{
			StageFlags.set(20, in_isZeldaEvent);
		}

		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}
	};
}