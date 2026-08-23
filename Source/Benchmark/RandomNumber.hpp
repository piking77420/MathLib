#ifndef MATH_LIB_RANDOM_NUMBER_H
#define MATH_LIB_RANDOM_NUMBER_H

#include <numeric>
#include <random>

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

        double real(double min = std::numeric_limits<double>::lowest(),
                    double max = std::numeric_limits<double>::max());

    private:
        std::mt19937 m_rng;
    };

} // namespace MathLib::Benchmark

#endif // MATH_LIB_RANDOM_NUMBER_H
