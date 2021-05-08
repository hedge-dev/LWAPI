#pragma once

namespace app::fnd
{
	class VariantDataUtil
	{
	public:
		static void* NewObject(const RflClass& rClass, csl::fnd::IAllocator* pAllocator)
		{
			return csl::fnd::Singleton<RflTypeInfoRegistry>::GetInstance()->ConstructObject(pAllocator, rClass.GetName());
		}
	};
}