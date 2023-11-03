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
			eEventType_Start,
			eEventType_BaseData,
			eEventType_LevelData
		};

		virtual ~StageDataListener() = default;
		virtual void LoadStartingCallback(EventType in_event) {}
		virtual void LoadFinishedCallback(EventType in_event) {}
	};

	class StageDataInitializer : public fnd::ReferencedObject
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpUpdate, ASLR(0x009339F0), StageDataInitializer*);

	public:
		struct Cinfo
		{
			GameDocument* pDocument;
			StageInfo::SStageData* pStage;
		};

		enum StateType : char
		{
			eStateType_None,
			eStateType_BeginLoad,
			eStateType_LoadingBaseData,
			eStateType_LoadingLevelData,
			eStateType_LoadingTerrainData,
			eStateType_LoadFinished,
		};

		StageInfo::SStageData* pStage{};
		GameDocument* pDocument{};
		StageDataListener* pListener{};
		csl::ut::Enum<StateType, char> State{};
		csl::ut::FixedString<64> StageName{};
		csl::ut::FixedString<64> StageDirectory{};
		csl::ut::FixedString<64> DataDirectory{};
		TerrainManager* pTerrainMan{};
		CSetObjectManager* pSetObjMan{};
		xgame::SceneParameters* pSceneParams{};
		float DeadLine{ -100 };
		float NearClipPlane{ 1 };
		float FarClipPlane{ 10000 };
		float Fov{ 45 };

		StageDataInitializer(const Cinfo& in_info) :
			m_pStage(in_info.pStage), m_pDocument(in_info.pDocument),
			m_StageName(pStage->Name),
			m_StageDirectory(pStage->Directory),
			m_DataDirectory(findFileName(StageDirectory)),
			m_pTerrainMan(pDocument->GetService<TerrainManager>()),
			m_pSetObjMan(pDocument->GetService<CSetObjectManager>()),
			m_pSceneParams(pDocument->GetService<xgame::SceneParameters>()) {  }

		void BeginLoad()
		{
			State = eStateType_BeginLoad;
			NotifyLoadStarting(StageDataListener::eEventType_Start);
		}

		void NotifyLoadStarting(StageDataListener::EventType in_event) const
		{
			if (pListener)
				pListener->LoadStartingCallback(in_event);
		}

		[[nodiscard]] bool IsLoadFinished() const
		{
			return State == eStateType_LoadFinished;
		}

		void Update()
		{
			ms_fpUpdate(this);
		}
	};
}