#ifndef CPU_INSTRUCTION_SET_H
#define CPU_INSTRUCTION_SET_H

#include <cstdint>
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
            bool sse = false;
            bool avx = false;
            bool avx2 = false;
        };

        struct ARMInstructionSet
        {
            bool sve = false;
            bool neon = false;
        };

    } // Cpu

    class CpuInstructionSet : public
#if CPU_X86_64
                              Cpu::X86InstructionSet
#elif CPU_ARM_64
                              Cpu::ARMInstructionSet
#else
#error
#endif
    {
    public:
        CpuInstructionSet();

        ~CpuInstructionSet() = default;

    private:
    };

} // namespace MathLib

#endif // CPU_INSTRUCTION_SET_H