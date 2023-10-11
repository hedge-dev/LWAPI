#pragma once

namespace app::StageInfo
{
	static std::pair<const char*, Game::EPhantomType> phantomMap[Game::EPhantomType::PHANTOM_MAX] =
	{
		{ "drill",		Game::EPhantomType::PHANTOM_DRILL },
		{ "laser",		Game::EPhantomType::PHANTOM_LASER },
		{ "rocket",		Game::EPhantomType::PHANTOM_ROCKET },
		{ "eagle",		Game::EPhantomType::PHANTOM_EAGLE },
		{ "asteroid",	Game::EPhantomType::PHANTOM_ASTEROID },
		{ "rhythm",		Game::EPhantomType::PHANTOM_RHYTHM },
		{ "bomb",		Game::EPhantomType::PHANTOM_BOMB },
		{ "hover",		Game::EPhantomType::PHANTOM_HOVER },
		{ "quake",		Game::EPhantomType::PHANTOM_QUAKE }
	};
	
	static std::pair<const char*, animal::AnimalType> animalMap[animal::AnimalType::ANIMAL_MAX] =
	{
		{ "FLICKIE",	animal::AnimalType::ANIMAL_FLICKIE },
		{ "COOKIE",		animal::AnimalType::ANIMAL_COOKIE },
		{ "PECKIE",		animal::AnimalType::ANIMAL_PECKIE },
		{ "PICKIE",		animal::AnimalType::ANIMAL_PICKIE },
		{ "POCKY",		animal::AnimalType::ANIMAL_POCKY },
		{ "RICKY",		animal::AnimalType::ANIMAL_RICKY },
		{ "ROCKY",		animal::AnimalType::ANIMAL_ROCKY },
	};

	static Game::EPhantomType PhantomTypeFromName(const char* in_pName);
	static animal::AnimalType AnimalTypeFromName(const char* in_pName);

	class CStageInfo
	{
	private:
		inline static FUNCTION_PTR(int, __thiscall, ms_fpGetAdvStageIndex, ASLR(0x00912C30), CStageInfo*, int, int);

	public:
		inline static CStageInfo** ms_ppInstance = reinterpret_cast<CStageInfo**>(ASLR(0x00FEFD38));

		struct SZoneInfo
		{
			uint m_Unk1{};
			uint m_Unk2{};

			csl::ut::FixedString<16> m_Missions[5];
		};

		csl::fnd::IAllocator* m_pAllocator{};
		csl::ut::ObjectMoveArray<SStageData*> m_Stages{ m_pAllocator };
		csl::ut::ObjectMoveArray<WorldNode*> m_Worlds[2];
		SZoneInfo m_Zones[19];
		csl::ut::MoveArray<const char*> StageNames{ m_pAllocator };

		[[nodiscard]] static CStageInfo* GetInstance()
		{
			return *ms_ppInstance;
		}

		SStageData* GetStageData(const char* in_pName) const
		{
			for (auto& pData : m_Stages)
			{
				if (pData->m_Name == in_pName)
					return pData;
			}

			return nullptr;
		}

		static void ReadMission_Mission(const char* in_pCat, game::LuaScript& in_rScript, void* in_pCtx)
		{
			auto* pStageData = new(static_cast<CStageInfo*>(in_pCtx)->m_pAllocator) StageInfo::SStageData();
			const char* pString{};

			if (!in_rScript.GetString("name", pString))
				return;
		
			pStageData->m_Name = pString;

			if (in_rScript.GetString("dir", pString))
				pStageData->m_Directory = pString;
			else
				pStageData->m_Directory = pStageData->m_Name;

			if (in_rScript.GetString("path_data", pString))
				pStageData->m_PathData = pString;
			else
				pStageData->m_PathData = pStageData->m_Directory;
		
			if (!in_rScript.GetVector3("player_pos", pStageData->m_PlayerPositions[0]))
				pStageData->m_PlayerPositions[0] = { 0.0f, 0.0f, 0.0f };

			csl::math::Vector3 direction{};
			if (in_rScript.GetVector3("player_dir", direction))
			{
				pStageData->m_PlayerRotations[0].x() = direction.x() * MATHF_PI / 180.0f;
				pStageData->m_PlayerRotations[0].y() = direction.y() * MATHF_PI / 180.0f;
				pStageData->m_PlayerRotations[0].z() = direction.z() * MATHF_PI / 180.0f;
			}

			if (!in_rScript.GetVector3("player2_pos", pStageData->m_PlayerPositions[1]))
			{
				pStageData->m_PlayerPositions[1] = pStageData->m_PlayerPositions[0];
			}

			if (in_rScript.GetVector3("player2_dir", direction))
			{
				pStageData->m_PlayerRotations[1].x() = direction.x() * MATHF_PI / 180.0f;
				pStageData->m_PlayerRotations[1].y() = direction.y() * MATHF_PI / 180.0f;
				pStageData->m_PlayerRotations[1].z() = direction.z() * MATHF_PI / 180.0f;
			}
			else
			{
				pStageData->m_PlayerRotations[1] = pStageData->m_PlayerRotations[0];
			}

			if (in_rScript.GetString("bgm", pString))
				pStageData->m_Bgm = pString;

			if (in_rScript.GetString("bgm_sv", pString))
				pStageData->m_BgmSv = pString;

			if (in_rScript.GetString("amb", pString))
				pStageData->m_Amb = pString;

			if (in_rScript.GetString("amb_in", pString))
				pStageData->m_AmbIn = pString;

			in_rScript.GetFloat("reverb", pStageData->m_Reverb);

			if (in_rScript.GetString("player_mode", pString))
			{
				if (!strcmp(pString, "2D"))
					pStageData->m_PlayerFlags.set(0);
				else if (!strcmp(pString, "WATER"))
					pStageData->m_PlayerFlags.set(1);
				else if (!strcmp(pString, "SKYCHASE"))
					pStageData->m_PlayerFlags.set(2);
				else if (!strcmp(pString, "TOP"))
					pStageData->m_PlayerFlags.set(3);
				else if (!strcmp(pString, "SNOWBALL"))
					pStageData->m_PlayerFlags.set(4);
			}
			
			ut::InplaceTempArray<const char*, 10> stageAttrs{};
			if (in_rScript.GetStringArray("attrs", stageAttrs))
			{
				for (size_t i = 0; i < stageAttrs.size(); i++)
				{
					if (!strcmp(stageAttrs[i], "no_redring"))
						pStageData->m_StageFlags.set(2, true);

					if (!strcmp(stageAttrs[i], "only_normalplay"))
					{
						pStageData->m_StageFlags.set(3, true);
						pStageData->m_StageFlags.set(4, true);
					}

					if (!strcmp(stageAttrs[i], "bakubaku"))
						pStageData->m_StageFlags.set(5, true);

					if (!strcmp(stageAttrs[i], "floor_reflect"))
						pStageData->m_StageFlags.set(6, true);

					if (!strcmp(stageAttrs[i], "randombox_noquake"))
						pStageData->m_StageFlags.set(7, true);

					if (!strcmp(stageAttrs[i], "no_bomb"))
						pStageData->m_StageFlags.set(8, true);

					if (!strcmp(stageAttrs[i], "lastboss"))
						pStageData->m_StageFlags.set(9, true);

					if (!strcmp(stageAttrs[i], "dlc"))
					{
						pStageData->m_StageFlags.set(3, true);
						pStageData->m_StageFlags.set(10, true);
					}

					if (!strcmp(stageAttrs[i], "yoshiisland"))
						pStageData->m_StageFlags.set(11, true);

					if (!strcmp(stageAttrs[i], "zelda"))
						pStageData->m_StageFlags.set(12, true);
				}
			}

			if (strstr(pStageData->m_Name.c_str(), "mini"))
				pStageData->m_StageFlags.set(0, true);
			else if (strstr(pStageData->m_Name.c_str(), "batl"))
				pStageData->m_StageFlags.set(1, true);

			ut::InplaceTempArray<const char*, Game::EPhantomType::PHANTOM_MAX> phantoms{};
			if (in_rScript.GetStringArray("phantoms", phantoms))
			{
				for (size_t i = 0; i < phantoms.size(); i++)
				{
					Game::EPhantomType type = PhantomTypeFromName(phantoms[i]);
					if (type != static_cast<Game::EPhantomType>(-1))
						pStageData->m_Phantoms.push_back_unchecked(type);
				}
			}

			if (pStageData->m_StageFlags.test(1))
				pStageData->m_Phantoms.push_back_unchecked(Game::EPhantomType::PHANTOM_QUAKE);
			else if (!pStageData->m_StageFlags.test(0) && !pStageData->m_StageFlags.test(1) && !pStageData->m_StageFlags.test(8))
				pStageData->m_Phantoms.push_back_unchecked(Game::EPhantomType::PHANTOM_BOMB);

			if (in_rScript.OpenNode("time"))
			{
				in_rScript.GetFloat("time_limit", pStageData->m_TimeData.m_Limit);
				ut::InplaceTempArray<float, 4> times{};
				if (in_rScript.GetFloatArray("rank", times))
				{
					for (size_t i = 0; i < times.size(); i++)
						pStageData->m_TimeData.m_RankIntervals[i] = times[i];
				}

				in_rScript.CloseNode();
			}

			ut::InplaceTempArray<const char*, 3> animals{};
			if (in_rScript.GetStringArray("animals", animals))
			{
				for (size_t i = 0; i < animals.size(); i++)
					pStageData->m_Animals.push_back_unchecked(AnimalTypeFromName(animals[i]));
			}

			if (!in_rScript.GetInt("unlock_animals", pStageData->m_RequiredAnimals))
				pStageData->m_RequiredAnimals = 0;

			if (in_rScript.GetString("clear_cond", pString))
			{
				if (!strcmp(pString, "goal"))
					pStageData->m_ClearCondition = StageInfo::SStageData::ClearCondition::CONDITION_GOAL;
				else if (!strcmp(pString, "timeout"))
					pStageData->m_ClearCondition = StageInfo::SStageData::ClearCondition::CONDITION_TIMEOUT;
			}

			if (!in_rScript.GetFloat("eagle_altitude", pStageData->m_EagleAltitude))
				pStageData->m_EagleAltitude = 20.0f;

			static_cast<CStageInfo*>(in_pCtx)->m_Stages.push_back(pStageData);
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
							stage.m_Name = name;
							stage.m_Title = title;

							world->AddNode(stage);
						}, world);

					pWorlds->push_back(world);

				}, &m_Worlds[worldIdx]);
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
		for (size_t i = 0; i < Game::EPhantomType::PHANTOM_MAX; i++)
		{
			if (!strcmp(in_pName, phantomMap[i].first))
				return phantomMap[i].second;
		}

		return static_cast<Game::EPhantomType>(-1);
	}

	animal::AnimalType AnimalTypeFromName(const char* in_pName)
	{
		for (size_t i = 0; i < animal::AnimalType::ANIMAL_MAX; i++)
		{
			if (!strcmp(in_pName, animalMap[i].first))
				return animalMap[i].second;
		}

		return static_cast<animal::AnimalType>(animal::AnimalType::ANIMAL_MAX + 1);
	}
}