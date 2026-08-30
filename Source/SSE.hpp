#ifndef MATH_LIB_SSE_H
#define MATH_LIB_SSE_H

#include <MathLibHeader.hpp>

#define VECTOR4F_ALIGNEMENT 16

#if defined(SIMD_SSE2)

#include <immintrin.h>

namespace MathLib::Simd
{
    using VectorRegister4Float = __m128;

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float makeVector4Aligned(const float* ptr) noexcept
    {
        return _mm_load_ps(ptr);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float makeVector4Unaligned(const float* ptr) noexcept
    {
        return _mm_loadu_ps(ptr);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float makeVector4(float x, float y, float z, float w) noexcept
    {
        return _mm_set_ps(w, z, y, x);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float makeVector4(float value) noexcept
    {
#ifdef _mm_load1_ps
        return _mm_set1_ps(value);
#else
        return _mm_set_ps1(value);
#endif // _mm_load1_ps
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float makeVector4Zero() noexcept
    {
        return _mm_setzero_ps();
    }

    MATH_LIB_FORCE_INLINE void storeAligned(VectorRegister4Float v, float* ptr) noexcept
    {
        _mm_store_ps(ptr, v);
    }

    MATH_LIB_FORCE_INLINE void storeUnaligned(VectorRegister4Float v, float* ptr) noexcept
    {
        _mm_storeu_ps(ptr, v);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float add(const VectorRegister4Float& a,
                                                                 const VectorRegister4Float& b) noexcept
    {
        return _mm_add_ps(a, b);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float sub(const VectorRegister4Float& a,
                                                                 const VectorRegister4Float& b) noexcept
    {
        return _mm_sub_ps(a, b);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float mul(const VectorRegister4Float& a,
                                                                 const VectorRegister4Float& b) noexcept
    {
        return _mm_mul_ps(a, b);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float div(const VectorRegister4Float& a,
                                                                 const VectorRegister4Float& b) noexcept
    {
        return _mm_div_ps(a, b);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float min(const VectorRegister4Float& a,
                                                                 const VectorRegister4Float& b) noexcept
    {
        return _mm_min_ps(a, b);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float max(const VectorRegister4Float& a,
                                                                 const VectorRegister4Float& b) noexcept
    {
        return _mm_max_ps(a, b);
    }

    // a * b + c
    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float fma(const VectorRegister4Float& a,
                                                                 const VectorRegister4Float& b,
                                                                 const VectorRegister4Float& c) noexcept
    {
#if defined(SIMD_FMA)
        return _mm_fmadd_ps(a, b, c);
#else
        return mul(add(a, b), c);
#endif
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE float dot(const VectorRegister4Float& a, const VectorRegister4Float& b) noexcept
    {
#if defined(SIMD_SSE42)
        return _mm_cvtss_f32(_mm_dp_ps(a, b, 0xF1));
#else
        // [ax*bx, ay*by, az*bz, aw*bw]
        const __m128 mul = _mm_mul_ps(a, b);

        // [az*bz, aw*bw, az*bz, aw*bw]
        const __m128 high = _mm_movehl_ps(mul, mul);

        // [ax*bx + az*bz, ay*by + aw*bw, ...]
        const __m128 sum = _mm_add_ps(mul, high);

        // Move lane 1 into lane 0.
        const __m128 lane1 = _mm_shuffle_ps(sum, sum, _MM_SHUFFLE(1, 1, 1, 1));

        // ax*bx + ay*by + az*bz + aw*bw
        return _mm_cvtss_f32(_mm_add_ss(sum, lane1));
#endif // SIMD_SSE42
    }

} // namespace MathLib::Simd

#endif // defined(SIMD_SSE2)

#endif // MATH_LIB_SSE_H
