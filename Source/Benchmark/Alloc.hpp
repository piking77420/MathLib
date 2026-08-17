#ifndef MATH_LIB_ALLOC_H
#define MATH_LIB_ALLOC_H

#include <bit>
#include <cstdlib>

#if defined(_MSC_VER)
#include <malloc.h>
#endif

#include <MathLibHeader.hpp>

namespace Alloc
{
    template<typename T>
    [[nodiscard]] T* alignMalloc(std::size_t _count, std::size_t _alignment)
    {
        const std::size_t size = sizeof(T) * _count;

#if defined(_MSC_VER)
        return static_cast<T*>(_aligned_malloc(size, _alignment));
#else
        // std::aligned_alloc requires size to be a multiple of alignment.
        return static_cast<T*>(std::aligned_alloc(_alignment, MathLib::alignedSize(size, _alignment)));
#endif
    }

    void freeAlignedMalloc(void* _ptr);

} // namespace Alloc

#endif // MATH_LIB_ALLOC_H
