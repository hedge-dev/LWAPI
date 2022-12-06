#pragma once

namespace app::SetEd
{
	struct SResObjectProjectData
	{
		uint m_Signature;
		uint m_Version; // Always 1
		INSERT_PADDING(12);
		app::TArray<SResObjectData*, app::dbg::Allocator<SResObjectData*>> m_Objects;
	};
}