#ifndef MATH_LIB_VECTOR_BENCHMARK_H
#define MATH_LIB_VECTOR_BENCHMARK_H

#include <cstddef>
#include <benchmark/benchmark.h>
#include <BenchmarkHeader.hpp>
#include <BenchmarkMaker.hpp>
#include <MathLibHeader.hpp>
#include <Vector2d.hpp>
#include <Vector3d.hpp>
#include <Vector4d.hpp>

using namespace MathLib;
using namespace MathLib::Benchmark;

// NOLINTBEGIN(cppcoreguidelines-macro-usage)
// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(misc-const-correctness)
// NOLINTBEGIN(clang-analyzer-deadcode.DeadStores)
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)

namespace MathLib::Benchmark
{
    template<VectorMath T, bool hardwareAlign>
    void dot(benchmark::State& state)
    {
        static const auto vectors = makeRandom<T, hardwareAlign>();
        std::size_t i = 0;
        for (auto _ : state)
        {
            const T& v1 = vectors[i++ % vectors.size()];
            const T& v2 = vectors[i++ % vectors.size()];
            auto result = T::dot(v1, v2);
            benchmark::DoNotOptimize(result);
        }
    }

    template<VectorMath T, bool hardwareAlign>
    void lengthSquare(benchmark::State& state)
    {
        static const auto vectors = makeRandom<T, hardwareAlign>();
        std::size_t i = 0;
        for (auto _ : state)
        {
            const T& v = vectors[i++ % vectors.size()];
            auto result = v.lengthSquare();
            benchmark::DoNotOptimize(result);
        }
    }

    template<VectorMath T, bool hardwareAlign>
    void length(benchmark::State& state)
    {
        static const auto vectors = makeRandom<T, hardwareAlign>();
        std::size_t i = 0;
        for (auto _ : state)
        {
            const T& v = vectors[i++ % vectors.size()];
            auto result = v.length();
            benchmark::DoNotOptimize(result);
        }
    }

    template<VectorMath T, bool hardwareAlign>
    void distanceSquare(benchmark::State& state)
    {
        static const auto vectors = makeRandom<T, hardwareAlign>();

        std::size_t i = 0;

        for (auto _ : state)
        {
            const T& v1 = vectors[i++ % vectors.size()];
            const T& v2 = vectors[i++ % vectors.size()];

            auto result = T::distanceSquare(v1, v2);

            benchmark::DoNotOptimize(result);
        }
    }

    template<VectorMath T, bool hardwareAlign>
    void distance(benchmark::State& state)
    {
        static const auto vectors = makeRandom<T, hardwareAlign>();

        std::size_t i = 0;

        for (auto _ : state)
        {
            const T& v1 = vectors[i++ % vectors.size()];
            const T& v2 = vectors[i++ % vectors.size()];

            auto result = T::distance(v1, v2);

            benchmark::DoNotOptimize(result);
        }
    }

    template<VectorMath T, bool hardwareAlign>
    void getNormalize(benchmark::State& state)
    {
        static const auto vectors = makeRandom<T, hardwareAlign>();

        std::size_t i = 0;

        for (auto _ : state)
        {
            const T& v = vectors[i++ % vectors.size()];

            auto result = v.getNormalize();

            benchmark::DoNotOptimize(result);
        }
    }

    template<VectorMath T, bool hardwareAlign>
    void getNormalizeFast(benchmark::State& state)
    {
        static const auto vectors = makeRandom<T, hardwareAlign>();

        std::size_t i = 0;

        for (auto _ : state)
        {
            const T& v = vectors[i++ % vectors.size()];

            auto result = v.getNormalizeFast();

            benchmark::DoNotOptimize(result);
        }
    }

    template<VectorMath T, bool hardwareAlign>
    void cross(benchmark::State& state)
    {
        static const auto vectors = makeRandom<T, hardwareAlign>();

        std::size_t i = 0;

        for (auto _ : state)
        {
            const T& v1 = vectors[i++ % vectors.size()];
            const T& v2 = vectors[i++ % vectors.size()];

            if constexpr (std::is_same_v<T, Vector4<double>>)
            {
                const T& v3 = vectors[i++ % vectors.size()];
                auto result = T::cross(v1, v2, v3);
                benchmark::DoNotOptimize(result);
            }
            else
            {
                auto result = T::cross(v1, v2);
                benchmark::DoNotOptimize(result);
            }
        }
    }

    template<VectorMath T, bool hardwareAlign>
    void max(benchmark::State& state)
    {
        static const auto vectors = makeRandom<T, hardwareAlign>();

        std::size_t i = 0;

        for (auto _ : state)
        {
            const T& v1 = vectors[i++ % vectors.size()];
            const T& v2 = vectors[i++ % vectors.size()];

            auto result = T::max(v1, v2);

            benchmark::DoNotOptimize(result);
        }
    }

    template<VectorMath T, bool hardwareAlign>
    void min(benchmark::State& state)
    {
        static const auto vectors = makeRandom<T, hardwareAlign>();

        std::size_t i = 0;

        for (auto _ : state)
        {
            const T& v1 = vectors[i++ % vectors.size()];
            const T& v2 = vectors[i++ % vectors.size()];

            auto result = T::min(v1, v2);

            benchmark::DoNotOptimize(result);
        }
    }

    template<VectorMath T, bool hardwareAlign>
    void abs(benchmark::State& state)
    {
        static const auto vectors = makeRandom<T, hardwareAlign>();
        std::size_t i = 0;
        for (auto _ : state)
        {
            const T& v = vectors[i++ % vectors.size()];
            auto result = v.abs();
            benchmark::DoNotOptimize(result);
        }
    }

#define MAKE_BENCHMARK_VECTOR(VectorType, HardwareAlign)                                                               \
    BENCHMARK_TEMPLATE(dot, VectorType, HardwareAlign);                                                                \
    BENCHMARK_TEMPLATE(lengthSquare, VectorType, HardwareAlign);                                                       \
    BENCHMARK_TEMPLATE(length, VectorType, HardwareAlign);                                                             \
    BENCHMARK_TEMPLATE(distanceSquare, VectorType, HardwareAlign);                                                     \
    BENCHMARK_TEMPLATE(distance, VectorType, HardwareAlign);                                                           \
    BENCHMARK_TEMPLATE(getNormalize, VectorType, HardwareAlign);                                                       \
    BENCHMARK_TEMPLATE(getNormalizeFast, VectorType, HardwareAlign);                                                   \
    BENCHMARK_TEMPLATE(cross, VectorType, HardwareAlign);                                                              \
    BENCHMARK_TEMPLATE(min, VectorType, HardwareAlign);                                                                \
    BENCHMARK_TEMPLATE(max, VectorType, HardwareAlign);                                                                \
    BENCHMARK_TEMPLATE(abs, VectorType, HardwareAlign);

    namespace Vector2Benchmark
    {
        MAKE_BENCHMARK_VECTOR(Vector2d, falseSharing);
        MAKE_BENCHMARK_VECTOR(Vector2d, avoidFalseSharing);
    } // namespace Vector2Benchmark

    namespace Vector3Benchmark
    {
        MAKE_BENCHMARK_VECTOR(Vector3d, falseSharing);
        MAKE_BENCHMARK_VECTOR(Vector3d, avoidFalseSharing);

    } // namespace Vector3Benchmark

    namespace Vector4Benchmark
    {
        MAKE_BENCHMARK_VECTOR(Vector4d, falseSharing);
        MAKE_BENCHMARK_VECTOR(Vector4d, avoidFalseSharing);

    } // namespace Vector4Benchmark

} // MathLib::Benchmark

// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
// NOLINTEND(clang-analyzer-deadcode.DeadStores)
// NOLINTEND(misc-const-correctness)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)
// NOLINTEND(cppcoreguidelines-macro-usage)

#endif // MATH_LIB_VECTOR_BENCHMARK_H
