
inline uint app::fnd::Property::MapStringToKey(const char* pStr)
{
	csl::ut::StringMapOperation op;
	return op.hash(reinterpret_cast<size_t>(pStr));
}

inline app::fnd::PropertyValue::PropertyValue(const float f)
{
	setFloat(f);
}

inline app::fnd::PropertyValue::PropertyValue(const int i)
{
	setInt(i);
}

inline app::fnd::PropertyValue::PropertyValue(void* p)
{
	setPtr(p);
}

inline app::fnd::PropertyValue::PropertyValue(uint64 i)
{
	setUint64(i);
}

inline void app::fnd::PropertyValue::setFloat(const float f)
{
	union
	{
		float f;
		uint u;
	} u;
	u.f = f;
	m_Data = u.u;
}

inline void app::fnd::PropertyValue::setInt(const int i)
{
	m_Data = i;
}

inline void app::fnd::PropertyValue::setPtr(void* p)
{
	m_Data = reinterpret_cast<uint64>(p);
}

inline void app::fnd::PropertyValue::setUint64(uint64 i)
{
	m_Data = i;
}

inline float app::fnd::PropertyValue::getFloat() const
{
	union
	{
		float f;
		uint u;
	} u;
	u.u = uint(m_Data);
	return u.f;
}

inline int app::fnd::PropertyValue::getInt() const
{
	return static_cast<int>(m_Data);
}

inline void* app::fnd::PropertyValue::getPtr() const
{
	return reinterpret_cast<void*>(m_Data);
}

inline uint64 app::fnd::PropertyValue::getUint64() const
{
	return m_Data;
}
