#pragma once

namespace app::fnd
{
	class Geometry
	{
	public:
		struct Triangle
		{
			uint v0;
			uint v1;
			uint v2;
		};

		csl::ut::MoveArray<csl::math::Vector3> m_Vertices;
		csl::ut::MoveArray<Triangle> m_Triangles;

		Geometry(csl::fnd::IAllocator* in_pAllocator) : m_Vertices(in_pAllocator), m_Triangles(in_pAllocator)
		{
			
		}
	};
}