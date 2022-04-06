#pragma once

namespace app
{
	namespace fnd
	{
		class TerrainParam;
	}

	class TerrainManager : public fnd::GameService
	{
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEFD9C));

	public:
		INSERT_PADDING(16){}; // ObjectMoveArray<intrusive_ptr<TerrainBase>>
		fnd::TerrainParam* m_pParam{};
		uint m_Unk2{};

		TerrainManager() : GameService(0)
		{

		}

		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}
	};
}