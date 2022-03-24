#pragma once

namespace hh::gfx
{
	class GfxObject
	{
	public:
		uint m_ObjectType{ 1 };
		csl::fnd::IAllocator* m_pAllocator{};

		GfxObject(csl::fnd::IAllocator* in_pAllocator) : m_pAllocator(in_pAllocator)
		{
			
		}

		virtual void Destroy()
		{
			this->~GfxObject();
			if (m_pAllocator)
				m_pAllocator->Free(this);
		}

		virtual ~GfxObject() = default;

		[[nodiscard]] csl::fnd::IAllocator* GetAllocator() const
		{
			return m_pAllocator;
		}
	};
}