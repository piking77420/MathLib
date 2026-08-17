#include <benchmark/benchmark.h>

#include <Alloc.hpp>
#include <Vector2d.hpp>

using namespace MathLib;
using namespace Alloc;

static void BM_Vector2dDot(benchmark::State& state)
{
    const Vector2d a(10.0, 20.0);
    const Vector2d b(30.0, 40.0);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(a);
        benchmark::DoNotOptimize(b);

        const double result = Vector2d::dot(a, b);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_Vector2dDot);

static void BM_Vector2dDot_Array(benchmark::State& state)
{
    std::array<Vector2d, 1024> a;
    std::array<Vector2d, 1024> b;

    // initialize outside benchmark loop
    benchmark::DoNotOptimize(a);
    benchmark::DoNotOptimize(b);

    for (auto _ : state)
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

static void BM_Vector2dDot_Array_Aligned(benchmark::State& state)
{
    constexpr size_t size = 1024;
    Vector2d* arrayA = alignMalloc<Vector2d>(size, SSE_ALIGNEMENT);
    Vector2d* arrayB = alignMalloc<Vector2d>(size, SSE_ALIGNEMENT);
    benchmark::DoNotOptimize(arrayA);
    benchmark::DoNotOptimize(arrayA);

    for (auto _ : state)
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

static void BM_Vector2dDot_Array_Aligned_NoFalseSharing(benchmark::State& state)
{
    constexpr size_t size = 1024;
    Vector2d* arrayA = alignMalloc<Vector2d>(size, std::hardware_destructive_interference_size);
    Vector2d* arrayB = alignMalloc<Vector2d>(size, std::hardware_destructive_interference_size);

    benchmark::DoNotOptimize(arrayA);
    benchmark::DoNotOptimize(arrayA);

    for (auto _ : state)
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

static void BM_Vector2dDot_Array_Aligned_NoFalseSharing_ToArray(benchmark::State& state)
{
    constexpr size_t size = 1024;
    Vector2d* arrayA = alignMalloc<Vector2d>(size, std::hardware_destructive_interference_size);
    Vector2d* arrayB = alignMalloc<Vector2d>(size, std::hardware_destructive_interference_size);
    double* arrayResult = alignMalloc<double>(size, std::hardware_destructive_interference_size);

    benchmark::DoNotOptimize(arrayA);
    benchmark::DoNotOptimize(arrayB);
    benchmark::DoNotOptimize(arrayResult);

    for (auto _ : state)
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

static void BM_Vector2dAdd(benchmark::State& state)
{
    const Vector2d a(10.0, 20.0);
    const Vector2d b(30.0, 40.0);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(a);
        benchmark::DoNotOptimize(b);

        const Vector2d result = a + b;
        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_Vector2dAdd);
