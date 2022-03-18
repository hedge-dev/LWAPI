#pragma once

namespace app::fnd
{
	class Geometry;
}

namespace app::game
{
	class ColliMeshShapeBase : public ColliShape
	{
	public:
		ResPhysicsMesh m_Mesh{};

		virtual bool GetGeometry(csl::ut::MoveArray<fnd::Geometry*>& out_geometries, csl::fnd::IAllocator* in_pAllocator) = 0;
		virtual void SetSubpartEnabled(int in_id, bool in_option) { }
		virtual int GetSubpartId(const char* in_pName) const { return -1; }
		virtual int GetSubpartIdForShapeKey(uint in_key) const { return -1; }
	};

	class ColliMeshShapeCInfo : public ColliShapeCInfo
	{
	public:
		ResPhysicsMesh m_Mesh{};

		ColliMeshShapeCInfo() : ColliShapeCInfo(CollisionShapeType::ShapeType::ShapeType_Mesh)
		{

		}
	};
}