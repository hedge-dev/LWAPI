#pragma once

namespace csl::ut
{
	template<typename TKey, typename Tx>
	struct Pair
	{
		TKey key;
		Tx x;

		Pair(TKey key, Tx x) : key(key), x(x) {}

		bool operator==(const TKey& key) const
		{
			return this->key == key;
		}

		bool operator!=(const TKey& key) const
		{
			return this->key != key;
		}
	};

	template<typename TKey, typename Tx>
	inline static Pair<TKey, Tx> MakePair(TKey key, Tx x)
	{
		return Pair<TKey, Tx>{key, x};
	}
}