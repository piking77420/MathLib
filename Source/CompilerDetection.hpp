#ifndef MATH_LIB_COMPILER_DETECTION_H
#define MATH_LIB_COMPILER_DETECTION_H

// NOLINTBEGIN(cppcoreguidelines-macro-usage)

// Architecture
#if defined(_M_X64) || defined(__x86_64__)
#define CPU_X86_64 1
#elif defined(_M_IX86) || defined(__i386__)
#define CPU_X86_32 1
#elif defined(_M_ARM64) || defined(__aarch64__)
#define CPU_ARM_64 1
#elif defined(_M_ARM) || defined(__arm__)
#define CPU_ARM_32 1
#endif

#if CPU_X86_64

#if defined(MATHLIB_SIMD_LEVEL_AVX2)

#define SIMD_AVX2 1
#define SIMD_AVX 1
#define SIMD_SSE2 1

#elif defined(MATHLIB_SIMD_LEVEL_AVX)

#define SIMD_AVX 1
#define SIMD_SSE2 1

#elif defined(MATHLIB_SIMD_LEVEL_SSE2)

#define SIMD_SSE2 1

#endif

#endif // CPU_X86_64

#if CPU_ARM_64

// ARM SIMD
#if defined(MATHLIB_SIMD_LEVEL_SVE)
#define SIMD_ARM_SVE 1
#endif

#if defined(MATHLIB_SIMD_LEVEL_SVE2)
#define SIMD_ARM_SVE2 1
#endif

#if defined(MATHLIB_SIMD_LEVEL)
#define SIMD_ARM_NEON 1
#endif

#endif // CPU_ARM_64

#if CPU_X86_64
#include <immintrin.h>
#endif // CPU_X86_64

#if SIMD_ARM_SVE
#include <arm_sve.h>
#endif

#if SIMD_ARM_SVE2
#include <arm_sve.h>
#endif

#if SIMD_ARM_NEON
#include <arm_neon.h>
#endif

// NOLINTEND(cppcoreguidelines-macro-usage)

#endif // MATH_LIB_COMPILER_DETECTION_H
