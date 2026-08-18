#ifndef MATH_LIB_MATH_LIB_HEADER_H
#define MATH_LIB_MATH_LIB_HEADER_H

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstdint>
#include <cstdlib>

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
#define SIMD_SSE42 1
#define SIMD_SSE2 1

#elif defined(MATHLIB_SIMD_LEVEL_AVX)

#define SIMD_AVX 1
#define SIMD_SSE42 1
#define SIMD_SSE2 1

#elif defined(MATHLIB_SIMD_LEVEL_SSE42)

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

#if defined(_MSC_VER)
#define MATH_LIB_FORCE_INLINE __forceinline
#define MATH_LIB_RESTRICT __restrict

#elif defined(__clang__)
#define MATH_LIB_FORCE_INLINE inline __attribute__((always_inline))
#define MATH_LIB_RESTRICT __restrict

#elif defined(__GNUC__)
#define MATH_LIB_FORCE_INLINE inline __attribute__((always_inline))
#define MATH_LIB_RESTRICT __restrict__

#else
#define MATH_LIB_FORCE_INLINE inline
#endif

#if !defined(NDEBUG)
#define MATHLIB_ASSERT(x) assert(x)
#else
#define MATHLIB_ASSERT(x) ((void)0)
#endif

#define ASSERT_IS_FINITE(x) MATHLIB_ASSERT((x).isFinite());

namespace MathLib
{
    constexpr double DoubleEpsilon = 0.0001;
    constexpr float FloatEpsilon = 0.001f;

    constexpr double SquareDoubleEpsilon = DoubleEpsilon * DoubleEpsilon;
    constexpr float SquareFloatEpsilon = FloatEpsilon * FloatEpsilon;

    [[nodiscard]] constexpr bool fuzzyZero(double _value, double _tolerance = DoubleEpsilon)
    {
        return std::abs(_value) < _tolerance;
    }

    [[nodiscard]] constexpr bool fuzzyZero(float _value, float _tolerance = FloatEpsilon)
    {
        return std::abs(_value) < _tolerance;
    }

    [[nodiscard]] constexpr bool fuzzyEqual(double _a, double _b, double _tolerance = DoubleEpsilon)
    {
        return std::abs(_a - _b) <= _tolerance * std::max({1.0, std::abs(_a), std::abs(_b)});
    }

    [[nodiscard]] constexpr bool fuzzyEqual(float _a, float _b, float _tolerance = FloatEpsilon)
    {
        return std::abs(_a - _b) <= _tolerance * std::max({1.0f, std::abs(_a), std::abs(_b)});
    }

    template<std::size_t Alignment>
    [[nodiscard]] constexpr bool isAligned(const void* const _ptr) noexcept
    {
        static_assert(std::has_single_bit(Alignment));

        return (reinterpret_cast<std::uintptr_t>(_ptr) & (Alignment - 1)) == 0;
    }

    constexpr size_t alignedSize(size_t _size, size_t _alignement) noexcept
    {
        return (_size + _alignement - 1) & ~(_alignement - 1);
    }

    static constexpr size_t SSE_ALIGNEMENT = 16;
    static constexpr size_t AVX_AVX2_ALIGNEMENT = 32;
}

// NOLINTEND(cppcoreguidelines-macro-usage)
#endif // MATH_LIB_MATH_LIB_HEADER_H
