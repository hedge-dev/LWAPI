#pragma once

namespace app::fnd
{
	class Geometry
	{
	public:
		struct Triangle
		{
			uint V0;
			uint V1;
			uint V2;
		};

		csl::ut::MoveArray<csl::math::Vector3> Vertices;
		csl::ut::MoveArray<Triangle> Triangles;

		Geometry(csl::fnd::IAllocator* in_pAllocator) : Vertices(in_pAllocator), Triangles(in_pAllocator)
		{
			
		}
	};
}