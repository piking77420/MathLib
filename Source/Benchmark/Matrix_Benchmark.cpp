#ifndef MATH_LIB_MATRIX_BENCHMARK_H
#define MATH_LIB_MATRIX_BENCHMARK_H

#include <cstddef>
#include <benchmark/benchmark.h>
#include <BenchmarkHeader.hpp>
#include <BenchmarkMaker.hpp>
#include <MathLibHeader.hpp>
#include <Matrix2x2d.hpp>
#include <Matrix3x3d.hpp>
#include <Matrix4x4d.hpp>
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
    template<Matrix T, bool hardwareAlign>
    void determinant(benchmark::State& state)
    {
        static const auto matrices = makeRandom<T, hardwareAlign>();
        std::size_t i = 0;
        for (auto _ : state)
        {
            const T& m = matrices[i++ % matrices.size()];
            const auto result = m.determinant();
            benchmark::DoNotOptimize(result);
        }
    }

    template<Matrix T, bool hardwareAlign>
    void transpose(benchmark::State& state)
    {
        static const auto matrices = makeRandom<T, hardwareAlign>();
        std::size_t i = 0;
        for (auto _ : state)
        {
            const T& m = matrices[i++ % matrices.size()];
            const auto transpose = m.getTranspose();
            benchmark::DoNotOptimize(transpose);
        }
    }

    template<Matrix T, bool hardwareAlign>
    void inverse(benchmark::State& state)
    {
        static const auto matrices = makeRandom<T, hardwareAlign>();
        std::size_t i = 0;
        for (auto _ : state)
        {
            const T& m = matrices[i++ % matrices.size()];
            const auto inverse = m.getInverse();

            benchmark::DoNotOptimize(inverse);
        }
    }

    template<Matrix T, bool hardwareAlign>
    void multiplyVector(benchmark::State& state)
    {
        static const auto matrices = makeRandom<T, hardwareAlign>();
        static const auto vectors = makeRandom<typename T::_VectorType, hardwareAlign>();
        std::size_t i = 0;
        for (auto _ : state)
        {
            const T& m = matrices[i++ % matrices.size()];
            const auto& v = vectors[i % vectors.size()];
            auto result = m * v;
            benchmark::DoNotOptimize(result);
        }
    }
    static constexpr size_t iterationCount = 1'000'000ull;

#define MAKE_BENCHMARK_MATRIX(MatrixType, HardwareAlign)                                                               \
    BENCHMARK_TEMPLATE(determinant, MatrixType, HardwareAlign);                                                        \
    BENCHMARK_TEMPLATE(transpose, MatrixType, HardwareAlign);                                                          \
    BENCHMARK_TEMPLATE(inverse, MatrixType, HardwareAlign);                                                            \
    BENCHMARK_TEMPLATE(multiplyVector, MatrixType, HardwareAlign);

    namespace Matrix2x2dBenchmark
    {
        MAKE_BENCHMARK_MATRIX(Matrix2x2d, falseSharing);
        MAKE_BENCHMARK_MATRIX(Matrix2x2d, avoidFalseSharing);
    } // namespace Matrix2x2dBenchmark

    namespace Matrix3x3Benchmark
    {
        MAKE_BENCHMARK_MATRIX(Matrix3x3d, falseSharing);
        MAKE_BENCHMARK_MATRIX(Matrix3x3d, avoidFalseSharing);

    } // namespace Matrix3x3Benchmark

    namespace Matrix4x4Benchmark
    {
        MAKE_BENCHMARK_MATRIX(Matrix4x4d, falseSharing);
        MAKE_BENCHMARK_MATRIX(Matrix4x4d, avoidFalseSharing);

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
