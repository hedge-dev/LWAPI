#pragma once

namespace hh::gfx
{
	class AnimObject;

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
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpSetAnimObject, ASLR(0x00C005E0), ModelNode*, AnimObject*, uint);
		
	public:
		INSERT_PADDING(12) {};
		ModelNodeInstance* pInstance{};
		INSERT_PADDING(8) {};
		csl::ut::FixedArray<AnimObject*, 6> AnimationObjects{};
		INSERT_PADDING(20) {};
		csl::math::Aabb Bounds{};

		ModelNode() = delete;

		void SetAnimObject(AnimObject* in_pObject, uint in_type)
		{
			if (in_type < AnimationObjects.size())
			{
				AnimationObjects[in_type] = in_pObject;
			}
			else
			{
				// There's too many casts for us to implement here,
				// Maybe implement it fully when we have all the types
				ms_fpSetAnimObject(this, in_pObject, in_type);
			}
		}

		const csl::math::Aabb& GetBounds() const
		{
			return Bounds;
		}

		void SetBounds(const csl::math::Aabb& in_rBounds)
		{
			Bounds = in_rBounds;
		}
	};
}
