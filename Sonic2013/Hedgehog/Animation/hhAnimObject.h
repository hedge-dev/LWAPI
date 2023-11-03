#pragma once

namespace hh::gfx
{
	class AnimObject : public hh::gfx::GfxObject
	{
	public:
		DEFINE_RTTI_PTR(ASLR(0x011D6DC4)) DEFINE_RTTI_GETTER;

		uint Flags{};

		AnimObject(csl::fnd::IAllocator* in_pAllocator) : GfxObject(in_pAllocator)
		{
			
		}

		virtual void UpdateFrame(float in_delta) = 0;
		virtual void SetGlobalFrame(float in_frame) = 0;
	};
}