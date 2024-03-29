#pragma once

namespace hh::gfx
{
	class AnimMorphTargetControl : public AnimMorphTargetNode
	{
	private:
		inline static FUNCTION_PTR(AnimMorphTargetControl*, __cdecl, ms_fpCreate, ASLR(0x00C06BB0), csl::fnd::IAllocator*, hh::gfx::res::ResAnimMorphTarget);

	public:
		DEFINE_RTTI_PTR(ASLR(0x00FCE158)) DEFINE_RTTI_GETTER;

		INSERT_PADDING(8) {};
		float Speed{ 1 };
		hh::gfx::res::ResAnimMorphTarget Resource{};

		inline static AnimMorphTargetControl* Create(csl::fnd::IAllocator* in_pAllocator, hh::gfx::res::ResAnimMorphTarget in_resource)
		{
			return ms_fpCreate(in_pAllocator, in_resource);
		}
	};
}