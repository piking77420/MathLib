#ifndef MATH_LIB_SIMDHEADER_H
#define MATH_LIB_SIMDHEADER_H

#include <MathLibHeader.hpp>
#include <AVX.hpp>
#include <NEON.hpp>
#include <SSE.hpp>

namespace MathLib
{
    template<typename T>
    struct SimdAlignementRegister4;

    template<>
    struct SimdAlignementRegister4<float>
    {
#if defined(_M_X64)
        static constexpr size_t Value = sizeof(__m128);
#elif defined(_M_ARM64)
        static constexpr size_t Value = sizeof(float32x4_t);
#endif
    };

    template<>
    struct SimdAlignementRegister4<double>
    {
#if defined(_M_X64)
        static constexpr size_t Value = sizeof(__m256d);
#elif defined(_M_ARM64)
        static constexpr size_t Value = sizeof(float64x2x2_t);
#endif
    };

} // namespace MathLib

#endif // MATH_LIB_SIMDHEADER_H
