#pragma once

namespace app::SetEd
{
	struct SResObjectProjectData
	{
		uint Signature;
		uint Version; // Always 1
		INSERT_PADDING(12);
		app::TArray<SResObjectData*, app::dbg::Allocator<SResObjectData*>> Objects;
	};
}