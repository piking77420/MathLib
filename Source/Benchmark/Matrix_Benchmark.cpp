#include <array>
#include <cstddef>
#include <benchmark/benchmark.h>
#include <Alloc.hpp>
#include <BenchmarkHeader.hpp>
#include <RandomNumber.hpp>
#include <MathLibHeader.hpp>
#include <Matrix2x2d.hpp>
#include <Matrix3x3d.hpp>
#include <Matrix4x4d.hpp>

using namespace MathLib;
using namespace Alloc;
using namespace MathLib::Benchmark;

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(misc-const-correctness)
// NOLINTBEGIN(clang-analyzer-deadcode.DeadStores)
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)

template<typename T>
concept Matrix = std::is_same_v<T, Matrix2x2d> || std::is_same_v<T, Matrix3x3d> || std::is_same_v<T, Matrix4x4d>;

template<Matrix T>
struct MakeRandomMatrix
{
    T operator()([[maybe_unused]] MathLib::Benchmark::RandomNumber& randomNumber) const
    {
        return T();
    }
};

static constexpr double Min = -10.0;
static constexpr double Max = 10.0;

template<>
struct MakeRandomMatrix<Matrix2x2d>
{
    static Matrix2x2d operator()(MathLib::Benchmark::RandomNumber& randomNumber)
    {
        return Matrix2x2d(randomNumber.real(Min, Max), randomNumber.real(Min, Max), randomNumber.real(Min, Max),
                          randomNumber.real(Min, Max));
    }
};

template<>
struct MakeRandomMatrix<Matrix3x3d>
{
    static Matrix3x3d operator()(MathLib::Benchmark::RandomNumber& randomNumber)
    {

        return Matrix3x3d(randomNumber.real(Min, Max), randomNumber.real(Min, Max), randomNumber.real(Min, Max),
                          randomNumber.real(Min, Max), randomNumber.real(Min, Max), randomNumber.real(Min, Max),
                          randomNumber.real(Min, Max), randomNumber.real(Min, Max), randomNumber.real(Min, Max));
    }
};

template<>
struct MakeRandomMatrix<Matrix4x4d>
{
    static Matrix4x4d operator()(MathLib::Benchmark::RandomNumber& randomNumber)
    {
        return Matrix4x4d(randomNumber.real(Min, Max), randomNumber.real(Min, Max), randomNumber.real(Min, Max),
                          randomNumber.real(Min, Max), randomNumber.real(Min, Max), randomNumber.real(Min, Max),
                          randomNumber.real(Min, Max), randomNumber.real(Min, Max), randomNumber.real(Min, Max),
                          randomNumber.real(Min, Max), randomNumber.real(Min, Max), randomNumber.real(Min, Max),
                          randomNumber.real(Min, Max), randomNumber.real(Min, Max), randomNumber.real(Min, Max),
                          randomNumber.real(Min, Max));
    }
};

template<Matrix T>
static std::vector<T> makeMatrices()
{
    MathLib::Benchmark::RandomNumber randomNumber(0u);
    static constexpr size_t elemementCount = 1024ull;

    std::vector<T> matrices;
    matrices.reserve(elemementCount);

    while (matrices.size() < elemementCount)
    {
        T m = MakeRandomMatrix<T>::operator()(randomNumber);

        while (std::abs(m.determinant()) < DoubleEpsilon)
        {
            m = MakeRandomMatrix<T>::operator()(randomNumber);
        }
        matrices.push_back(m);
    }

    return matrices;
}

namespace MathLib::Benchmark
{
    template<Matrix T>
    void BM_Determinant(benchmark::State& state)
    {
        static const auto matrices = makeMatrices<T>();

        std::size_t i = 0;

        for (auto _ : state)
        {
            const T& m = matrices[i++ % matrices.size()];

            const auto determinant = m.determinant();

            benchmark::DoNotOptimize(determinant);
        }
    }

    template<Matrix T>
    void BM_Transpose(benchmark::State& state)
    {
        static const auto matrices = makeMatrices<T>();

        std::size_t i = 0;

        for (auto _ : state)
        {
            const T& m = matrices[i++ % matrices.size()];

            const T transpose = m.getTranspose();

            benchmark::DoNotOptimize(transpose);
        }
    }

    template<Matrix T>
    void BM_Inverse(benchmark::State& state)
    {
        static const auto matrices = makeMatrices<T>();

        std::size_t i = 0;

        for (auto _ : state)
        {
            const T& m = matrices[i++ % matrices.size()];

            const T inverse = m.getInverse();

            benchmark::DoNotOptimize(inverse);
        }
    }

    namespace Matrix2x2dBenchmark
    {
        BENCHMARK_TEMPLATE(BM_Determinant, Matrix2x2d);
        BENCHMARK_TEMPLATE(BM_Transpose, Matrix2x2d);
        BENCHMARK_TEMPLATE(BM_Inverse, Matrix2x2d);

    } // namespace Matrix2x2dBenchmark

    namespace Matrix3x3Benchmark
    {
        BENCHMARK_TEMPLATE(BM_Determinant, Matrix3x3d);
        BENCHMARK_TEMPLATE(BM_Transpose, Matrix3x3d);
        BENCHMARK_TEMPLATE(BM_Inverse, Matrix3x3d);
    } // namespace Matrix2x2dBenchmark

    namespace Matrix4x4Benchmark
    {
        BENCHMARK_TEMPLATE(BM_Determinant, Matrix4x4d);
        BENCHMARK_TEMPLATE(BM_Transpose, Matrix4x4d);
        BENCHMARK_TEMPLATE(BM_Inverse, Matrix4x4d);
    } // namespace Matrix2x2dBenchmark
}
//  MathLib::Benchmark
// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
// NOLINTEND(clang-analyzer-deadcode.DeadStores)
// NOLINTEND(misc-const-correctness)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)
