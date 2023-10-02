#pragma once

namespace app
{
	struct WorldAreaMapCInfo
	{
	public:
		struct Event
		{
			INSERT_PADDING(24);
		};
		
		bool Unk1{};
		csl::ut::MoveArray<Event> Events{};
		bool IsRequestingChangeItem{};
		bool IsTrialVersion{};

		WorldAreaMapCInfo(csl::fnd::IAllocator* in_pAllocator) : Events(15, in_pAllocator)
		{

		}
	};

	class GameModeWorldAreaMap :
		public GameMode,
		public TTinyFsm<GameModeWorldAreaMap, GameModeUtil::Event<GameModeWorldAreaMap>, true>,
		TinyFsmSetOption<TiFSM_OPTION_USE_FP_TOP>
	{
	public:
		csl::ut::FixedString<32> Unk1{ "worldmap" };
		csl::ut::FixedString<16> Unk2{ "worldmap" };
		csl::ut::FixedString<16> Unk3{ "worldmap" };
		INSERT_PADDING(4) {};
		INSERT_PADDING(4) {};
		INSERT_PADDING(8) {}; // boost::intrusive_ptr<worldmap::CWorldMapCamera>[2]
		ut::RefPtr<Camera::CCameraController> rpCameraController{}; // boost::intrusive_ptr<Camera::CCameraController>
		INSERT_PADDING(4) {};
		const char* pStageName{ "w1a01" };
		INSERT_PADDING(4) {};
		csl::ut::Bitset<uint> Flags{};
		int Unk4{ -1 };
		INSERT_PADDING(160) {};
		csl::math::Vector3 Unk5{};
		csl::math::Vector3 Unk6{};
		csl::math::Vector3 PlayerPosition{};
		INSERT_PADDING(8) {}; // worldmap::MapCoord CursorPosition{};
		INSERT_PADDING(8) {};
		csl::math::Vector3 SonicPosition{};
		INSERT_PADDING(4) {};
		INSERT_PADDING(4) {};
		INSERT_PADDING(4) {}; // HUD::CHudWorldAreaMap* pHud{};
		INSERT_PADDING(4) {};
		INSERT_PADDING(4) {};
		INSERT_PADDING(4) {}; // worldmap::CWorldMapCursor* pCursor{};
		INSERT_PADDING(4) {}; // worldmap::CWorldMapSonic* pSonic{};
		INSERT_PADDING(28) {}; // worldmap::CWorldMapRoad* pRoads[7]{};
		INSERT_PADDING(4) {};
		INSERT_PADDING(248) {}; // worldmap::CWorldMapDiorama* pDioramas[62]{};
		INSERT_PADDING(248) {};
		INSERT_PADDING(4) {}; // worldmap::CWorldMapEarth* pEarth{};
		INSERT_PADDING(8) {}; // GameObjectHandle<worldmap::CWorldMapOmochao> OmochaoHandle{};
		INSERT_PADDING(8) {}; // GameObjectHandle<worldmap::CWorldMapYacker> YackerHandle{};
		INSERT_PADDING(8) {}; // GameObjectHandle<worldmap::CWorldMapItembox> ItemboxHandle{};
		INSERT_PADDING(56) {}; // GameObjectHandle<worldmap::CWorldMapItembox> ItemboxItemHandles[7]{};
		INSERT_PADDING(56) {}; // GameObjectHandle<worldmap::WorldMapChaosEmerald> EmeraldHandles[7]{};
		INSERT_PADDING(8) {}; // GameObjectHandle<worldmap::WorldMapFlowEffect> FlowEffect{};
		WorldAreaMapDioramaInfo DioramaInfos[86]{};
		int DioramaType[62]{};
		csl::ut::MoveArray<WorldAreaMapCInfo::Event> Events{ m_pAllocator };
		WorldAreaMapCInfo::Event CurrentEvent{};
		int Unk7{};
		int Unk8{};
		int Unk9{ 8 };
		int Unk10{};
		int Unk11{};
		int Unk12{ -1 };
		alignas(16) csl::math::Vector3 Unk13[8]{};
		csl::math::Vector2 Unk14{};
		csl::math::Quaternion EarthRotation{};
		csl::math::Vector2 Unk15{};
		csl::math::Vector2 Unk16{};
		float Unk17{};
		INSERT_PADDING(16) {};
		int UnlockedMinigameCount[7]{};
		csl::ut::InplaceMoveArray<uint8, 3> Unk18{ nullptr };
		INSERT_PADDING(4) {};
		INSERT_PADDING(4) {};
		INSERT_PADDING(4) {};
		INSERT_PADDING(4) {};
		HUD::CHudCmnButton* pHudButton{};
		INSERT_PADDING(4) {};
		fnd::SoundHandle Unk19{};
		fnd::SoundHandle Unk20{};
		INSERT_PADDING(24) {}; // GameObjectHandle<worldmap::CWorldMapDiorama> DioramaHandle[3]{};
	};

	inline bool IsExistNextOpenCircusStage(int in_zoneIndex, int* out_pLastOpenCircusIndex, int* out_pRedRingRequirement)
	{
		int save{};

		if (in_zoneIndex >= 7)
			return false;
	
		auto* pSaveManager = csl::fnd::Singleton<SaveData::CSaveManager>::GetInstance();
		auto* pFlagSet = pSaveManager->GetSaveData(&save)->GetCurrentGameData(&save)->GetFlagSet(&save);
		if (!pFlagSet->GetFlagZoneUnlocked(in_zoneIndex))
			return false;
	
		int redRingCount = pFlagSet->CountRedRingZone(in_zoneIndex, 20);
		if (redRingCount >= 20)
			return false;
	
		*out_pLastOpenCircusIndex = redRingCount / 5;
		*out_pRedRingRequirement = 5 * (redRingCount / 5) + 5 - redRingCount;

		return true;
	}
}