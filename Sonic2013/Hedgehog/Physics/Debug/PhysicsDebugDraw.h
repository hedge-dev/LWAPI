#pragma once

namespace app::game
{
	class PhysicsDebugDraw : public fnd::ReferencedObject
	{
	public:
		csl::ut::Bitset<uint> Flags{};
		csl::ut::MoveArray<ColliShape*> Shapes{ GetAllocator() };
		csl::ut::PointerMap<ColliShape*, uint> ShapeMap{ GetAllocator() };
	};
}