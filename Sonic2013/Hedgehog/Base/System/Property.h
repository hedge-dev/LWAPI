#pragma once

namespace app::fnd
{
	struct alignas(8) PropertyValue
	{
		uint64 Data;

		inline PropertyValue() { Data = 0; }
		inline PropertyValue(const float in_float);
		inline PropertyValue(const int in_int);
		inline PropertyValue(void* in_pPtr);
		inline PropertyValue(uint64 in_long);

		inline void setFloat(const float in_float);
		inline void setInt(const int in_int);
		inline void setPtr(void* in_pPtr);
		inline void setUint64(uint64 in_long);

		inline float getFloat() const;
		inline int getInt() const;
		inline void* getPtr() const;
		inline uint64 getUint64() const;
	};
	
	class Property
	{
	public:
		uint Key{};
		uint AlignmentPadding{};
		PropertyValue Value{};

		Property() {}
		Property(uint in_key) : Key(in_key) { }
		Property(uint in_key, PropertyValue in_value) : Key(in_key), Value(in_value) {}

		uint GetKey() const
		{
			return Key;
		}

		PropertyValue GetValue() const
		{
			return Value;
		}

		void SetValue(PropertyValue in_value)
		{
			Value = in_value;
		}

		static uint MapStringToKey(const char* in_pStr);
	};
}

#include "hhProperty.inl"