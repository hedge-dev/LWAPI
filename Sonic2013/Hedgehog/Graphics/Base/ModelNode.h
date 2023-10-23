#pragma once

namespace hh::gfx
{
	class NodeInstance
	{
	public:
		csl::ut::Bitset<uint> Flags{};
		INSERT_PADDING(88){};
	};

	class ModelNodeInstance
	{
	public:
		csl::ut::MoveArray<NodeInstance> Nodes{};
		res::ResModel Model{};
	};

	class ModelNode : public SceneNode
	{
	public:
		INSERT_PADDING(12) {};
		ModelNodeInstance* pInstance{};
		INSERT_PADDING(8) {};
		GfxObject* pGraphicsObjects[6]{};
		INSERT_PADDING(20) {};
		csl::math::Aabb m_Bounds{};

		ModelNode() = delete;

		const csl::math::Aabb& GetBounds() const
		{
			return m_Bounds;
		}

		void SetBounds(const csl::math::Aabb& in_bounds)
		{
			m_Bounds = in_bounds;
		}
	};
}