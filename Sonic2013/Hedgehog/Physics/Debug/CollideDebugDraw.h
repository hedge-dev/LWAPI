#pragma once

namespace app::game
{
	class CollideDebugDraw : public fnd::ReferencedObject
	{
	public:
		csl::ut::MoveArray<ColliShape*> Shapes{ GetAllocator() };
	};
}