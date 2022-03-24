#pragma once

namespace hh::gfx
{
	class ModelNode : public SceneNode
	{
	public:
		INSERT_PADDING(68) {};
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