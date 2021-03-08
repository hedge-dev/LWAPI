#pragma once

namespace app::StageInfo
{
	class CStageInfo
	{
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
		csl::ut::MoveArray<const char*> m_Unk1{ m_pAllocator }; // Levels?

		[[nodiscard]] static CStageInfo* GetInstance()
		{
			return *ms_ppInstance;
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
	};
}