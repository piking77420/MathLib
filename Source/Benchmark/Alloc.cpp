#include <Alloc.hpp>

namespace Alloc
{
    void freeAlignedMalloc(void* _ptr)
    {
#if defined(_MSC_VER)
        _aligned_free(_ptr);
#else
        std::free(_ptr);
#endif // defined(_MSC_VER)
    }
} // namespace Alloc
