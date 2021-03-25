#pragma once

namespace csl::ut
{
	template<typename TKey, typename Tx>
	class Pair
	{
	public:
		TKey key;
		Tx x;
	};

	template<typename TKey, typename Tx>
	inline static Pair<TKey, Tx> MakePair(TKey key, Tx x)
	{
		return Pair<TKey, Tx>{key, x};
	}
}