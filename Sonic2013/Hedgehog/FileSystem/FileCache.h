#pragma once

namespace app::fnd
{
	class FileCache : public ReferencedObject
	{
	public:
		class DataTag;
		
		INSERT_PADDING(232) {};
		uint Flags{};
		csl::ut::MoveArray<DataTag*> Tags{};
		csl::ut::MoveArray<DataTag*> Tags2{};
		csl::ut::FixedString<64> Unk1{};
		csl::ut::FixedString<64> Unk2{};
		csl::ut::FixedString<64> Unk3{};
		csl::ut::FixedString<64> Cache{};
		csl::ut::StringMap<DataTag*> TagLookup{ GetAllocator() };
		uint SizeTotal{};
		uint SizeL{};
		uint SizeU{};
		uint Unk4{};

		uint CalcFreeCache() const
		{
			return SizeTotal - (SizeU + SizeL);
		}

		void OnEnterCache()
		{
			Flags &= 0xFFFFFFFE;
		}

		void OnLeaveCache()
		{
			
		}
	};
}