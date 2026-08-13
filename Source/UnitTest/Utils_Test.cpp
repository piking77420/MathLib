#include <gtest/gtest.h>

#include <span>

#include <MathLibHeader.hpp>
#include <CpuInstructionSet.hpp>
#include <Vector4d.hpp>

using namespace MathLib;
static inline const CpuInstructionSet InstructionSet{};

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

// Cheat Sheet
// isAligned<16>(ptr); // SSE
// isAligned<32>(ptr); // AVX / AVX2
// isAligned<64>(ptr); // AVX-512

TEST(Utils, Aligned)
{
    alignas(32) std::byte data[64];

    EXPECT_TRUE(isAligned<32>(data));
    EXPECT_FALSE(isAligned<32>(data + 1));
    EXPECT_FALSE(isAligned<32>(data + 8));
    EXPECT_FALSE(isAligned<32>(data + 16));
    EXPECT_TRUE(isAligned<32>(data + 32));
}

TEST(Utils, NotAligned)
{
    alignas(32) std::byte data[64];

    const void* ptr = data + 8;

    EXPECT_FALSE(isAligned<32>(ptr));
}

TEST(Utils, AlignmentVector4)
{
    {
        alignas(32) Vector4d v;
        EXPECT_TRUE(isAligned<32>(&v));
    }

    {
        alignas(32) std::byte storage[sizeof(Vector4d)];

        Vector4d* v = std::construct_at(reinterpret_cast<Vector4d*>(storage));

        EXPECT_TRUE(isAligned<32>(v));

        std::destroy_at(v);
    }
}

TEST(Utils, Vector4dNotAVXAligned)
{
    alignas(32) std::byte storage[64];

    // storage is 32-byte aligned.
    // +8 is still valid for Vector4d (alignof == 8),
    // but deliberately not 32-byte aligned.
    void* ptr = storage + 8;

    auto* v = std::construct_at(static_cast<Vector4d*>(ptr));

    EXPECT_TRUE(isAligned<8>(v));
    EXPECT_FALSE(isAligned<32>(v));

    std::destroy_at(v);
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
