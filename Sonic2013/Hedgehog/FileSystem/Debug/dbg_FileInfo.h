#pragma once

namespace app::dbg
{
	class FileInfo
	{
	public:
		struct Data
		{
			csl::ut::FixedString<48> Name{};
			uint32_t Status{};
			void* pBuffer{};
			size_t Size{};
			INSERT_PADDING(8) {}; // ???
		};
	};
}