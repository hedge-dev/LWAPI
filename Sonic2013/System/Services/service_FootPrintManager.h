#pragma once

namespace app
{
	struct ResInfo
	{
		csl::ut::FixedString<32> PackName{};
		csl::ut::FixedString<32> TextureNames[2]{};
	};

	class FootPrintManager : fnd::GameService
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetupResources, ASLR(0x009029C0), FootPrintManager*, const ResInfo&);
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEFC74));

	public:
		csl::fnd::IAllocator* pAllocator{ game::GlobalAllocator::GetAllocator(2) };
		INSERT_PADDING(4); // app::FootPrintManager::Implement

	public:
		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}

		void SetupResources(const ResInfo& in_rInfo)
		{
			ms_fpSetupResources(this, in_rInfo);
		}
	};
}