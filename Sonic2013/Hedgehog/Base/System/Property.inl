
inline uint app::fnd::Property::MapStringToKey(const char* in_pStr)
{
	csl::ut::StringMapOperation op;
	return op.hash(reinterpret_cast<size_t>(in_pStr));
}

inline app::fnd::PropertyValue::PropertyValue(const float in_float)
{
	setFloat(in_float);
}

inline app::fnd::PropertyValue::PropertyValue(const int in_int)
{
	setInt(in_int);
}

inline app::fnd::PropertyValue::PropertyValue(void* in_pPtr)
{
	setPtr(in_pPtr);
}

inline app::fnd::PropertyValue::PropertyValue(uint64 in_long)
{
	setUint64(in_long);
}

inline void app::fnd::PropertyValue::setFloat(const float in_float)
{
	union
	{
		float f;
		uint u;
	} u;
	u.f = in_float;
	Data = u.u;
}

inline void app::fnd::PropertyValue::setInt(const int in_int)
{
	Data = in_int;
}

inline void app::fnd::PropertyValue::setPtr(void* in_pPtr)
{
	Data = reinterpret_cast<uint64>(in_pPtr);
}

inline void app::fnd::PropertyValue::setUint64(uint64 in_long)
{
	Data = in_long;
}

inline float app::fnd::PropertyValue::getFloat() const
{
	union
	{
		float f;
		uint u;
	} u;
	u.u = uint(Data);
	return u.f;
}

inline int app::fnd::PropertyValue::getInt() const
{
	return static_cast<int>(Data);
}

inline void* app::fnd::PropertyValue::getPtr() const
{
	return reinterpret_cast<void*>(Data);
}

inline uint64 app::fnd::PropertyValue::getUint64() const
{
	return Data;
}
