#ifndef MATH_LIB_ALLOC_H
#define MATH_LIB_ALLOC_H

#include <cstdlib>

#if defined(_MSC_VER)
#include <malloc.h>
#endif

#include <MathLibHeader.hpp>

namespace Alloc
{
    template<typename T>
    [[nodiscard]] T* alignMalloc(std::size_t count, std::size_t alignment)
    {
        const std::size_t size = sizeof(T) * count;
        static_assert(std::is_trivially_constructible_v<T>);
#if defined(_MSC_VER)
        return static_cast<T*>(_aligned_malloc(size, alignment));
#else
        // std::aligned_alloc requires size to be a multiple of alignment.
        return static_cast<T*>(std::aligned_alloc(alignment, MathLib::alignedSize(size, alignment)));
#endif
    }

    void freeAlignedMalloc(void* ptr);

} // namespace Alloc

#endif // MATH_LIB_ALLOC_H
