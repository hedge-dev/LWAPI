#pragma once

namespace hh::gfx
{
	class GfxObject
	{
	public:
		uint ObjectType{ 1 };
		csl::fnd::IAllocator* pAllocator{};

		GfxObject(csl::fnd::IAllocator* in_pAllocator) : pAllocator(in_pAllocator)
		{
			
		}

		virtual void Destroy()
		{
			this->~GfxObject();
			if (pAllocator)
				pAllocator->Free(this);
		}

		virtual ~GfxObject() = default;

		[[nodiscard]] csl::fnd::IAllocator* GetAllocator() const
		{
			return pAllocator;
		}
	};
}