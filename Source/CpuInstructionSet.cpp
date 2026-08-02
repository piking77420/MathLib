#include <array>

#include <CpuInstructionSet.hpp>
#include <CompilerDetection.hpp>

// https://learn.microsoft.com/en-us/cpp/intrinsics/cpuid-cpuidex?view=msvc-140
// https://gcc.gnu.org/onlinedocs/gcc-16.1.0/gcc/x86-Built-in-Functions.html

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(misc-include-cleaner)
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

namespace MathLib
{
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

        std::array<int, 4> registers{};
        __cpuid(registers.data(), 0);

        return static_cast<std::uint32_t>(registers[0]);

#elif defined(__GNUC__) || defined(__clang__)

        return __get_cpuid_max(0, nullptr);

#else

        return 0;

#endif
    }

    [[nodiscard]] inline std::uint64_t xgetbv(std::uint32_t _index) noexcept
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

    [[nodiscard]] constexpr bool hasBit(std::uint32_t _value, std::uint32_t _bit) noexcept
    {
        return (_value & (std::uint32_t{1} << _bit)) != 0;
    }

    CpuInstructionSet::CpuInstructionSet()
    {

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)

        const std::uint32_t maximumLeaf = maximumCpuidLeaf();

        if (maximumLeaf < 1)
        {
            return;
        }

        Cpu::X86InstructionSet& x86InstructionSet = emplace<Cpu::X86InstructionSet>();

        const CpuidRegisters leaf1 = cpuid(1);

        // CPUID leaf 1, EDX
        x86InstructionSet.mmx = hasBit(leaf1.edx, 23);
        x86InstructionSet.sse = hasBit(leaf1.edx, 25);
        x86InstructionSet.sse2 = hasBit(leaf1.edx, 26);

        // CPUID leaf 1, ECX
        x86InstructionSet.sse3 = hasBit(leaf1.ecx, 0);
        x86InstructionSet.ssse3 = hasBit(leaf1.ecx, 9);
        x86InstructionSet.sse41 = hasBit(leaf1.ecx, 19);
        x86InstructionSet.sse42 = hasBit(leaf1.ecx, 20);

        const bool cpuFma = hasBit(leaf1.ecx, 12);
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

        x86InstructionSet.avx = cpuAvx && osSupportsAvx;
        x86InstructionSet.fma = cpuFma && x86InstructionSet.avx;

        if (maximumLeaf < 7)
        {
            return;
        }

        const CpuidRegisters leaf7 = cpuid(7, 0);

        x86InstructionSet.bmi1 = hasBit(leaf7.ebx, 3);
        x86InstructionSet.bmi2 = hasBit(leaf7.ebx, 8);

        const bool cpuAvx2 = hasBit(leaf7.ebx, 5);

        x86InstructionSet.avx2 = cpuAvx2 && x86InstructionSet.avx;

        constexpr std::uint64_t Avx512State = AvxState | (std::uint64_t{1} << 5) | // Opmask registers
                                              (std::uint64_t{1} << 6) |            // ZMM0-ZMM15 upper bits
                                              (std::uint64_t{1} << 7);             // ZMM16-ZMM31

        const bool osSupportsAvx512 = osxsave && (xcr0 & Avx512State) == Avx512State;

        x86InstructionSet.avx512f = hasBit(leaf7.ebx, 16) && osSupportsAvx512;

        // AVX-512 subsets are useful only when AVX512F is available.
        x86InstructionSet.avx512dq = x86InstructionSet.avx512f && hasBit(leaf7.ebx, 17);

        x86InstructionSet.avx512cd = x86InstructionSet.avx512f && hasBit(leaf7.ebx, 28);

        x86InstructionSet.avx512bw = x86InstructionSet.avx512f && hasBit(leaf7.ebx, 30);

        x86InstructionSet.avx512vl = x86InstructionSet.avx512f && hasBit(leaf7.ebx, 31);
#endif
    }

} // namespace MathLib

// NOLINTEND(misc-include-cleaner)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
