#include <gtest/gtest.h>

#include <CompilerDetection.hpp>
#include <CpuInstructionSet.hpp>

using namespace MathLib;
static inline const CpuInstructionSet InstructionSet{};

TEST(SIMDExtension, CompileTimeConfiguration)
{
#if CPU_X86_64
#if SIMD_AVX2
    SUCCEED() << "Compiled with AVX2 enabled.";
    EXPECT_TRUE(InstructionSet.sse);
    EXPECT_TRUE(InstructionSet.avx);
    EXPECT_TRUE(InstructionSet.avx2);
#elif SIMD_AVX
    SUCCEED() << "Compiled with AVX enabled.";
    EXPECT_TRUE(InstructionSet.sse);
    EXPECT_TRUE(InstructionSet.avx);
#elif SIMD_SSE2
    SUCCEED() << "Compiled with SSE2 enabled.";
    EXPECT_TRUE(InstructionSet.sse);
#else
    SUCCEED() << "Compiled without an explicitly selected SIMD level.";
#endif // SIMD_AVX2

#elif CPU_ARM_64

#if SIMD_ARM_NEON
    SUCCEED() << "Compiled with AVX2 enabled.";
    EXPECT_TRUE(InstructionSet.enon);
    EXPECT_TRUE(InstructionSet.avx);
    EXPECT_TRUE(InstructionSet.avx2);
#elif SIMD_ARM_SVE
    SUCCEED() << "Compiled with AVX enabled.";
    EXPECT_TRUE(InstructionSet.sve);
#else
    SUCCEED() << "Compiled without an explicitly selected SIMD level.";
#endif // SIMD_ARM_NEON

#endif // CPU_X86_64
}

TEST(SIMDExtension, MatchesCompilerRuntimeDetection)
{
#if CPU_X86_64
#if (defined(__GNUC__) || defined(__clang__)) && !defined(_MSC_VER)

    EXPECT_EQ(InstructionSet.sse, __builtin_cpu_supports("sse") != 0);

    EXPECT_EQ(InstructionSet.avx, __builtin_cpu_supports("avx") != 0);

    EXPECT_EQ(InstructionSet.avx2, __builtin_cpu_supports("avx2") != 0);
#endif // (defined(__GNUC__) || defined(__clang__)) && !defined(_MSC_VER)

#endif // CPU_X86_64
}
