#pragma once

#include <Windows.h>
#include <WinBase.h>
#include <type_traits>

typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short sint16;
typedef unsigned short uint16;
typedef signed int sint32;
typedef unsigned int uint32;
typedef signed long long sint64;
typedef unsigned long long uint64;

typedef unsigned short ushort;
typedef unsigned int uint;

#define _CONCATX(x, y) x##y
#define _CONCAT(x, y)  _CONCATX(x, y)

#define CONCAT2(x, y) _CONCAT(x, y)

#define CHAR_BIT 8
#define FORCE_RET __asm mov esp, ebp \
	__asm pop ebp \
	__asm retn \

#define INSERT_PADDING(length) char CONCAT2(pad, __LINE__)[length]

#define ASSERT(condition, message) static_assert(condition, message)

#define ASSERT_OFFSETOF(type, field, offset) ASSERT(offsetof(type, field) == offset, "offsetof("#type"::"#field") != "#offset)

#define FUNCTION_PTR(returnType, callingConvention, function, location, ...) \
	returnType (callingConvention *function)(__VA_ARGS__) = (returnType(callingConvention*)(__VA_ARGS__))(location)

#define BASE_ADDRESS 0x400000

#ifdef BASE_ADDRESS
const HMODULE MODULE_HANDLE = GetModuleHandle(nullptr);

#define ASLR(address) \
    ((size_t)MODULE_HANDLE + (size_t)address - (size_t)BASE_ADDRESS)
#endif