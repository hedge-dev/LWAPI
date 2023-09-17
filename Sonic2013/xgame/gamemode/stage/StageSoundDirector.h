#pragma once

namespace app::xgame
{
	class CStageSoundDirector : public GameObject
	{
		enum BGMCategoryType : char
		{

		};

		struct alignas(4) VolumeInfo
		{
			float Unk1{ 1.0f };
			float Unk2{};
			float Unk3{};
			float Unk4{};
			float Unk5{};
			bool Unk6{};
		};

		struct BGMInfo
		{
			fnd::SoundHandle Handle{};
			csl::ut::FixedString<32> Name{};
			int Unk1{};
			VolumeInfo Volume{};
			float Unk2{ -1.0f };
		};

	public:
		fnd::SoundPlayer* pSoundPlayer{};
		const CLevelInfo* pLevelInfo{};
		const StageInfo::SStageData* pStageData{};
		BGMInfo BGMs[5]{};
		csl::ut::Bitset<uint> Flags{};
		csl::ut::FixedString<32> Unk1{};
		csl::ut::FixedString<32> Unk2{};
		csl::ut::FixedString<32> Unk3{};
		StageSoundGuidePathControl PathControl{};
		BGMCoordinator Coordinator{};
		BGMParamCoordinator ParamCoordinator{};
		csl::ut::Enum<BGMCategoryType, char> Unk4{ (BGMCategoryType)-1 };
		csl::ut::Enum<BGMCategoryType, char> Unk5{ (BGMCategoryType)-1 };
		int Unk6{ -1 };
		fnd::SoundListenerHandle HandleListeners[5]{};

	private:
		inline static FUNCTION_PTR(CStageSoundDirector*, __thiscall, ms_fpCtor, ASLR(0x0095B160), CStageSoundDirector*, const StageInfo::SStageData*, const CLevelInfo*);
		inline static FUNCTION_PTR(CStageSoundDirector*, __thiscall, ms_fpDtor, ASLR(0x0095C4E0), CStageSoundDirector*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpInitPlayerGuidePathControl, ASLR(0x0095B680), CStageSoundDirector*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpMuteStageSE, ASLR(0x0095AD90), CStageSoundDirector*, bool);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpStopBGM, ASLR(0x0095AFB0), CStageSoundDirector*, float);

	public:
		CStageSoundDirector(const StageInfo::SStageData* in_pStageData, const CLevelInfo* in_pLevelInfo)
		{
			ms_fpCtor(this, in_pStageData, in_pLevelInfo);
		}

		~CStageSoundDirector() override
		{
			ms_fpDtor(this);
		}

		// Temporary, does not actually exist
		static CStageSoundDirector* Create(const StageInfo::SStageData* in_pStageData, const CLevelInfo* in_pLevelInfo)
		{
			void* mem = operator new(sizeof(CStageSoundDirector));
			return ms_fpCtor(static_cast<CStageSoundDirector*>(mem), in_pStageData, in_pLevelInfo);
		}

		/*CStageSoundDirector(const StageInfo::SStageData* in_pStageData, const CLevelInfo* in_pLevelInfo)
			: GameObject()
			, pLevelInfo(in_pLevelInfo)
			, pStageData(in_pStageData)
			, pSoundPlayer(csl::fnd::Singleton<fnd::SoundPlayer>::GetInstance())
		{
			SetObjectCategory(13);
		}*/

		void InitPlayerGuidePathControl()
		{
			ms_fpInitPlayerGuidePathControl(this);
		}

		void MuteStageSE(bool in_isEnable)
		{
			ms_fpMuteStageSE(this, in_isEnable);
		}

		void StopBGM(float in_time)
		{
			ms_fpStopBGM(this, in_time);
		}
	};
}