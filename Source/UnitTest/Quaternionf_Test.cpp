#include <gtest/gtest.h>

#include <numbers>

#include <MathLibHeader.hpp>
#include <MatrixTransformation.hpp>
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

using namespace MathLib;

TEST(TestQuaternionf, constructor)
{
    const Quaternionf v = Quaternionf(1., 2., 3., 4.);

    EXPECT_FLOAT_EQ(v.getX(), 1.0);
    EXPECT_FLOAT_EQ(v.getY(), 2.0);
    EXPECT_FLOAT_EQ(v.getZ(), 3.0);
    EXPECT_FLOAT_EQ(v.getW(), 4.0);
}

TEST(TestQuaternionf, zero)
{
    const Quaternionf v = Quaternionf::zero();

    EXPECT_FLOAT_EQ(v.getX(), 0.0);
    EXPECT_FLOAT_EQ(v.getY(), 0.0);
    EXPECT_FLOAT_EQ(v.getZ(), 0.0);
    EXPECT_FLOAT_EQ(v.getW(), 0.0);
}

TEST(TestQuaternionf, identity)
{
    const Quaternionf v = Quaternionf::identity();

    EXPECT_FLOAT_EQ(v.getX(), 0.0);
    EXPECT_FLOAT_EQ(v.getY(), 0.0);
    EXPECT_FLOAT_EQ(v.getZ(), 0.0);
    EXPECT_FLOAT_EQ(v.getW(), 1.0);
}

TEST(TestQuaternionf, Setter)
{
    Quaternionf v{};
    v.setX(1.);
    v.setY(2.);
    v.setZ(3.);
    v.setW(4.);

    EXPECT_FLOAT_EQ(v.getX(), 1.0);
    EXPECT_FLOAT_EQ(v.getY(), 2.0);
    EXPECT_FLOAT_EQ(v.getZ(), 3.0);
    EXPECT_FLOAT_EQ(v.getW(), 4.0);
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
