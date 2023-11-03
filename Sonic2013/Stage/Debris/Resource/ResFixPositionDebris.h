#pragma once

namespace app::debris
{
	class ResFixPositionDebris
	{
	public:
		struct SDesc
		{
			const char* pSkeletonName{};
			hh::ut::PackFile* pPackFile{};
		};

		struct SModelData
		{
			INSERT_PADDING(16);
		};

	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpBuild, ASLR(0x008477B0), ResFixPositionDebris*, SDesc&);

	public:
		csl::ut::ObjectMoveArray<SModelData> Models{};

		ResFixPositionDebris(csl::fnd::IAllocator* in_pAllocator) : Models(in_pAllocator)
		{

		}

		ResFixPositionDebris() : Models(game::GlobalAllocator::GetAllocator(2))
		{

		}

		void Build(SDesc& in_rDescription)
		{
			ms_fpBuild(this, in_rDescription);
		}
	};
}