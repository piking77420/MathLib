#include <RandomNumber.hpp>

namespace MathLib::Benchmark
{
    double RandomNumber::real(double min, double max)
    {
        return std::uniform_real_distribution<double>(min, max)(m_rng);
    }

} // namespace MathLib::Benchmark
