#pragma once

namespace app::animation
{
	class SkeletonBase : public fnd::ReferencedObject
	{
	public:
		hh::gfx::res::ResSkeleton Skeleton{};
		csl::ut::Bitset<uint> Flags{};
		INSERT_PADDING(8) {};
		csl::ut::MoveArray<csl::math::Matrix34> Unk1{ m_pAllocator };
		csl::ut::MoveArray<csl::math::Matrix34> Unk2{ m_pAllocator };
	};
}