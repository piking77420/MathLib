#include <array>
#include <cstddef>
#include <benchmark/benchmark.h>
#include <BenchmarkHeader.hpp>
#include <Alloc.hpp>
#include <MathLibHeader.hpp>
#include <Vector4d.hpp>

using namespace MathLib;
using namespace Alloc;

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(misc-const-correctness)
// NOLINTBEGIN(clang-analyzer-deadcode.DeadStores)
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)

namespace
{

    void BM_Vector4dDot(benchmark::State& state)
    {
        Vector4d a(10.0, 20.0, -2, -10);
        Vector4d b(30.0, 40.0, -24, 10);

        for (auto _ : state)
        {
            double result = Vector4d::dot(a, b);
            benchmark::DoNotOptimize(result);
        }
    }
    BENCHMARK(BM_Vector4dDot);

    void BM_Vector4dDot_Array(benchmark::State& state)
    {
        std::array<Vector4d, 1024> a;
        std::array<Vector4d, 1024> b;

        benchmark::DoNotOptimize(a);
        benchmark::DoNotOptimize(b);

        for (auto _ : state)
        {
            double result = 0.0;

            for (std::size_t i = 0; i < a.size(); ++i)
            {
                result += Vector4d::dot(a[i], b[i]);
            }

            benchmark::DoNotOptimize(result);
        }
    }
    BENCHMARK(BM_Vector4dDot_Array);

    void BM_Vector4dDot_Array_Aligned(benchmark::State& state)
    {
        constexpr size_t size = 1024;
        Vector4d* arrayA = alignMalloc<Vector4d>(size, SSE_ALIGNEMENT);
        Vector4d* arrayB = alignMalloc<Vector4d>(size, SSE_ALIGNEMENT);
        benchmark::DoNotOptimize(arrayA);
        benchmark::DoNotOptimize(arrayA);

        for (auto _ : state)
        {
            double result = 0.0;

            for (std::size_t i = 0; i < size; ++i)
            {
                result += Vector4d::dot(arrayA[i], arrayA[i]);
            }

            benchmark::DoNotOptimize(result);
        }

        freeAlignedMalloc(arrayA);
        freeAlignedMalloc(arrayB);
    }
    BENCHMARK(BM_Vector4dDot_Array_Aligned);

    void BM_Vector4dDot_Array_Aligned_NoFalseSharing(benchmark::State& state)
    {
        constexpr size_t size = 1024;
        Vector4d* arrayA = alignMalloc<Vector4d>(size, HardwareDestructiveInterferenceSize);
        Vector4d* arrayB = alignMalloc<Vector4d>(size, HardwareDestructiveInterferenceSize);

        benchmark::DoNotOptimize(arrayA);
        benchmark::DoNotOptimize(arrayA);

        for (auto _ : state)
        {
            double result = 0.0;
            for (std::size_t i = 0; i < size; ++i)
            {
                result += Vector4d::dot(arrayA[i], arrayA[i]);
            }

            benchmark::DoNotOptimize(result);
        }

        freeAlignedMalloc(arrayA);
        freeAlignedMalloc(arrayB);
    }
    BENCHMARK(BM_Vector4dDot_Array_Aligned_NoFalseSharing);

    void BM_Vector4dDot_Array_Aligned_NoFalseSharing_ToArray(benchmark::State& state)
    {
        constexpr size_t size = 1024;
        Vector4d* arrayA = alignMalloc<Vector4d>(size, HardwareDestructiveInterferenceSize);
        Vector4d* arrayB = alignMalloc<Vector4d>(size, HardwareDestructiveInterferenceSize);
        double* arrayResult = alignMalloc<double>(size, HardwareDestructiveInterferenceSize);
        benchmark::DoNotOptimize(arrayA);
        benchmark::DoNotOptimize(arrayB);
        benchmark::DoNotOptimize(arrayResult);

        for (auto _ : state)
        {
            for (std::size_t i = 0; i < size; ++i)
            {
                arrayResult[i] = Vector4d::dot(arrayA[i], arrayA[i]);
            }
        }

        freeAlignedMalloc(arrayA);
        freeAlignedMalloc(arrayB);
    }
    BENCHMARK(BM_Vector4dDot_Array_Aligned_NoFalseSharing_ToArray);
}

// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
// NOLINTEND(clang-analyzer-deadcode.DeadStores)
// NOLINTEND(misc-const-correctness)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)
