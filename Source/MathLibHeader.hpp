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

#if (defined(__arm__) && !defined(__aarch64__))
#error "32-bit ARM is not supported"
#endif

#if defined(__i386__) || defined(_M_IX86)
#error "32-bit x86 is not supported"
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
#define SIMD_SVE 1
#endif

#if defined(MATHLIB_SIMD_LEVEL_SVE2)
#define SIMD_SVE2 1
#endif

// NEON is always available on ARM64 / AArch64.
#define SIMD_NEON 1

#endif // CPU_ARM_64

#if CPU_X86_64
#include <immintrin.h>
#endif // CPU_X86_64

#if SIMD_SVE
#include <arm_sve.h>
#endif

#if SIMD_SVE2
#include <arm_sve.h>
#endif

#if SIMD_NEON
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

#if defined(__clang__)
#define MATH_ASSUME(x) __builtin_assume(x)
#elif defined(_MSC_VER)
#define MATH_ASSUME(x) __assume(x)
#elif defined(__GNUC__)
#define MATH_ASSUME(x)                                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
            __builtin_unreachable();                                                                                   \
    } while (false)
#else
#define MATH_ASSUME(x) ((void)0)
#endif

namespace MathLib
{
    constexpr double DoubleEpsilon = 0.0001;
    constexpr float FloatEpsilon = 0.001f;

    constexpr double SquareDoubleEpsilon = DoubleEpsilon * DoubleEpsilon;
    constexpr float SquareFloatEpsilon = FloatEpsilon * FloatEpsilon;

    template<typename T>
    struct Epsilon;

    template<>
    struct Epsilon<float>
    {
        static constexpr float Value = FloatEpsilon;
        static constexpr float Square = SquareFloatEpsilon;
        static constexpr float Double = FloatEpsilon * FloatEpsilon;
    };

    template<>
    struct Epsilon<double>
    {
        static constexpr double Value = DoubleEpsilon;
        static constexpr double Square = SquareDoubleEpsilon;
        static constexpr double Double = DoubleEpsilon * DoubleEpsilon;
    };

    [[nodiscard]] constexpr bool fuzzyZero(double value, double tolerance = DoubleEpsilon)
    {
        return std::abs(value) < tolerance;
    }

    [[nodiscard]] constexpr bool fuzzyZero(float value, float tolerance = FloatEpsilon)
    {
        return std::abs(value) < tolerance;
    }

    [[nodiscard]] constexpr bool fuzzyEqual(double a, double b, double tolerance = DoubleEpsilon)
    {
        return std::abs(a - b) <= tolerance * std::max({1.0, std::abs(a), std::abs(b)});
    }

    [[nodiscard]] constexpr bool fuzzyEqual(float a, float b, float tolerance = FloatEpsilon)
    {
        return std::abs(a - b) <= tolerance * std::max({1.0f, std::abs(a), std::abs(b)});
    }

    enum class RotationOrder
    {
        // Rotation application order.
        // Column-vector convention:
        //
        // XYZ -> Rz * Ry * Rx
        // XZY -> Ry * Rz * Rx
        // YXZ -> Rz * Rx * Ry
        // YZX -> Rx * Rz * Ry
        // ZXY -> Ry * Rx * Rz
        // ZYX -> Rx * Ry * Rz

        XYZ,
        XZY,
        YXZ,
        YZX,
        ZXY,
        ZYX,
    };

    template<std::size_t Alignment>
    [[nodiscard]] constexpr bool isAligned(const void* const ptr) noexcept
    {
        static_assert(std::has_single_bit(Alignment));

        return (reinterpret_cast<std::uintptr_t>(ptr) & (Alignment - 1)) == 0;
    }

    constexpr size_t alignedSize(size_t size, size_t alignement) noexcept
    {
        return (size + alignement - 1) & ~(alignement - 1);
    }

    static constexpr size_t SSE_ALIGNEMENT = 16;
    static constexpr size_t AVX_ALIGNEMENT = 32;


    template<typename T>
    struct SimdTraits;

    template<>
    struct SimdTraits<float>
    {
#if defined(MATH_LIB_AVX)
        using Register = __m128;
#elif defined(MATH_LIB_NEON)
        using Register = float32x4_t;
#endif
    };

    template<>
    struct SimdTraits<double>
    {
#if defined(MATH_LIB_AVX)
        using Register = __m256d;
#elif defined(MATH_LIB_NEON)
        using Register = float64x2x2_t; // or whatever abstraction you use
#endif
    };

}

// NOLINTEND(cppcoreguidelines-macro-usage)
#endif // MATH_LIB_MATH_LIB_HEADER_H
