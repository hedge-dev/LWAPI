#pragma once

namespace app::SetEd
{
	class CResource : public fnd::ReferencedObject
	{
	public:
		csl::ut::ObjectMoveArray<app::ut::RefPtr<CClassProject>> ClassProjects{ GetAllocator() };
		csl::ut::ObjectMoveArray<app::ut::RefPtr<CObjectProject>> ObjectProjects{ GetAllocator() };

		CResClass FindClass(const char* in_pName) const
		{
			if (!ClassProjects.size())
				return {};

			for (auto& pProject : ClassProjects)
			{	
				auto result = pProject->FindClass(in_pName);
				if (!result.IsValid())
					continue;

				return result;
			}

			return {};
		}

		CObjectProject* GetObjectProject(size_t in_index) const
		{
			if (in_index < ObjectProjects.size())
				return ObjectProjects[in_index].get();

			return { nullptr };
		}
	};
}