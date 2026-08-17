#include <Alloc.hpp>

namespace Alloc
{
    void freeAlignedMalloc(void* ptr)
    {
#if defined(_MSC_VER)
        _aligned_free(ptr);
#else
        std::free(ptr);
#endif // defined(_MSC_VER)
    }
} // namespace Alloc
