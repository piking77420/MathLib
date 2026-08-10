#include <CpuInstructionSet.hpp>

// https://learn.microsoft.com/en-us/cpp/intrinsics/cpuid-cpuidex?view=msvc-140
// https://gcc.gnu.org/onlinedocs/gcc-16.1.0/gcc/x86-Built-in-Functions.html

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(misc-include-cleaner)
// NOLINTBEGIN(misc-use-anonymous-namespace)
// NOLINTBEGIN(hicpp-no-assemble)

#if CPU_ARM_64
#include <sys/auxv.h>
#include <asm/hwcap.h>
#endif

namespace MathLib
{
#if CPU_X86_64
    struct CpuidRegisters
    {
        std::uint32_t eax{};
        std::uint32_t ebx{};
        std::uint32_t ecx{};
        std::uint32_t edx{};
    };

    [[nodiscard]] static inline CpuidRegisters cpuid(std::uint32_t _leaf, std::uint32_t _subleaf = 0) noexcept
    {
        CpuidRegisters result{};

#if defined(_MSC_VER)

        int registers[4];

        __cpuidex(registers, static_cast<int>(_leaf), static_cast<int>(_subleaf));

        result.eax = static_cast<std::uint32_t>(registers[0]);
        result.ebx = static_cast<std::uint32_t>(registers[1]);
        result.ecx = static_cast<std::uint32_t>(registers[2]);
        result.edx = static_cast<std::uint32_t>(registers[3]);

#elif defined(__GNUC__) || defined(__clang__)

        __cpuid_count(_leaf, _subleaf, result.eax, result.ebx, result.ecx, result.edx);

#endif

        return result;
    }

    [[nodiscard]] inline std::uint32_t maximumCpuidLeaf() noexcept
    {
#if defined(_MSC_VER)

        int registers[4];
        __cpuid(registers, 0);

        return static_cast<std::uint32_t>(registers[0]);

#elif defined(__GNUC__) || defined(__clang__)

        return __get_cpuid_max(0, nullptr);

#else

        return 0;

#endif
    }

    [[nodiscard]] static inline std::uint64_t xgetbv(const std::uint32_t _index) noexcept
    {
#if defined(_MSC_VER)

        return _xgetbv(_index);

#elif defined(__GNUC__) || defined(__clang__)

        std::uint32_t low{};
        std::uint32_t high{};

        __asm__ volatile("xgetbv" : "=a"(low), "=d"(high) : "c"(_index));

        return static_cast<std::uint64_t>(low) | (static_cast<std::uint64_t>(high) << 32);

#else

        return 0;

#endif
    }

    [[nodiscard]] static constexpr bool hasBit(const std::uint32_t _value, const std::uint32_t _bit) noexcept
    {
        return (_value & (std::uint32_t{1} << _bit)) != 0;
    }
#endif // CPU_X86_64

    CpuInstructionSet::CpuInstructionSet()
    {
#if CPU_X86_64

        const std::uint32_t maximumLeaf = maximumCpuidLeaf();

        if (maximumLeaf < 1)
        {
            return;
        }
        const CpuidRegisters leaf1 = cpuid(1);

        // CPUID leaf 1, EDX
        sse = hasBit(leaf1.edx, 25);

        const bool cpuAvx = hasBit(leaf1.ecx, 28);
        const bool osxsave = hasBit(leaf1.ecx, 27);

        std::uint64_t xcr0 = 0;

        if (osxsave)
        {
            xcr0 = xgetbv(0);
        }

        constexpr std::uint64_t AvxState = (std::uint64_t{1} << 1) | // XMM
                                           (std::uint64_t{1} << 2);  // YMM

        const bool osSupportsAvx = osxsave && (xcr0 & AvxState) == AvxState;

        avx = cpuAvx && osSupportsAvx;

        if (maximumLeaf < 7)
        {
            return;
        }

        const CpuidRegisters leaf7 = cpuid(7, 0);
        const bool cpuAvx2 = hasBit(leaf7.ebx, 5);

        avx2 = cpuAvx2 && avx;
#elif CPU_ARM_64
        const unsigned long hwcap = getauxval(AT_HWCAP);
        neon = (hwcap & HWCAP_ASIMD) != 0;
        sve = (hwcap & HWCAP_SVE) != 0;
#endif // CPU_X86_64
    }

} // namespace MathLib

// NOLINTEND(hicpp-no-assemble)
// NOLINTEND(misc-use-anonymous-namespace)
// NOLINTEND(misc-include-cleaner)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
