#include <gtest/gtest.h>

#include <CompilerDetection.hpp>
#include <CpuInstructionSet.hpp>

using namespace MathLib;
static inline const CpuInstructionSet InstructionSet{};
#if CPU_X86_64

TEST(SIMDExtension, CompileTimeConfiguration)
{
#if SIMD_AVX2
    SUCCEED() << "Compiled with AVX2 enabled.";
#elif SIMD_AVX
    SUCCEED() << "Compiled with AVX enabled.";
#elif SIMD_SSE2
    SUCCEED() << "Compiled with SSE2 enabled.";
#else
    SUCCEED() << "Compiled without an explicitly selected SIMD level.";
#endif
}

TEST(SIMDExtension, DetectsX86InstructionSet)
{
    EXPECT_TRUE(std::holds_alternative<Cpu::X86InstructionSet>(InstructionSet));
}

#if (defined(__GNUC__) || defined(__clang__)) && !defined(_MSC_VER)

TEST(SIMDExtension, MatchesCompilerRuntimeDetection)
{
    ASSERT_TRUE(std::holds_alternative<Cpu::X86InstructionSet>(InstructionSet));

    const auto& x86Instruction = std::get<Cpu::X86InstructionSet>(InstructionSet);

    EXPECT_EQ(x86Instruction.mmx, __builtin_cpu_supports("mmx") != 0);

    EXPECT_EQ(x86Instruction.sse, __builtin_cpu_supports("sse") != 0);

    EXPECT_EQ(x86Instruction.sse2, __builtin_cpu_supports("sse2") != 0);

    EXPECT_EQ(x86Instruction.sse3, __builtin_cpu_supports("sse3") != 0);

    EXPECT_EQ(x86Instruction.ssse3, __builtin_cpu_supports("ssse3") != 0);

    EXPECT_EQ(x86Instruction.sse41, __builtin_cpu_supports("sse4.1") != 0);

    EXPECT_EQ(x86Instruction.sse42, __builtin_cpu_supports("sse4.2") != 0);

    EXPECT_EQ(x86Instruction.avx, __builtin_cpu_supports("avx") != 0);

    EXPECT_EQ(x86Instruction.avx2, __builtin_cpu_supports("avx2") != 0);

    EXPECT_EQ(x86Instruction.fma, __builtin_cpu_supports("fma") != 0);

    EXPECT_EQ(x86Instruction.bmi1, __builtin_cpu_supports("bmi") != 0);

    EXPECT_EQ(x86Instruction.bmi2, __builtin_cpu_supports("bmi2") != 0);

    EXPECT_EQ(x86Instruction.avx512f, __builtin_cpu_supports("avx512f") != 0);

    EXPECT_EQ(x86Instruction.avx512dq, __builtin_cpu_supports("avx512dq") != 0);

    EXPECT_EQ(x86Instruction.avx512cd, __builtin_cpu_supports("avx512cd") != 0);

    EXPECT_EQ(x86Instruction.avx512bw, __builtin_cpu_supports("avx512bw") != 0);

    EXPECT_EQ(x86Instruction.avx512vl, __builtin_cpu_supports("avx512vl") != 0);
}

#endif

#endif // CPU_X86_64
