#pragma once

namespace hh::gfx
{
	class ResMorphTargetVtxWeight;
	class AnimMorphTargetNode : public AnimObject
	{
	public:
		DEFINE_RTTI_PTR(ASLR(0x00FCEAC8)) DEFINE_RTTI_GETTER;

		csl::ut::MoveArray<AnimMorphTargetNode*> nodes{};
		float speed{ 1 };

		AnimMorphTargetNode(csl::fnd::IAllocator* in_pAllocator) : AnimObject(in_pAllocator), nodes(in_pAllocator)
		{
			
		}

		virtual bool GetResult(size_t in_node, ResMorphTargetVtxWeight* in_pWeight) = 0;
	};
}