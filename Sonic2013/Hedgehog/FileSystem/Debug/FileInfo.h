#pragma once

namespace app::dbg
{
	class FileInfo
	{
	public:
		struct Data
		{
			csl::ut::FixedString<48> m_Name{};
			uint32_t m_Status{};
			void* m_pBuffer{};
			size_t m_Size{};
			INSERT_PADDING(8) {}; // ???
		};
	};
}