#include <gtest/gtest.h>

#include <Vector4d.hpp>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

using namespace MathLib;

TEST(TestVec4, Constructor)
{
    const Vector4d v = Vector4d(1., 2., 3., 4.);

    EXPECT_DOUBLE_EQ(v.getX(), 1.0);
    EXPECT_DOUBLE_EQ(v.getY(), 2.0);
    EXPECT_DOUBLE_EQ(v.getZ(), 3.0);
    EXPECT_DOUBLE_EQ(v.getW(), 4.0);
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)