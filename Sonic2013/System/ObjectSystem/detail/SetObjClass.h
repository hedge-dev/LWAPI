#pragma once

namespace app
{
	enum ESetObjectSpawnType
	{
		eSetObjectSpawnType_Default = 0
	};
	
	class CObjInfo;
	class CSetObjectListener;

	class CSetObjClass
	{
	public:
		typedef CSetObjectListener* CreateObject_t();
		typedef CObjInfo* CreateInfo_t(csl::fnd::IAllocator* in_pAllocator);
		typedef void SetupParamMap_t(app::SetEd::CResClass in_rClass);

		const char* pName{};
		const char* pType{};
		CreateObject_t* fpCreateObject{};
		CreateInfo_t* fpCreateInfo{};
		SetupParamMap_t* fpSetupParamMap{};
		const fnd::GOComponentClass** ppComponents{};
		uint Unk1{};
		float DefaultRangeOut{};
		float DefaultRangeIn{};
		csl::ut::Enum<ESetObjectSpawnType, char> SpawnType{};
		const char* pCategory{};

	public:

		template<class T>
		inline static CSetObjectListener* ObjectCreator()
		{
			return new T();
		}

		template<class T>
		inline static CObjInfo* InfoCreator(csl::fnd::IAllocator* in_pAllocator)
		{
			return new(in_pAllocator) T();
		}

		CSetObjClass()
		{

		}
		
		CSetObjClass(const char* in_pName, const char* in_pType, const char* in_pCategory, CreateObject_t in_fpCreateObject, CreateInfo_t* in_fpCreateInfo, SetupParamMap_t* in_fpSetupParamMap, const fnd::GOComponentClass** in_ppComponents, float in_defaultRangeOut, float in_defaultRangeIn, ESetObjectSpawnType in_spawnType)
		{
			pName = in_pName;
			pType = in_pType;
			pCategory = in_pCategory;
			fpCreateObject = in_fpCreateObject;
			fpCreateInfo = in_fpCreateInfo;
			fpSetupParamMap = in_fpSetupParamMap;
			ppComponents = in_ppComponents;
			DefaultRangeIn = in_defaultRangeIn;
			DefaultRangeOut = in_defaultRangeOut;
			SpawnType = in_spawnType;
		}

		template<typename TObject, typename TInfo>
		inline static CSetObjClass Create(const char* in_pName, const char* in_pType, const char* in_pCategory, SetupParamMap_t* in_fpSetupParamMap = nullptr, const fnd::GOComponentClass** in_ppComponents = nullptr, float in_defaultRangeOut = 1200, float in_defaultRangeIn = 1000, ESetObjectSpawnType in_spawnType = eSetObjectSpawnType_Default)
		{
			CSetObjClass info{};

			info.pName = in_pName;
			info.pType = in_pType;
			info.pCategory = in_pCategory;
			info.fpCreateObject = ObjectCreator<TObject>;
			info.fpCreateInfo = InfoCreator<TInfo>;
			info.fpSetupParamMap = in_fpSetupParamMap;
			info.ppComponents = in_ppComponents;
			info.DefaultRangeIn = in_defaultRangeIn;
			info.DefaultRangeOut = in_defaultRangeOut;
			info.SpawnType = in_spawnType;
			return info;
		}

		template<typename TObject>
		inline static CSetObjClass Create(const char* in_pName, const char* in_pType, const char* in_pCategory, CreateInfo_t* in_fpCreateInfo = nullptr, SetupParamMap_t* in_fpSetupParamMap = nullptr, const fnd::GOComponentClass** in_ppComponents = nullptr, float in_defaultRangeOut = 1200, float in_defaultRangeIn = 1000, ESetObjectSpawnType in_spawnType = eSetObjectSpawnType_Default)
		{
			CSetObjClass info{};
			info.pName = in_pName;
			info.pType = in_pType;
			info.pCategory = in_pCategory;
			info.fpCreateObject = ObjectCreator<TObject>;
			info.fpCreateInfo = in_fpCreateInfo;
			info.fpSetupParamMap = in_fpSetupParamMap;
			info.ppComponents = in_ppComponents;
			info.DefaultRangeIn = in_defaultRangeIn;
			info.DefaultRangeOut = in_defaultRangeOut;
			info.SpawnType = in_spawnType;
			return info;
		}

		inline static CSetObjClass Create(const char* in_pName, const char* in_pType, const char* in_pCategory, CreateObject_t in_fpCreateObject, CreateInfo_t* in_fpCreateInfo, SetupParamMap_t* in_fpSetupParamMap = nullptr, const fnd::GOComponentClass** in_ppComponents = nullptr, float in_defaultRangeOut = 1200, float in_defaultRangeIn = 1000, ESetObjectSpawnType in_spawnType = eSetObjectSpawnType_Default)
		{
			CSetObjClass info{};
			info.pName = in_pName;
			info.pType = in_pType;
			info.pCategory = in_pCategory;
			info.fpCreateObject = in_fpCreateObject;
			info.fpCreateInfo = in_fpCreateInfo;
			info.fpSetupParamMap = in_fpSetupParamMap;
			info.ppComponents = in_ppComponents;
			info.DefaultRangeIn = in_defaultRangeIn;
			info.DefaultRangeOut = in_defaultRangeOut;
			info.SpawnType = in_spawnType;
			return info;
		}

		CObjInfo* CreateInfo(csl::fnd::IAllocator* in_pAllocator) const
		{
			if (!fpCreateInfo)
				return nullptr;

			return fpCreateInfo(in_pAllocator);
		}

		void SetupParamMap(app::SetEd::CResClass in_rClass) const
		{
			if (!fpSetupParamMap)
				return;

			fpSetupParamMap(in_rClass);
		}
	};
}