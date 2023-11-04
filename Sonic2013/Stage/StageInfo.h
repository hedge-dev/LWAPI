#pragma once

namespace app::StageInfo
{
	static std::pair<const char*, Game::EPhantomType> phantomMap[Game::EPhantomType::ePhantom_Max] =
	{
		{ "drill",		Game::EPhantomType::ePhantom_Drill },
		{ "laser",		Game::EPhantomType::ePhantom_Laser },
		{ "rocket",		Game::EPhantomType::ePhantom_Rocket },
		{ "eagle",		Game::EPhantomType::ePhantom_Eagle },
		{ "asteroid",	Game::EPhantomType::ePhantom_Asteroid },
		{ "rhythm",		Game::EPhantomType::ePhantom_Rhythm },
		{ "bomb",		Game::EPhantomType::ePhantom_Bomb },
		{ "hover",		Game::EPhantomType::ePhantom_Hover },
		{ "quake",		Game::EPhantomType::ePhantom_Quake }
	};
	
	static std::pair<const char*, animal::AnimalType> animalMap[animal::AnimalType::eAnimal_Max] =
	{
		{ "FLICKIE",	animal::AnimalType::eAnimal_Flickie },
		{ "COOKIE",		animal::AnimalType::eAnimal_Cookie },
		{ "PECKIE",		animal::AnimalType::eAnimal_Peckie },
		{ "PICKIE",		animal::AnimalType::eAnimal_Pickie },
		{ "POCKY",		animal::AnimalType::eAnimal_Pocky },
		{ "RICKY",		animal::AnimalType::eAnimal_Ricky },
		{ "ROCKY",		animal::AnimalType::eAnimal_Rocky },
	};

	static Game::EPhantomType PhantomTypeFromName(const char* in_pName);
	static animal::AnimalType AnimalTypeFromName(const char* in_pName);

	class CStageInfo
	{
	private:
		inline static FUNCTION_PTR(int, __thiscall, ms_fpGetAdvStageIndex, ASLR(0x00912C30), CStageInfo*, int, int);
		inline static FUNCTION_PTR(int, __cdecl, ms_fpReadZone_All, ASLR(0x00912F20), const char*, game::LuaScript&, void*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetupZoneInfo, ASLR(0x00913D60), CStageInfo*);
		inline static CStageInfo** ms_ppInstance = reinterpret_cast<CStageInfo**>(ASLR(0x00FEFD38));

	public:
		struct SZoneInfo
		{
			uint StageOffset{}; // Starting stage offset in CStageInfo::m_Stages
			uint NumMissions{};

			csl::ut::FixedString<16> Missions[5];
		};

		csl::fnd::IAllocator* pAllocator{};
		csl::ut::ObjectMoveArray<SStageData*> Stages{ pAllocator };
		csl::ut::ObjectMoveArray<WorldNode*> Worlds[2]{ { pAllocator }, { pAllocator } };
		csl::ut::FixedArray<SZoneInfo, 19> Zones{};
		csl::ut::MoveArray<const char*> StageNames{ pAllocator };

		CStageInfo(csl::fnd::IAllocator* in_pAllocator) : pAllocator(in_pAllocator)
		{
			
		}

		~CStageInfo()
		{
			for (auto& stage : Stages)
			{
				stage->Release();
			}

			for (auto& world : Worlds)
			{
				for (auto& node : world)
				{
					node->Release();
				}
			}
		}

		[[nodiscard]] static CStageInfo* GetInstance()
		{
			return *ms_ppInstance;
		}

		void Setup(game::LuaScript& in_rScript)
		{
			size_t missionCount{};
			in_rScript.ForEach("mission_all", Mission_CountAll, &missionCount);
			in_rScript.ForEach("test_mission_all", Mission_CountAll, &missionCount);

			if (missionCount)
			{
				in_rScript.ForEach("mission_all", ReadMission_All, this);
				in_rScript.ForEach("test_mission_all", ReadMission_All, this);
			}

			in_rScript.ForEach("zone_table", ReadZone_All, this);
			SetupZoneInfo();
		}

		void SetupZoneInfo()
		{
			ms_fpSetupZoneInfo(this);
		}

		void AddDebugLevel(const char* in_pWorldName, const char* in_pTitle, const char* in_pId, size_t in_worldType = 0)
		{
			if (in_worldType > 1)
			{
				return;
			}

			auto& world = Worlds[in_worldType];
			WorldNode* node{};

			for (auto& worldNode : world)
			{
				if (!strncmp(worldNode->GetTitle(), in_pWorldName, strlen(in_pWorldName)))
				{
					node = worldNode;
					break;
				}
			}

			if (node == nullptr)
			{
				node = new(world.get_allocator()) WorldNode();
				node->SetTitle(in_pWorldName);
				world.push_back(node);

				node->AddNode({ in_pTitle, in_pId });
				return;
			}

			for (auto& level : node->GetStages())
			{
				if (level.Name == in_pId)
				{
					level.Title = in_pTitle;
					return;
				}
			}

			node->AddNode({ in_pTitle, in_pId });
		}

		SStageData* GetStageData(const char* in_pName) const
		{
			for (auto& pData : Stages)
			{
				if (pData->Name == in_pName)
					return pData;
			}

			return nullptr;
		}

		static void ReadZone_All(const char* in_pCat, game::LuaScript& in_rScript, void* in_pCtx)
		{
			ms_fpReadZone_All(in_pCat, in_rScript, in_pCtx);
		}

		static void Mission_CountAll(const char* in_pCat, game::LuaScript& in_rScript, void* in_pCtx)
		{
			in_rScript.ForEach("missions", Mission_CountMission, in_pCtx);
		}

		static void Mission_CountMission(const char* in_pCat, game::LuaScript& in_rScript, void* in_pCtx)
		{
			++*(size_t*)in_pCtx;
		}

		static void ReadMission_All(const char* in_pCat, game::LuaScript& in_rScript, void* in_pCtx)
		{
			in_rScript.ForEach("missions", ReadMission_Mission, in_pCtx);
		}

		static void ReadMission_Mission(const char* in_pCat, game::LuaScript& in_rScript, void* in_pCtx)
		{
			auto* pStageData = new(static_cast<CStageInfo*>(in_pCtx)->pAllocator) StageInfo::SStageData();
			const char* pString{};

			if (!in_rScript.GetString("name", pString))
				return;
		
			pStageData->Name = pString;

			if (in_rScript.GetString("dir", pString))
				pStageData->Directory = pString;
			else
				pStageData->Directory = pStageData->Name;

			if (in_rScript.GetString("path_data", pString))
				pStageData->PathData = pString;
			else
				pStageData->PathData = pStageData->Directory;
		
			if (!in_rScript.GetVector3("player_pos", pStageData->PlayerPositions[0]))
				pStageData->PlayerPositions[0] = { 0.0f, 0.0f, 0.0f };

			csl::math::Vector3 direction{};
			if (in_rScript.GetVector3("player_dir", direction))
			{
				pStageData->PlayerRotations[0].x() = direction.x() * MATHF_PI / 180.0f;
				pStageData->PlayerRotations[0].y() = direction.y() * MATHF_PI / 180.0f;
				pStageData->PlayerRotations[0].z() = direction.z() * MATHF_PI / 180.0f;
			}

			if (!in_rScript.GetVector3("player2_pos", pStageData->PlayerPositions[1]))
			{
				pStageData->PlayerPositions[1] = pStageData->PlayerPositions[0];
			}

			if (in_rScript.GetVector3("player2_dir", direction))
			{
				pStageData->PlayerRotations[1].x() = direction.x() * MATHF_PI / 180.0f;
				pStageData->PlayerRotations[1].y() = direction.y() * MATHF_PI / 180.0f;
				pStageData->PlayerRotations[1].z() = direction.z() * MATHF_PI / 180.0f;
			}
			else
			{
				pStageData->PlayerRotations[1] = pStageData->PlayerRotations[0];
			}

			if (in_rScript.GetString("bgm", pString))
				pStageData->Bgm = pString;

			if (in_rScript.GetString("bgm_sv", pString))
				pStageData->BgmSv = pString;

			if (in_rScript.GetString("amb", pString))
				pStageData->Amb = pString;

			if (in_rScript.GetString("amb_in", pString))
				pStageData->AmbIn = pString;

			in_rScript.GetFloat("reverb", pStageData->Reverb);

			if (in_rScript.GetString("player_mode", pString))
			{
				if (!strcmp(pString, "2D"))
					pStageData->PlayerFlags.set(0);
				else if (!strcmp(pString, "WATER"))
					pStageData->PlayerFlags.set(1);
				else if (!strcmp(pString, "SKYCHASE"))
					pStageData->PlayerFlags.set(2);
				else if (!strcmp(pString, "TOP"))
					pStageData->PlayerFlags.set(3);
				else if (!strcmp(pString, "SNOWBALL"))
					pStageData->PlayerFlags.set(4);
			}
			
			ut::InplaceTempArray<const char*, 10> stageAttrs{};
			if (in_rScript.GetStringArray("attrs", stageAttrs))
			{
				for (size_t i = 0; i < stageAttrs.size(); i++)
				{
					if (!strcmp(stageAttrs[i], "no_redring"))
						pStageData->StageFlags.set(2, true);

					if (!strcmp(stageAttrs[i], "only_normalplay"))
					{
						pStageData->StageFlags.set(3, true);
						pStageData->StageFlags.set(4, true);
					}

					if (!strcmp(stageAttrs[i], "bakubaku"))
						pStageData->StageFlags.set(5, true);

					if (!strcmp(stageAttrs[i], "floor_reflect"))
						pStageData->StageFlags.set(6, true);

					if (!strcmp(stageAttrs[i], "randombox_noquake"))
						pStageData->StageFlags.set(7, true);

					if (!strcmp(stageAttrs[i], "no_bomb"))
						pStageData->StageFlags.set(8, true);

					if (!strcmp(stageAttrs[i], "lastboss"))
						pStageData->StageFlags.set(9, true);

					if (!strcmp(stageAttrs[i], "dlc"))
					{
						pStageData->StageFlags.set(3, true);
						pStageData->StageFlags.set(10, true);
					}

					if (!strcmp(stageAttrs[i], "yoshiisland"))
						pStageData->StageFlags.set(11, true);

					if (!strcmp(stageAttrs[i], "zelda"))
						pStageData->StageFlags.set(12, true);
				}
			}

			if (strstr(pStageData->Name.c_str(), "mini"))
				pStageData->StageFlags.set(0, true);
			else if (strstr(pStageData->Name.c_str(), "batl"))
				pStageData->StageFlags.set(1, true);

			ut::InplaceTempArray<const char*, Game::EPhantomType::ePhantom_Max> phantoms{};
			if (in_rScript.GetStringArray("phantoms", phantoms))
			{
				for (size_t i = 0; i < phantoms.size(); i++)
				{
					Game::EPhantomType type = PhantomTypeFromName(phantoms[i]);
					if (type != static_cast<Game::EPhantomType>(-1))
						pStageData->Phantoms.push_back_unchecked(type);
				}
			}

			if (pStageData->StageFlags.test(1))
				pStageData->Phantoms.push_back_unchecked(Game::EPhantomType::ePhantom_Quake);
			else if (!pStageData->StageFlags.test(0) && !pStageData->StageFlags.test(1) && !pStageData->StageFlags.test(8))
				pStageData->Phantoms.push_back_unchecked(Game::EPhantomType::ePhantom_Bomb);

			if (in_rScript.OpenNode("time"))
			{
				in_rScript.GetFloat("time_limit", pStageData->TimeData.Limit);
				ut::InplaceTempArray<float, 4> times{};
				if (in_rScript.GetFloatArray("rank", times))
				{
					for (size_t i = 0; i < times.size(); i++)
						pStageData->TimeData.RankIntervals[i] = times[i];
				}

				in_rScript.CloseNode();
			}

			ut::InplaceTempArray<const char*, 3> animals{};
			if (in_rScript.GetStringArray("animals", animals))
			{
				for (size_t i = 0; i < animals.size(); i++)
					pStageData->Animals.push_back_unchecked(AnimalTypeFromName(animals[i]));
			}

			if (!in_rScript.GetInt("unlock_animals", pStageData->RequiredAnimals))
				pStageData->RequiredAnimals = 0;

			if (in_rScript.GetString("clear_cond", pString))
			{
				if (!strcmp(pString, "goal"))
					pStageData->ClearCondition = StageInfo::SStageData::ClearCondition::eClearCondition_Goal;
				else if (!strcmp(pString, "timeout"))
					pStageData->ClearCondition = StageInfo::SStageData::ClearCondition::eClearCondition_Timeout;
			}

			if (!in_rScript.GetFloat("eagle_altitude", pStageData->EagleAltitude))
				pStageData->EagleAltitude = 20.0f;

			static_cast<CStageInfo*>(in_pCtx)->Stages.push_back(pStageData);
		}

		void ReadCategoryDebug(const char* pCat, game::LuaScript& rScript, size_t worldIdx)
		{
			if (worldIdx > 2)
				return;

			rScript.ForEach(pCat, [](const char* node, game::LuaScript& script, void* pCtx)
				{
					auto* pWorlds = static_cast<csl::ut::ObjectMoveArray<WorldNode*>*>(pCtx);
					auto* world = new(pWorlds->get_allocator()) WorldNode();

					const char* title{};
					script.GetString("title", title);
					world->SetTitle(title);

					script.ForEach("stages", [](const char* node, game::LuaScript& script, void* pCtx)
						{
							auto* world = static_cast<WorldNode*>(pCtx);
							const char* name{};
							const char* title{};

							script.GetString("name", name);
							script.GetString("title", title);

							StageNode stage;
							stage.Name = name;
							stage.Title = title;

							world->AddNode(stage);
						}, world);

					pWorlds->push_back(world);

				}, &Worlds[worldIdx]);
		}

		const char* GetAdvStageName(int in_stageIndex)
		{
			return StageNames[in_stageIndex];
		}

		int GetAdvStageIndex(int in_worldIndex, int in_stageIndex)
		{
			return ms_fpGetAdvStageIndex(this, in_worldIndex, in_stageIndex);
		}

		SStageData* GetAdvStageData(int in_stageIndex)
		{
			return GetStageData(GetAdvStageName(in_stageIndex));
		}
	};

	Game::EPhantomType PhantomTypeFromName(const char* in_pName)
	{
		for (size_t i = 0; i < Game::EPhantomType::ePhantom_Max; i++)
		{
			if (!strcmp(in_pName, phantomMap[i].first))
				return phantomMap[i].second;
		}

		return static_cast<Game::EPhantomType>(-1);
	}

	animal::AnimalType AnimalTypeFromName(const char* in_pName)
	{
		for (size_t i = 0; i < animal::AnimalType::eAnimal_Max; i++)
		{
			if (!strcmp(in_pName, animalMap[i].first))
				return animalMap[i].second;
		}

		return static_cast<animal::AnimalType>(animal::AnimalType::eAnimal_Max + 1);
	}
}