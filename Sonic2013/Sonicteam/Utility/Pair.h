#pragma once

namespace csl::ut
{
	template<typename TKey, typename Tx, typename Ty>
	struct Pair
	{
		TKey key;
		Tx x;
		Ty y;
	};

	template<typename TKey, typename Tx, typename Ty>
	inline static Pair<TKey, Tx, Ty> MakePair(TKey key, Tx x, Ty y)
	{
		return Pair<TKey, Tx, Ty>{key, x, y};
	}
}