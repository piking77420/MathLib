#ifndef MATH_LIB_MATRIX_BENCHMARK_H
#define MATH_LIB_MATRIX_BENCHMARK_H

#include <cstddef>
#include <cstdint>
#include <benchmark/benchmark.h>
#include <BenchmarkHeader.hpp>
#include <BenchmarkMaker.hpp>
#include <MathLibHeader.hpp>

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
    template<Matrix T, bool hardwareAlign>
    void determinant(benchmark::State& state)
    {
        static const auto matrices = makeRandom<T, hardwareAlign>();
        size_t i = 0;
        constexpr int64_t batchSize = 32;
        for (auto _ : state)
        {
            for (size_t j = 0; j < batchSize; ++j)
            {
                const T& m = matrices[i];
                auto result = m.determinant();
                benchmark::DoNotOptimize(result);
                ++i;
                if (i == matrices.size())
                    i = 0;
            }
        }
        state.SetItemsProcessed(state.iterations() * batchSize);
    }

    template<Matrix T, bool hardwareAlign>
    void transposeInPlace(benchmark::State& state)
    {
        static const auto matrices = makeRandom<T, hardwareAlign>();
        size_t i = 0;
        constexpr int64_t batchSize = 32;

        for (auto _ : state)
        {
            for (size_t j = 0; j < batchSize; ++j)
            {
                T result = matrices[i];
                result.transpose();
                benchmark::DoNotOptimize(result);
                ++i;
                if (i == matrices.size())
                    i = 0;
            }
        }
        state.SetItemsProcessed(state.iterations() * batchSize);
    }

    template<Matrix T, bool hardwareAlign>
    void inverse(benchmark::State& state)
    {
        static const auto matrices = makeRandom<T, hardwareAlign>();
        size_t i = 0;
        constexpr int64_t batchSize = 32;

        for (auto _ : state)
        {
            for (size_t j = 0; j < batchSize; ++j)
            {
                const T& m = matrices[i];
                auto inverse = m.getInverse();

                benchmark::DoNotOptimize(inverse);
                ++i;
                if (i == matrices.size())
                    i = 0;
            }
        }
        state.SetItemsProcessed(state.iterations() * batchSize);
    }

    template<Matrix T, bool hardwareAlign>
    void multiplyVector(benchmark::State& state)
    {
        static const auto matrices = makeRandom<T, hardwareAlign>();
        static const auto vectors = makeRandom<typename T::_VectorType, hardwareAlign>();
        size_t i = 0;
        constexpr int64_t batchSize = 32;

        for (auto _ : state)
        {
            for (size_t j = 0; j < batchSize; ++j)
            {
                const T& m = matrices[i];
                const auto& v = vectors[i];
                auto result = m * v;
                benchmark::DoNotOptimize(result);
                ++i;
                if (i == matrices.size())
                    i = 0;
            }
        }

        state.SetItemsProcessed(state.iterations() * batchSize);
    }

    static constexpr size_t iterationCount = 1'000'000ull;

#define MAKE_BENCHMARK_MATRIX(MatrixType, HardwareAlign)                                                               \
    BENCHMARK_TEMPLATE(determinant, MatrixType, HardwareAlign)                                                         \
        ->MinTime(1.0)                                                                                                 \
        ->Repetitions(10)                                                                                              \
        ->ReportAggregatesOnly(true);                                                                                  \
    BENCHMARK_TEMPLATE(transposeInPlace, MatrixType, HardwareAlign)                                                    \
        ->MinTime(1.0)                                                                                                 \
        ->Repetitions(10)                                                                                              \
        ->ReportAggregatesOnly(true);                                                                                  \
    BENCHMARK_TEMPLATE(inverse, MatrixType, HardwareAlign)->MinTime(1.0)->Repetitions(10)->ReportAggregatesOnly(true); \
    BENCHMARK_TEMPLATE(multiplyVector, MatrixType, HardwareAlign)                                                      \
        ->MinTime(1.0)                                                                                                 \
        ->Repetitions(10)                                                                                              \
        ->ReportAggregatesOnly(true);

    namespace Matrix2x2dBenchmark
    {
        // MAKE_BENCHMARK_MATRIX(Matrix2x2d, falseSharing);
    } // namespace Matrix2x2dBenchmark

    namespace Matrix3x3Benchmark
    {
        // MAKE_BENCHMARK_MATRIX(Matrix3x3d, falseSharing);

    } // namespace Matrix3x3Benchmark

    namespace Matrix4x4Benchmark
    {
        MAKE_BENCHMARK_MATRIX(Matrix4x4d, falseSharing);

    } // namespace Matrix4x4Benchmark
}
//  MathLib::Benchmark

// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
// NOLINTEND(clang-analyzer-deadcode.DeadStores)
// NOLINTEND(misc-const-correctness)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)
// NOLINTEND(cppcoreguidelines-macro-usage)

#endif // MATH_LIB_MATRIX_BENCHMARK_H
