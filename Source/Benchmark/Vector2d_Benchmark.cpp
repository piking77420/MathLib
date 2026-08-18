#include <array>
#include <cstddef>
#include <benchmark/benchmark.h>
#include <BenchmarkHeader.hpp>
#include <Alloc.hpp>
#include <MathLibHeader.hpp>
#include <Vector2d.hpp>

using namespace MathLib;
using namespace Alloc;

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(misc-const-correctness)
// NOLINTBEGIN(clang-analyzer-deadcode.DeadStores)
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)

namespace
{

    void BM_Vector2dDot(benchmark::State& _state)
    {
        Vector2d a(10.0, 20.0);
        Vector2d b(30.0, 40.0);

        for (auto _ : _state)
        {
            double result = Vector2d::dot(a, b);
            benchmark::DoNotOptimize(result);
        }
    }
    BENCHMARK(BM_Vector2dDot);

    void BM_Vector2dDot_Array(benchmark::State& _state)
    {
        std::array<Vector2d, 1024> a;
        std::array<Vector2d, 1024> b;

        benchmark::DoNotOptimize(a);
        benchmark::DoNotOptimize(b);

        for (auto _ : _state)
        {
            double result = 0.0;

            for (std::size_t i = 0; i < a.size(); ++i)
            {
                result += Vector2d::dot(a[i], b[i]);
            }

            benchmark::DoNotOptimize(result);
        }
    }
    BENCHMARK(BM_Vector2dDot_Array);

    void BM_Vector2dDot_Array_Aligned(benchmark::State& _state)
    {
        constexpr size_t size = 1024;
        Vector2d* arrayA = alignMalloc<Vector2d>(size, SSE_ALIGNEMENT);
        Vector2d* arrayB = alignMalloc<Vector2d>(size, SSE_ALIGNEMENT);
        benchmark::DoNotOptimize(arrayA);
        benchmark::DoNotOptimize(arrayA);

        for (auto _ : _state)
        {
            double result = 0.0;

            for (std::size_t i = 0; i < size; ++i)
            {
                result += Vector2d::dot(arrayA[i], arrayA[i]);
            }

            benchmark::DoNotOptimize(result);
        }

        freeAlignedMalloc(arrayA);
        freeAlignedMalloc(arrayB);
    }
    BENCHMARK(BM_Vector2dDot_Array_Aligned);

    void BM_Vector2dDot_Array_Aligned_NoFalseSharing(benchmark::State& _state)
    {
        constexpr size_t size = 1024;
        Vector2d* arrayA = alignMalloc<Vector2d>(size, HardwareDestructiveInterferenceSize);
        Vector2d* arrayB = alignMalloc<Vector2d>(size, HardwareDestructiveInterferenceSize);

        benchmark::DoNotOptimize(arrayA);
        benchmark::DoNotOptimize(arrayA);

        for (auto _ : _state)
        {
            double result = 0.0;
            for (std::size_t i = 0; i < size; ++i)
            {
                result += Vector2d::dot(arrayA[i], arrayA[i]);
            }

            benchmark::DoNotOptimize(result);
        }

        freeAlignedMalloc(arrayA);
        freeAlignedMalloc(arrayB);
    }
    BENCHMARK(BM_Vector2dDot_Array_Aligned_NoFalseSharing);

    void BM_Vector2dDot_Array_Aligned_NoFalseSharing_ToArray(benchmark::State& _state)
    {
        constexpr size_t size = 1024;
        Vector2d* arrayA = alignMalloc<Vector2d>(size, HardwareDestructiveInterferenceSize);
        Vector2d* arrayB = alignMalloc<Vector2d>(size, HardwareDestructiveInterferenceSize);
        double* arrayResult = alignMalloc<double>(size, HardwareDestructiveInterferenceSize);
        benchmark::DoNotOptimize(arrayA);
        benchmark::DoNotOptimize(arrayB);
        benchmark::DoNotOptimize(arrayResult);

        for (auto _ : _state)
        {
            for (std::size_t i = 0; i < size; ++i)
            {
                arrayResult[i] = Vector2d::dot(arrayA[i], arrayA[i]);
            }
        }

        freeAlignedMalloc(arrayA);
        freeAlignedMalloc(arrayB);
    }
    BENCHMARK(BM_Vector2dDot_Array_Aligned_NoFalseSharing_ToArray);
}

// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
// NOLINTEND(clang-analyzer-deadcode.DeadStores)
// NOLINTEND(misc-const-correctness)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)
