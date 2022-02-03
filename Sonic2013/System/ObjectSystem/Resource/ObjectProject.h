#pragma once

namespace app::SetEd
{
	struct SResObjectProjectData
	{
		uint m_Signature;
		INSERT_PADDING(16);
		app::TArray<SResObjectData*, app::dbg::Allocator<SResObjectData*>> m_Objects;
	};
}