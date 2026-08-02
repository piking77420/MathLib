#ifndef CPU_INSTRUCTION_SET_H
#define CPU_INSTRUCTION_SET_H

#include <cstdint>
#include <variant>

#include <CompilerDetection.hpp>

#if defined(_MSC_VER)

#include <intrin.h>

#elif defined(__GNUC__) || defined(__clang__)

#if CPU_X86_64
#include <cpuid.h>
#endif // CPU_X86_64

#endif

namespace MathLib
{
    namespace Cpu
    {
        struct X86InstructionSet
        {
            bool mmx = false;
            bool sse = false;
            bool sse2 = false;
            bool sse3 = false;
            bool ssse3 = false;
            bool sse41 = false;
            bool sse42 = false;

            bool avx = false;
            bool avx2 = false;

            bool fma = false;
            bool bmi1 = false;
            bool bmi2 = false;

            bool avx512f = false;
            bool avx512dq = false;
            bool avx512cd = false;
            bool avx512bw = false;
            bool avx512vl = false;
        };

        struct ARMInstructionSet
        {
            bool todo;
        };

    } // Cpu

    class CpuInstructionSet : public std::variant<Cpu::X86InstructionSet, Cpu::ARMInstructionSet>
    {
    public:
        CpuInstructionSet();

        ~CpuInstructionSet() = default;

        bool isValid() const;

    private:
    };

} // namespace MathLib

#endif // CPU_INSTRUCTION_SET_H