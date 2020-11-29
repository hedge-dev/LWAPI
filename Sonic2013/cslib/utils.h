#pragma once

#include <Windows.h>
#include <WinBase.h>
#include <type_traits>

#define CONCAT2(x, y) x##y
#define CHAR_BIT 8
#define FORCE_RET __asm ret

const HMODULE MODULE_HANDLE = GetModuleHandle(NULL);
#define BASE_ADDRESS (size_t)MODULE_HANDLE(NULL)

#define INSERT_PADDING(length) char CONCAT2(pad, __LINE__)[length]
#define ASSERT(condition, message) static_assert(condition, message)
#define ASSERT_OFFSETOF(type, field, offset) ASSERT(offsetof(type, field) == offset, "offsetof("#type"::"#field") != "#offset)

#define ASLR(address) \
	((unsigned int)MODULE_HANDLE + (unsigned int)address - 0x400000)

#define FUNCTION_PTR(returnType, callingConvention, function, location, ...) \
	returnType (callingConvention *function)(__VA_ARGS__) = (returnType(callingConvention*)(__VA_ARGS__))(location)