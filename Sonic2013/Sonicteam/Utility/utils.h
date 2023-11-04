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

#undef max
namespace csl::ut
{
    const HMODULE MODULE_HANDLE = GetModuleHandle(nullptr);
    static constexpr size_t SIGN_BIT = ((1u << ((sizeof(size_t) * CHAR_BIT) - 1)));

    template<typename TTo, typename TFrom>
    TTo union_cast(const TFrom& in_rFrom)
    {
        alignas(std::max(alignof(TTo), alignof(TFrom))) union
	    {
            char srcBuffer[sizeof(TFrom)];
	    	char destBuffer[sizeof(TTo)];
	    } container;

        if constexpr (sizeof(TTo) > sizeof(TFrom))
            memset(container.destBuffer, 0, sizeof(container.destBuffer));

        memcpy(container.srcBuffer, &in_rFrom, sizeof(container.srcBuffer));
        return *reinterpret_cast<TTo*>(container.destBuffer);
    }

    template<typename T>
    T RoundUp(const T& in_rValue, uint in_round)
    {
        return (in_rValue + in_round - 1) & ~(in_round - 1);
    }

    template<typename T>
    T RoundDown(const T& in_rValue, uint in_round)
    {
        return in_rValue & ~(in_round - 1);
    }
}

namespace csl::fnd
{
    static int VSnprintf(char* in_pBuf, size_t in_bufSize, const char* in_pFormat, va_list in_args)
    {
        if (!in_bufSize)
            return -1;

        int result = vsnprintf_s(in_pBuf, in_bufSize, -1, in_pFormat, in_args);

        return result;
    }

    static int Snprintf(char* in_pBuf, size_t in_bufSize, const char* in_pFormat, ...)
    {
        if (!in_bufSize)
            return -1;
    	
        va_list args;
        va_start(args, pFormat);

        int result = vsnprintf_s(in_pBuf, in_bufSize, -1, in_pFormat, args);
    	
        va_end(args);

        return result;
    }
	
	// This is copied from optimised code
	static size_t StrLcpy(char* pDestBuf, const char* in_pSrc, size_t in_len)
	{
        char* pCurChar = in_pDestBuf;
        size_t bytesReplaced = 0;
        if (in_len == 1)
        {
            *in_pDestBuf = 0;
        }
        else
        {
            char srcChar = *in_pSrc;
            do
            {
                *pCurChar = srcChar;
                srcChar = (pCurChar++)[in_pSrc - in_pDestBuf + 1];
                ++bytesReplaced;
            } while (srcChar && bytesReplaced < len - 1);
            *pCurChar = 0;
        }
        return bytesReplaced;
	}
}