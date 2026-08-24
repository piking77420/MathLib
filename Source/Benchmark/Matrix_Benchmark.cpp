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
#include <Vector2d.hpp>
#include <Vector3d.hpp>
#include <Vector4d.hpp>

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

template<typename T>
concept VectorMath = std::is_same_v<T, Vector2d> || std::is_same_v<T, Vector3d> || std::is_same_v<T, Vector4d>;

template<typename T>
concept MathType = Matrix<T> || VectorMath<T>;

template<MathType T>
struct MakeRandom
{
    T operator()([[maybe_unused]] MathLib::Benchmark::RandomNumber& randomNumber) const
    {
        return T();
    }
};

static constexpr double Min = -10.0;
static constexpr double Max = 10.0;

template<>
struct MakeRandom<Matrix2x2d>
{
    static Matrix2x2d operator()(MathLib::Benchmark::RandomNumber& randomNumber)
    {
        return Matrix2x2d(randomNumber.real(Min, Max), randomNumber.real(Min, Max), randomNumber.real(Min, Max),
                          randomNumber.real(Min, Max));
    }
};

template<>
struct MakeRandom<Matrix3x3d>
{
    static Matrix3x3d operator()(MathLib::Benchmark::RandomNumber& randomNumber)
    {

        return Matrix3x3d(randomNumber.real(Min, Max), randomNumber.real(Min, Max), randomNumber.real(Min, Max),
                          randomNumber.real(Min, Max), randomNumber.real(Min, Max), randomNumber.real(Min, Max),
                          randomNumber.real(Min, Max), randomNumber.real(Min, Max), randomNumber.real(Min, Max));
    }
};

template<>
struct MakeRandom<Matrix4x4d>
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

template<>
struct MakeRandom<Vector2d>
{
    static Vector2d operator()(MathLib::Benchmark::RandomNumber& randomNumber)
    {
        return Vector2d(randomNumber.real(Min, Max), randomNumber.real(Min, Max));
    }
};

template<>
struct MakeRandom<Vector3d>
{
    static Vector3d operator()(MathLib::Benchmark::RandomNumber& randomNumber)
    {
        return Vector3d(randomNumber.real(Min, Max), randomNumber.real(Min, Max), randomNumber.real(Min, Max));
    }
};

template<>
struct MakeRandom<Vector4d>
{
    static Vector4d operator()(MathLib::Benchmark::RandomNumber& randomNumber)
    {
        return Vector4d(randomNumber.real(Min, Max), randomNumber.real(Min, Max), randomNumber.real(Min, Max),
                        randomNumber.real(Min, Max));
    }
};

static constexpr size_t elemementCount = 1024ull;

template<MathType T, bool hardwareAlign = false>
static auto makeRandom() -> std::conditional_t<hardwareAlign, HardwareAlignedVector<T>, std::vector<T>>
{
    MathLib::Benchmark::RandomNumber randomNumber(0u);

    std::conditional_t<hardwareAlign, HardwareAlignedVector<T>, std::vector<T>> types;
    types.reserve(elemementCount);

    while (types.size() < elemementCount)
    {
        T m = MakeRandom<T>::operator()(randomNumber);

        if constexpr (Matrix<T>)
        {
            while (std::abs(m.determinant()) < DoubleEpsilon)
            {
                m = MakeRandom<T>::operator()(randomNumber);
            }
        }

        types.push_back(m);
    }

    return types;
}

namespace MathLib::Benchmark
{
    template<Matrix T, bool hardwareAlign>
    void BM_Determinant(benchmark::State& state)
    {
        static const auto matrices = makeRandom<T, hardwareAlign>();

        std::size_t i = 0;

        for (auto _ : state)
        {
            const T& m = matrices[i++ % matrices.size()];

            const auto determinant = m.determinant();

            benchmark::DoNotOptimize(determinant);
        }
    }

    template<Matrix T, bool hardwareAlign>
    void BM_Transpose(benchmark::State& state)
    {
        static const auto matrices = makeRandom<T, hardwareAlign>();

        std::size_t i = 0;

        for (auto _ : state)
        {
            const T& m = matrices[i++ % matrices.size()];

            const T transpose = m.getTranspose();

            benchmark::DoNotOptimize(transpose);
        }
    }

    template<Matrix T, bool hardwareAlign>
    void BM_Inverse(benchmark::State& state)
    {
        static const auto matrices = makeRandom<T, hardwareAlign>();

        std::size_t i = 0;

        for (auto _ : state)
        {
            const T& m = matrices[i++ % matrices.size()];

            const T inverse = m.getInverse();

            benchmark::DoNotOptimize(inverse);
        }
    }

    template<Matrix T, bool hardwareAlign>
    void BM_MultiplyVector(benchmark::State& state)
    {
        static const auto matrices = makeRandom<T, hardwareAlign>();
        static const auto vectors = makeRandom<typename T::_VectorType, hardwareAlign>();

        std::size_t i = 0;

        for (auto _ : state)
        {
            const T& m = matrices[i++ % matrices.size()];
            const typename T::_VectorType& v = vectors[i++ % vectors.size()];

            const typename T::_VectorType vec = m * v;

            benchmark::DoNotOptimize(vec);
            i++;
        }
    }
    static constexpr size_t iterationCount = 1'000'000ull;

#define MAKE_BENCHMARK_MATRIX(matrixType, hardwareAlign)                                                               \
    BENCHMARK_TEMPLATE(BM_Determinant, matrixType, hardwareAlign)->Iterations(iterationCount);                         \
    BENCHMARK_TEMPLATE(BM_Transpose, matrixType, hardwareAlign)->Iterations(iterationCount);                           \
    BENCHMARK_TEMPLATE(BM_Inverse, matrixType, hardwareAlign)->Iterations(iterationCount);                             \
    BENCHMARK_TEMPLATE(BM_MultiplyVector, matrixType, hardwareAlign)->Iterations(iterationCount);                      \
                                                                                                                       \
    BENCHMARK_TEMPLATE(BM_Determinant, matrixType, hardwareAlign)->Iterations(iterationCount);                         \
    BENCHMARK_TEMPLATE(BM_Transpose, matrixType, hardwareAlign)->Iterations(iterationCount);                           \
    BENCHMARK_TEMPLATE(BM_Inverse, matrixType, hardwareAlign)->Iterations(iterationCount);                             \
    BENCHMARK_TEMPLATE(BM_MultiplyVector, matrixType, hardwareAlign)->Iterations(iterationCount);

    namespace Matrix2x2dBenchmark
    {
        MAKE_BENCHMARK_MATRIX(Matrix2x2d, false);
        MAKE_BENCHMARK_MATRIX(Matrix2x2d, true);
    } // namespace Matrix2x2dBenchmark

    namespace Matrix3x3Benchmark
    {
        MAKE_BENCHMARK_MATRIX(Matrix3x3d, false);
        MAKE_BENCHMARK_MATRIX(Matrix3x3d, true);

    } // namespace Matrix3x3Benchmark

    namespace Matrix4x4Benchmark
    {
        MAKE_BENCHMARK_MATRIX(Matrix4x4d, false);
        MAKE_BENCHMARK_MATRIX(Matrix4x4d, true);

    } // namespace Matrix4x4Benchmark
}
//  MathLib::Benchmark
// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
// NOLINTEND(clang-analyzer-deadcode.DeadStores)
// NOLINTEND(misc-const-correctness)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)
