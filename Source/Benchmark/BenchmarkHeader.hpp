#ifndef MATH_LIB_BENDCHMARK_HEADER_H
#define MATH_LIB_BENDCHMARK_HEADER_H
#include <cstddef>

// NOLINTBEGIN(cppcoreguidelines-macro-usage)

namespace MathLib
{
#if defined(__cpp_lib_hardware_interference_size)
#include <new>
    inline constexpr size_t hardwareConstructiveInterferenceSize = std::hardware_constructive_interference_size;
    inline constexpr size_t HardwareDestructiveInterferenceSize = std::hardware_destructive_interference_size;
#elif defined(__GCC_CONSTRUCTIVE_SIZE) && defined(__GCC_DESTRUCTIVE_SIZE)
    inline constexpr size_t hardwareConstructiveInterferenceSize = __GCC_CONSTRUCTIVE_SIZE;
    inline constexpr size_t HardwareDestructiveInterferenceSize = __GCC_DESTRUCTIVE_SIZE;
#else
    // clang 18 dont support std::hardware_constructive_interference_size and
    // std::hardware_destructive_interference_size clang 19 support __GCC_CONSTRUCTIVE_SIZE and __GCC_DESTRUCTIVE_SIZE
    // https://github.com/llvm/llvm-project/pull/89446#issuecomment-2070649367
    // custom implementation since gihub ci run on clang18
#if defined(__x86_64__) || defined(_M_X64)

    // x86-64
    inline constexpr size_t hardwareConstructiveInterferenceSize = 64;
    inline constexpr size_t HardwareDestructiveInterferenceSize = 64;

#elif defined(__i386__) || defined(_M_IX86)

    // x86-32
    inline constexpr size_t hardwareConstructiveInterferenceSize = 64;
    inline constexpr size_t HardwareDestructiveInterferenceSize = 64;
#elif defined(__aarch64__) || defined(_M_ARM64)

    inline constexpr size_t hardwareConstructiveInterferenceSize = 64;
    inline constexpr size_t HardwareDestructiveInterferenceSize = 256;

#elif defined(__powerpc64__) || defined(__ppc64__) || defined(_ARCH_PPC64)

    inline constexpr size_t hardwareConstructiveInterferenceSize = 128;
    inline constexpr size_t HardwareDestructiveInterferenceSize = 128;

#elif defined(__s390x__)

    inline constexpr size_t hardwareConstructiveInterferenceSize = 256;
    inline constexpr size_t HardwareDestructiveInterferenceSize = 256;

#elif defined(__AVR__) || defined(__BPF__) || defined(__m68k__) || defined(__mips__) || defined(__powerpc__) ||        \
    defined(__ppc__) || defined(__PPC__) || defined(__riscv) || defined(__sparc__)

    inline constexpr size_t hardwareConstructiveInterferenceSize = 32;
    inline constexpr size_t HardwareDestructiveInterferenceSize = 32;

#else

#error "Unsupported architecture"

#endif // defined(__x86_64__) || defined(_M_X64)

#endif // __cpp_lib_hardware_interference_size

    static constexpr bool falseSharing = false;
    static constexpr bool avoidFalseSharing = true;

} // MathLib

// NOLINTEND(cppcoreguidelines-macro-usage)
#endif // MATH_LIB_BENDCHMARK_HEADER_H
