#pragma once

namespace app::game
{
	class PhysicsDebugDraw : public fnd::ReferencedObject
	{
	public:
		csl::ut::Bitset<uint> m_Flags{};
		csl::ut::MoveArray<ColliShape*> m_Shapes{ GetAllocator() };
		csl::ut::PointerMap<ColliShape*, uint> m_ShapeMap{ GetAllocator() };
	};
}