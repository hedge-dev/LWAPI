#pragma once

namespace app::fnd
{
	class VariantDataUtil
	{
	public:
		static void* NewObject(const RflClass& in_rClass, csl::fnd::IAllocator* in_pAllocator)
		{
			return csl::fnd::Singleton<RflTypeInfoRegistry>::GetInstance()->ConstructObject(in_pAllocator, in_rClass.GetName());
		}
	};
}