#ifndef MATH_LIB_NEON_H
#define MATH_LIB_NEON_H

#include <MathLibHeader.hpp>

#if defined(SIMD_NEON)

#include <arm_neon.h>

namespace MathLib::Simd
{
    using VectorRegister4Float = float32x4_t;

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float makeVector4Aligned(const float* ptr) noexcept
    {
        return vld1q_f32(ptr);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float makeVector4Unaligned(const float* ptr) noexcept
    {
        return vld1q_f32(ptr);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float makeVector4(float x, float y, float z, float w) noexcept
    {
        const float values[4] = {x, y, z, w};
        return vld1q_f32(values);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float makeVector4(float value) noexcept
    {
        return vdupq_n_f32(value);
    }

    template<float>
    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float makeVector4Zero() noexcept
    {
        return vdupq_n_f32(0.0f);
    }

    MATH_LIB_FORCE_INLINE void storeAligned(VectorRegister4Float v, float* ptr) noexcept
    {
        vst1q_f32(ptr, v);
    }

    MATH_LIB_FORCE_INLINE void storeUnaligned(VectorRegister4Float v, float* ptr) noexcept
    {
        vst1q_f32(ptr, v);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float add(const VectorRegister4Float& a,
                                                                 const VectorRegister4Float& b) noexcept
    {
        return vaddq_f32(a, b);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float sub(const VectorRegister4Float& a,
                                                                 const VectorRegister4Float& b) noexcept
    {
        return vsubq_f32(a, b);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float mul(const VectorRegister4Float& a,
                                                                 const VectorRegister4Float& b) noexcept
    {
        return vmulq_f32(a, b);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float div(const VectorRegister4Float& a,
                                                                 const VectorRegister4Float& b) noexcept
    {
        return vdivq_f32(a, b);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float min(const VectorRegister4Float& a,
                                                                 const VectorRegister4Float& b) noexcept
    {
        return vminq_f32(a, b);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float max(const VectorRegister4Float& a,
                                                                 const VectorRegister4Float& b) noexcept
    {
        return vmaxq_f32(a, b);
    }

    // a * b + c
    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Float fma(const VectorRegister4Float& a,
                                                                 const VectorRegister4Float& b,
                                                                 const VectorRegister4Float& c) noexcept
    {
        return vfmaq_f32(c, a, b);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE float dot(const VectorRegister4Float& a, const VectorRegister4Float& b) noexcept
    {
        return vaddvq_f32(vmulq_f32(a, b));
    }

    struct VectorRegister4Double
    {
        float64x2_t low;
        float64x2_t high;
    };
    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double makeVector4Aligned(const double* ptr) noexcept
    {
        return {vld1q_f64(ptr), vld1q_f64(ptr + 2)};
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double makeVector4Unaligned(const double* ptr) noexcept
    {
        return {vld1q_f64(ptr), vld1q_f64(ptr + 2)};
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double makeVector4(double x, double y, double z,
                                                                          double w) noexcept
    {
        return {float64x2_t{x, y}, float64x2_t{z, w}};
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double makeVector4(double value) noexcept
    {
        return {vdupq_n_f64(value), vdupq_n_f64(value)};
    }

    template<double>
    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double makeVector4Zero() noexcept
    {
        return {vdupq_n_f64(0.0), vdupq_n_f64(0.0)};
    }

    MATH_LIB_FORCE_INLINE void storeAligned(const VectorRegister4Double& v, double* ptr) noexcept
    {
        vst1q_f64(ptr, v.low);
        vst1q_f64(ptr + 2, v.high);
    }

    MATH_LIB_FORCE_INLINE void storeUnaligned(const VectorRegister4Double& v, double* ptr) noexcept
    {
        vst1q_f64(ptr, v.low);
        vst1q_f64(ptr + 2, v.high);
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double add(const VectorRegister4Double& a,
                                                                  const VectorRegister4Double& b) noexcept
    {
        return {vaddq_f64(a.low, b.low), vaddq_f64(a.high, b.high)};
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double sub(const VectorRegister4Double& a,
                                                                  const VectorRegister4Double& b) noexcept
    {
        return {vsubq_f64(a.low, b.low), vsubq_f64(a.high, b.high)};
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double mul(const VectorRegister4Double& a,
                                                                  const VectorRegister4Double& b) noexcept
    {
        return {vmulq_f64(a.low, b.low), vmulq_f64(a.high, b.high)};
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double div(const VectorRegister4Double& a,
                                                                  const VectorRegister4Double& b) noexcept
    {
        return {vdivq_f64(a.low, b.low), vdivq_f64(a.high, b.high)};
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double min(const VectorRegister4Double& a,
                                                                  const VectorRegister4Double& b) noexcept
    {
        return {vminq_f64(a.low, b.low), vminq_f64(a.high, b.high)};
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double max(const VectorRegister4Double& a,
                                                                  const VectorRegister4Double& b) noexcept
    {
        return {vmaxq_f64(a.low, b.low), vmaxq_f64(a.high, b.high)};
    }

    // a * b + c
    [[nodiscard]] MATH_LIB_FORCE_INLINE VectorRegister4Double fma(const VectorRegister4Double& a,
                                                                  const VectorRegister4Double& b,
                                                                  const VectorRegister4Double& c) noexcept
    {
        return {vfmaq_f64(c.low, a.low, b.low), vfmaq_f64(c.high, a.high, b.high)};
    }

    [[nodiscard]] MATH_LIB_FORCE_INLINE double dot(const VectorRegister4Double& a,
                                                   const VectorRegister4Double& b) noexcept
    {
        const float64x2_t lowMul = vmulq_f64(a.low, b.low);
        const float64x2_t highMul = vmulq_f64(a.high, b.high);

        const float64x2_t sum = vaddq_f64(lowMul, highMul);

        return vaddvq_f64(sum);
    }

} // namespace MathLib::Simd

#endif // defined(SIMD_NEON)

#endif // MATH_LIB_NEON_H
