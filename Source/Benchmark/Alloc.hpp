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
    [[nodiscard]] T* alignMalloc(std::size_t _count, std::size_t _alignment)
    {
        const std::size_t size = sizeof(T) * _count;
        static_assert(std::is_trivially_constructible_v<T>);
#if defined(_MSC_VER)
        return static_cast<T*>(
            _aligned_malloc(size, _alignment)); // NOLINT(cppcoreguidelines-owning-memory, cppcoreguidelines-no-malloc)
#else
        // std::aligned_alloc requires size to be a multiple of alignment.
        return static_cast<T*>(std::aligned_alloc(
            _alignment, MathLib::alignedSize(
                            size, _alignment))); // NOLINT(cppcoreguidelines-owning-memory, cppcoreguidelines-no-malloc)
#endif
    }

    void freeAlignedMalloc(void* _ptr);

} // namespace Alloc

#endif // MATH_LIB_ALLOC_H
