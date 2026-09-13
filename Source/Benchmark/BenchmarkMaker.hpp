#ifndef MATH_LIB_BENCHMARK_MAKER_H
#define MATH_LIB_BENCHMARK_MAKER_H

#include <numeric>
#include <random>
#include <BenchmarkHeader.hpp>
#include <HardwareAlignedVector.hpp>
#include <MathLibHeader.hpp>
#include <Matrix2x2.hpp>
#include <Matrix3x3.hpp>
#include <Matrix4x4.hpp>
#include <Vector2.hpp>
#include <Vector3.hpp>
#include <Vector4.hpp>

namespace MathLib::Benchmark
{
    class RandomNumber
    {
    public:
        explicit RandomNumber(std::uint32_t seed)
            : m_rng(seed)
        {
        }

        ~RandomNumber() = default;

        double real(double min = std::numeric_limits<double>::lowest(), double max = std::numeric_limits<double>::max())
        {
            return std::uniform_real_distribution<double>(min, max)(m_rng);
        }

    private:
        std::mt19937 m_rng;
    };

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
    struct MakeRandom<Vector2<double>>
    {
        static Vector2<double> operator()(MathLib::Benchmark::RandomNumber& randomNumber)
        {
            return Vector2<double>(randomNumber.real(Min, Max), randomNumber.real(Min, Max));
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

} // namespace MathLib::Benchmark

#endif // MATH_LIB_BENCHMARK_MAKER_H
