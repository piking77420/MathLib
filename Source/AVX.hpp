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

} // namespace MathLib::Simd

#endif // defined(SIMD_AVX)

#endif // MATH_LIB_AVX_H
