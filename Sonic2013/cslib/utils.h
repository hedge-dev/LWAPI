#pragma once

#include <Windows.h>
#include <WinBase.h>
#include <type_traits>

#define CHAR_BIT 8
const HMODULE MODULE_HANDLE = GetModuleHandle(NULL);
#define BASE_ADDRESS (int)GetModuleHandle(NULL)

#define ASLR(address) \
	((unsigned int)MODULE_HANDLE + (unsigned int)address - 0x400000)

#define FUNCTION_PTR(returnType, callingConvention, function, location, ...) \
	returnType (callingConvention *function)(__VA_ARGS__) = (returnType(callingConvention*)(__VA_ARGS__))(location)