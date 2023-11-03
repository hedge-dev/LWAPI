#pragma once

namespace app::fnd
{
	class FileCache : public ReferencedObject
	{
	public:
		class DataTag;
		INSERT_PADDING(232) {};
		uint m_Flags{};
		csl::ut::MoveArray<DataTag*> m_Tags{};
		csl::ut::MoveArray<DataTag*> m_Tags2{};
		csl::ut::FixedString<64> m_Unk1{};
		csl::ut::FixedString<64> m_Unk2{};
		csl::ut::FixedString<64> m_Unk3{};
		csl::ut::FixedString<64> m_Cache{};
		csl::ut::StringMap<DataTag*> m_TagLookup{ GetAllocator() };
		uint m_SizeTotal{};
		uint m_SizeL{};
		uint m_SizeU{};
		uint m_Unk4{};

		uint CalcFreeCache() const
		{
			return m_SizeTotal - (m_SizeU + m_SizeL);
		}

		void OnEnterCache()
		{
			m_Flags &= 0xFFFFFFFE;
		}

		void OnLeaveCache()
		{
			
		}
	};
}