#pragma once

namespace app::SetEd
{
	class CResource : public fnd::ReferencedObject
	{
	public:
		csl::ut::ObjectMoveArray<app::ut::RefPtr<CClassProject>> m_ClassProjects{ GetAllocator() };
		csl::ut::ObjectMoveArray<app::ut::RefPtr<CObjectProject>> m_ObjectProjects{ GetAllocator() };

		CResClass FindClass(const char* pName) const
		{
			if (!m_ClassProjects.size())
				return {};

			for (auto& pProject : m_ClassProjects)
			{
				auto result = pProject->FindClass(pName);
				if (!result.IsValid())
					continue;

				return result;
			}

			return {};
		}
	};
}