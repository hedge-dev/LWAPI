#pragma once

namespace app::SetEd
{
	struct SResClassProjectData
	{
		INSERT_PADDING(8);
		app::TArray<SResClassData*, std::dummy::allocator<SResClassData*>> m_Classes{};
	};
}