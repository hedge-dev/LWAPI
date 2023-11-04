#pragma once

namespace csl::ut
{
	template<typename TKey, typename Tx>
	struct Pair
	{
		TKey Key;
		Tx X;

		Pair(TKey in_key, Tx in_x) : Key(in_key), X(in_x) {}

		bool operator==(const TKey& in_rKey) const
		{
			return this->Key == in_rKey;
		}

		bool operator!=(const TKey& in_rKey) const
		{
			return this->Key != in_rKey;
		}
	};

	template<typename TKey, typename Tx>
	inline static Pair<TKey, Tx> MakePair(TKey in_key, Tx in_x)
	{
		return Pair<TKey, Tx>{in_key, in_x};
	}
}