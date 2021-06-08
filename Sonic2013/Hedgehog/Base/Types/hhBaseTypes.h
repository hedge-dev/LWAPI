#pragma once

// Compiler
#if defined(__INTEL_COMPILER)
	#define HH_COMPILER_INTEL
#elif defined(_MSC_VER)
	#define HH_COMPILER_MSVC
#elif defined(__SNC__)
	#define HH_COMPILER_SNC
#elif defined(__GNUC__)
	#define HH_COMPILER_GCC
#elif defined(__MWERKS__)
	#define HH_COMPILER_MWERKS
#endif

#if !defined(HH_COMPILER_INTEL)
	#define HH_FORCE_INLINE __forceinline
#else
	#define HH_FORCE_INLINE inline
#endif

// Architecture

#if defined(__i386__) || defined(_M_IX86)
#	define HH_ARCH_IA32
#	define HH_ENDIAN_LITTLE 1
#	define HH_ENDIAN_BIG	0
#	define HH_POINTER_SIZE 4
#elif defined(_M_AMD64) || defined(_M_X64) || defined(__amd64) || defined(__x86_64)
#	define HH_ARCH_X64
#	define HH_ENDIAN_LITTLE 1
#	define HH_ENDIAN_BIG	0
#	define HH_POINTER_SIZE 8
#endif

typedef float  hhReal;
typedef float  hhFloat32;
typedef double hhDouble64;
typedef signed char		hhChar;
typedef signed char		hhInt8;
typedef signed short	hhInt16;
typedef signed int		hhInt32;
typedef unsigned char	hhUchar;
typedef unsigned char	hhUint8;
typedef unsigned short	hhUint16;
typedef unsigned int	hhUint32;

#if defined(HH_ARCH_X64)
#	if defined(HH_PLATFORM_X64)
	typedef unsigned __int64 hhUlong; 
	typedef signed __int64 hhLong;
#	else
	typedef unsigned long hhUlong; // UNIX64
	typedef signed long hhLong; // UNIX64
#	endif
#elif defined(HH_COMPILER_MSVC) && (_MSC_VER >= 1300)
	typedef unsigned __int64 hhUlong; // VC7.0 or higher, 64bit warnings
	typedef signed __int64 hhLong;
#else
	typedef unsigned long hhUlong;
	typedef signed long hhLong;
#endif

#define HH_ALIGN_OF(T) __alignof(T)
#define HH_NULL 0
#define HH_OFFSET_OF(CLASS, MEMBER) size_t(reinterpret_cast<hhLong>(&(reinterpret_cast<CLASS*>(16)->MEMBER))-16)

#define HH_REFLECTION_CLASSFILE_DESTINATION(PATH)
#define HH_DECLARE_REFLECTION() \
	static const struct app::fnd::RflClassMemberInternal ms_Members[]; \
	static const app::fnd::RflClass& staticClass(); \
	struct DefaultStruct

namespace app
{
	namespace fnd
	{
		class RflClass;

		struct Variant
		{
			void* m_pObject;
			const RflClass* m_pClass;
		};
	}
}

#define HH_COUNT_OF(x) (sizeof(x) / sizeof((x)[0]))