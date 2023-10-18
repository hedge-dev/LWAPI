#pragma once

namespace hh::gfx::res
{
	struct ResMorphTargetData;
	struct ResNodeData;

	struct ResMeshGroupData
	{
		ResMeshData* pMeshes{};
		uint MeshCount{};
		INSERT_PADDING(12) {};
		ResNameData Name{};
		INSERT_PADDING(8) {};
	};

	class ResMeshGroup : public ut::ResCommon<ResMeshGroupData>
	{
	public:
		const char* GetName()
		{
			return m_pRes->Name.m_pValue;
		}

		uint GetNumResMeshes() const
		{
			return m_pRes->MeshCount;
		}

		ResMesh GetResMesh(uint in_index) const
		{
			if (GetNumResMeshes() <= in_index)
				return { nullptr };

			return { &m_pRes->pMeshes[in_index] };
		}
	};

	struct ResModelData
	{
		ResMeshGroupData* pMeshGroups{};
		ResNodeData* pNodes{};
		ResMorphTargetData* pMorphTargets{};
		INSERT_PADDING(4);
		uint MeshGroupCount{};
		uint NodeCount{};
		uint MorphTargetCount{};
		INSERT_PADDING(8) {};
		ResNameData Name{};
		INSERT_PADDING(4) {}; // ResUserDataData UserData;
	};

	class ResModelBase : public ut::ResCommon<ResModelData>
	{
	public:
		const char* GetName()
		{
			return m_pRes->Name.m_pValue;
		}

		ResMeshGroup GetResMeshGroup(uint in_index) const
		{
			if (m_pRes->MeshGroupCount <= in_index)
				return { nullptr };
		
			return { &m_pRes->pMeshGroups[in_index] };
		}
	};

	class ResModel : public ResModelBase
	{
		inline static ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<ut::ResourceTypeInfo*>(ASLR(0x00FCE6B4));

	public:
		static const ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};
}