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
		typedef CObjInfo* CreateInfo_t(csl::fnd::IAllocator* pAllocator);
		typedef void SetupParamMap_t(app::SetEd::CResClass rClass);

		const char* m_pName{};
		const char* m_pType{};
		CreateObject_t* m_fpCreateObject{};
		CreateInfo_t* m_fpCreateInfo{};
		SetupParamMap_t* m_fpSetupParamMap{};
		const fnd::GOComponentClass** m_ppComponents{};
		uint m_Unk1{};
		float m_DefaultRangeOut{};
		float m_DefaultRangeIn{};
		csl::ut::Enum<ESetObjectSpawnType, char> m_SpawnType{};
		const char* m_pCategory{};

	public:

		template<class T>
		inline static CSetObjectListener* ObjectCreator()
		{
			return new T();
		}

		template<class T>
		inline static CObjInfo* InfoCreator(csl::fnd::IAllocator* pAllocator)
		{
			return new(pAllocator) T();
		}

		CSetObjClass()
		{

		}
		
		CSetObjClass(const char* pName, const char* pType, const char* pCategory, CreateObject_t fpCreateObject, CreateInfo_t* fpCreateInfo, SetupParamMap_t* fpSetupParamMap, const fnd::GOComponentClass** ppComponents, float defaultRangeOut, float defaultRangeIn, ESetObjectSpawnType spawnType)
		{
			m_pName = pName;
			m_pType = pType;
			m_pCategory = pCategory;
			m_fpCreateObject = fpCreateObject;
			m_fpCreateInfo = fpCreateInfo;
			m_fpSetupParamMap = fpSetupParamMap;
			m_ppComponents = ppComponents;
			m_DefaultRangeIn = defaultRangeIn;
			m_DefaultRangeOut = defaultRangeOut;
			m_SpawnType = spawnType;
		}

		template<typename TObject, typename TInfo>
		inline static CSetObjClass Create(const char* pName, const char* pType, const char* pCategory, SetupParamMap_t* fpSetupParamMap = nullptr, const fnd::GOComponentClass** ppComponents = nullptr, float defaultRangeOut = 1200, float defaultRangeIn = 1000, ESetObjectSpawnType spawnType = eSetObjectSpawnType_Default)
		{
			CSetObjClass info{};

			info.m_pName = pName;
			info.m_pType = pType;
			info.m_pCategory = pCategory;
			info.m_fpCreateObject = ObjectCreator<TObject>;
			info.m_fpCreateInfo = InfoCreator<TInfo>;
			info.m_fpSetupParamMap = fpSetupParamMap;
			info.m_ppComponents = ppComponents;
			info.m_DefaultRangeIn = defaultRangeIn;
			info.m_DefaultRangeOut = defaultRangeOut;
			info.m_SpawnType = spawnType;
			return info;
		}

		template<typename TObject>
		inline static CSetObjClass Create(const char* pName, const char* pType, const char* pCategory, CreateInfo_t* fpCreateInfo = nullptr, SetupParamMap_t* fpSetupParamMap = nullptr, const fnd::GOComponentClass** ppComponents = nullptr, float defaultRangeOut = 1200, float defaultRangeIn = 1000, ESetObjectSpawnType spawnType = eSetObjectSpawnType_Default)
		{
			CSetObjClass info{};
			info.m_pName = pName;
			info.m_pType = pType;
			info.m_pCategory = pCategory;
			info.m_fpCreateObject = ObjectCreator<TObject>;
			info.m_fpCreateInfo = fpCreateInfo;
			info.m_fpSetupParamMap = fpSetupParamMap;
			info.m_ppComponents = ppComponents;
			info.m_DefaultRangeIn = defaultRangeIn;
			info.m_DefaultRangeOut = defaultRangeOut;
			info.m_SpawnType = spawnType;
			return info;
		}

		CObjInfo* CreateInfo(csl::fnd::IAllocator* pAllocator) const
		{
			if (!m_fpCreateInfo)
				return nullptr;

			return m_fpCreateInfo(pAllocator);
		}

		void SetupParamMap(app::SetEd::CResClass rClass) const
		{
			if (!m_fpSetupParamMap)
				return;

			m_fpSetupParamMap(rClass);
		}
	};
}