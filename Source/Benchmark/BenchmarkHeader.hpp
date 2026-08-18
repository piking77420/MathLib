#ifndef MATH_LIB_BENDCHMARK_HEADER_H
#define MATH_LIB_BENDCHMARK_HEADER_H

namespace MathLib
{
#if defined(_MSC_VER)
#include <new>
    static constexpr size_t hardware_destructive_interference_size = std::hardware_destructive_interference_size;
#elif defined(__clang__) || defined(__GNUC__)
    static constexpr size_t hardware_destructive_interference_size = __GCC_DESTRUCTIVE_SIZE;
#endif // defined(_MSC_VER)

} // MathLib

#endif // MATH_LIB_BENDCHMARK_HEADER_H
