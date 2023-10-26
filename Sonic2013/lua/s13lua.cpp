// cl /Fo /Zl /c s13lua.cpp
// lib s13lua.obj

#include <Windows.h>
namespace
{
	const HMODULE MODULE_BASE = GetModuleHandle(nullptr);
}

struct Node;
struct TValue;
extern "C"
{
	const Node* ltable_dummynode_()
	{
		return (Node*)((size_t)MODULE_BASE + 0xA5FFA4);
	}

	const TValue* lobject_luaO_nilobject_()
	{
		return (TValue*)((size_t)MODULE_BASE + 0xA60050);
	}
}