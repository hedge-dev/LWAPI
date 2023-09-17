#pragma once

namespace app
{
	class SnowBallTrackManager : public fnd::GameService
	{
	public:
		struct ResInfo
		{
			csl::ut::FixedString<32> StagePackName{};
			csl::ut::FixedString<32> SnowlineName{};
		};

		INSERT_PADDING(8);
		
	private:
		inline static fnd::GameServiceClass* ms_pStaticClass = reinterpret_cast<fnd::GameServiceClass*>(ASLR(0x00FEFD04));
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetupResources, ASLR(0x00909CA0), SnowBallTrackManager*, const ResInfo&);

	public:
		static fnd::GameServiceClass& staticClass()
		{
			return *ms_pStaticClass;
		}

		SnowBallTrackManager() : fnd::GameService(0)
		{

		}

		void SetupResources(const ResInfo& in_rResourceInfo)
		{
			ms_fpSetupResources(this, in_rResourceInfo);
		}
	};
}