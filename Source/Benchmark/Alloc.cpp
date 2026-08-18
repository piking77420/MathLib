#include <Alloc.hpp>
#include <cstdlib>

// NOLINTBEGIN(cppcoreguidelines-no-malloc)
// NOLINTBEGIN(hicpp-no-malloc)
// NOLINTBEGIN(cppcoreguidelines-owning-memory)

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

// NOLINTEND(cppcoreguidelines-owning-memory)
// NOLINTEND(hicpp-no-malloc)
// NOLINTEND(cppcoreguidelines-no-malloc)
