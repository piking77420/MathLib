#include <benchmark/benchmark.h>

#include <Vector2d.hpp>

using namespace MathLib;

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

BENCHMARK(BM_Vector2dDot);
BENCHMARK(BM_Vector2dAdd);
