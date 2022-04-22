#pragma once

namespace app
{
	inline static const char* findFileName(const char* in_pName)
	{
		if (const auto* pName = strchr(in_pName, '/'))
			return pName + 1;

		return in_pName;
	}

	class TerrainManager;

	class StageDataListener
	{
	public:
		enum EventType
		{
			EventType_Start,
			EventType_BaseData,
			EventType_LevelData
		};
		virtual ~StageDataListener() = default;
		virtual void LoadStartingCallback(EventType in_event) {}
		virtual void LoadFinishedCallback(EventType in_event) {}
	};

	class StageDataInitializer : public fnd::ReferencedObject
	{
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x009339F0), StageDataInitializer*);
		struct Cinfo
		{
			GameDocument* m_pDocument;
			StageInfo::SStageData* m_pStage;
		};

		enum StateType : char
		{
			StateType_None,
			StateType_BeginLoad,
			StateType_LoadingBaseData,
			StateType_LoadingLevelData,
			StateType_LoadingTerrainData,
			StateType_LoadFinished,
		};

		StageInfo::SStageData* m_pStage{};
		GameDocument* m_pDocument{};
		StageDataListener* m_pListener{};
		csl::ut::Enum<StateType, char> m_State{};
		csl::ut::FixedString<64> m_StageName{};
		csl::ut::FixedString<64> m_StageDirectory{};
		csl::ut::FixedString<64> m_DataDirectory{};
		TerrainManager* m_pTerrainMan{};
		CSetObjectManager* m_pSetObjMan{};
		xgame::SceneParameters* m_pSceneParams{};
		float m_DeadLine{ -100 };
		float m_NearClipPlane{ 1 };
		float m_FarClipPlane{ 10000 };
		float m_Fov{ 45 };

		StageDataInitializer(const Cinfo& in_info) :
			m_pStage(in_info.m_pStage), m_pDocument(in_info.m_pDocument),
			m_StageName(m_pStage->m_Name),
			m_StageDirectory(m_pStage->m_Directory),
			m_DataDirectory(findFileName(m_StageDirectory)),
			m_pTerrainMan(m_pDocument->GetService<TerrainManager>()),
			m_pSetObjMan(m_pDocument->GetService<CSetObjectManager>()),
			m_pSceneParams(m_pDocument->GetService<xgame::SceneParameters>()) {  }

		void BeginLoad()
		{
			m_State = StateType_BeginLoad;
			NotifyLoadStarting(StageDataListener::EventType_Start);
		}

		void NotifyLoadStarting(StageDataListener::EventType in_event) const
		{
			if (m_pListener)
				m_pListener->LoadStartingCallback(in_event);
		}

		[[nodiscard]] bool IsLoadFinished() const
		{
			return m_State == StateType_LoadFinished;
		}

		void Update()
		{
			ms_fpUpdate(this);
		}
	};
}