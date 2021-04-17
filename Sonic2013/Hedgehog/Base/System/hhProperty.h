#pragma once

namespace app::fnd
{
	struct alignas(8) PropertyValue
	{
		uint64 m_Data;

		inline PropertyValue() { m_Data = 0; }
		inline PropertyValue(const float f);
		inline PropertyValue(const int i);
		inline PropertyValue(void* p);
		inline PropertyValue(uint64 i);

		inline void setFloat(const float f);
		inline void setInt(const int i);
		inline void setPtr(void* p);
		inline void setUint64(uint64 i);

		inline float getFloat() const;
		inline int getInt() const;
		inline void* getPtr() const;
		inline uint64 getUint64() const;
	};
	
	class Property
	{
	public:
		uint m_Key{};
		uint m_AlignmentPadding{};
		PropertyValue m_Value{};

		Property() {}
		Property(uint key) : m_Key(key) { }
		Property(uint key, PropertyValue value) : m_Key(key), m_Value(value) {}

		uint GetKey() const
		{
			return m_Key;
		}

		PropertyValue GetValue() const
		{
			return m_Value;
		}

		void SetValue(PropertyValue value)
		{
			m_Value = value;
		}

		static uint MapStringToKey(const char* pStr);
	};
}

#include "hhProperty.inl"