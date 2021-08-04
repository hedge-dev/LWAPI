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

#define INSERT_PADDING(length) char CONCAT2(pad, __LINE__)[length]

#define ASSERT(condition, message) static_assert(condition, message)

#define ASSERT_OFFSETOF(type, field, offset) ASSERT(offsetof(type, field) == offset, "offsetof("#type"::"#field") != "#offset)

#define FUNCTION_PTR(returnType, callingConvention, function, location, ...) \
	returnType (callingConvention *function)(__VA_ARGS__) = (returnType(callingConvention*)(__VA_ARGS__))(location)

#ifndef BASE_ADDRESS
#define BASE_ADDRESS 0x400000
#endif

#define ASLR(address) \
    ((size_t)csl::ut::MODULE_HANDLE + (size_t)address - (size_t)BASE_ADDRESS)

namespace csl::ut
{
    const HMODULE MODULE_HANDLE = GetModuleHandle(nullptr);
    static constexpr size_t SIGN_BIT = ((1u << ((sizeof(size_t) * CHAR_BIT) - 1)));
}

namespace csl::fnd
{	
    static int Snprintf(char* pBuf, size_t bufSize, const char* pFormat, ...)
    {
        if (!bufSize)
            return -1;
    	
        va_list args;
        va_start(args, pFormat);

        int result = vsnprintf_s(pBuf, bufSize, -1, pFormat, args);
    	
        va_end(args);

        return result;
    }
	
	// This is copied from optimised code
	static size_t StrLcpy(char* pDestBuf, const char* pSrc, size_t len)
	{
        char* pCurChar = pDestBuf;
        size_t bytesReplaced = 0;
        if (len == 1)
        {
            *pDestBuf = 0;
        }
        else
        {
            char srcChar = *pSrc;
            do
            {
                *pCurChar = srcChar;
                srcChar = (pCurChar++)[pSrc - pDestBuf + 1];
                ++bytesReplaced;
            } while (srcChar && bytesReplaced < len - 1);
            *pCurChar = 0;
        }
        return bytesReplaced;
	}
}