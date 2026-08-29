#ifndef MATH_LIB_AVX_H
#define MATH_LIB_AVX_H

#include <MathLibHeader.hpp>

#define VECTOR4D_ALIGNEMENT 32

#if defined(SIMD_AVX)

#include <immintrin.h>

namespace MathLib::Simd
{
    using VectorRegister4Double = __m256d;

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double makeVector4DAligned(const double* ptr) noexcept
    {
        return _mm256_load_pd(ptr);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double makeVector4DUnaligned(const double* ptr) noexcept
    {
        return _mm256_loadu_pd(ptr);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double makeVector4D(double x, double y, double z,
                                                                           double w) noexcept
    {
        return _mm256_set_pd(w, z, y, x);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double makeVector4D(double value) noexcept
    {
        return _mm256_set1_pd(value);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double makeVector4DZero() noexcept
    {
        return _mm256_setzero_pd();
    }

    MATH_LIB_FORCE_INLINE void storeAligned(VectorRegister4Double v, double* ptr) noexcept
    {
        _mm256_store_pd(ptr, v);
    }

    MATH_LIB_FORCE_INLINE void storeUnaligned(VectorRegister4Double v, double* ptr) noexcept
    {
        _mm256_storeu_pd(ptr, v);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double add(const VectorRegister4Double& a,
                                                                  const VectorRegister4Double& b) noexcept
    {
        return _mm256_add_pd(a, b);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double sub(const VectorRegister4Double& a,
                                                                  const VectorRegister4Double& b) noexcept
    {
        return _mm256_sub_pd(a, b);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double mul(const VectorRegister4Double& a,
                                                                  const VectorRegister4Double& b) noexcept
    {
        return _mm256_mul_pd(a, b);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double div(const VectorRegister4Double& a,
                                                                  const VectorRegister4Double& b) noexcept
    {
        return _mm256_div_pd(a, b);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double min(const VectorRegister4Double& a,
                                                                  const VectorRegister4Double& b) noexcept
    {
        return _mm256_min_pd(a, b);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double max(const VectorRegister4Double& a,
                                                                  const VectorRegister4Double& b) noexcept
    {
        return _mm256_max_pd(a, b);
    }

    // a * b + c
    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double fma(const VectorRegister4Double& a,
                                                                  const VectorRegister4Double& b,
                                                                  const VectorRegister4Double& c) noexcept
    {
#if defined(SIMD_FMA)
        return _mm256_fmadd_pd(a, b, c);
#else
        return mul(add(a, b), c);
#endif
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE double dot(const VectorRegister4Double& a, const VectorRegister4Double& b)
    {
        // [ax*bx, ay*by, az*bz, aw*bw]
        const __m256d mul = _mm256_mul_pd(a, b);

        // [ax*bx, ay*by]
        const __m128d low = _mm256_castpd256_pd128(mul);

        // [az*bz, aw*bw]
        const __m128d high = _mm256_extractf128_pd(mul, 1);
        // [ax*bx + az*bz, ay*by + aw*bw]
        const __m128d sum = _mm_add_pd(low, high);

        // Move high lane into low lane.
        const __m128d highSum = _mm_unpackhi_pd(sum, sum);

        // (ax*bx + az*bz) + (ay*by + aw*bw)
        return _mm_cvtsd_f64(_mm_add_sd(sum, highSum));
    }
} // namespace MathLib::Simd

#endif // defined(SIMD_AVX)

#endif // MATH_LIB_AVX_H
