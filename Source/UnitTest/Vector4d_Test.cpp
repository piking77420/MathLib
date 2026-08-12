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

TEST(TestVec4, Setter)
{
    Vector4d v{};
    v.setX(1.);
    v.setY(2.);
    v.setZ(3.);
    v.setW(4.);

    EXPECT_DOUBLE_EQ(v.getX(), 1.0);
    EXPECT_DOUBLE_EQ(v.getY(), 2.0);
    EXPECT_DOUBLE_EQ(v.getZ(), 3.0);
    EXPECT_DOUBLE_EQ(v.getW(), 4.0);
}


TEST(TestVec4, addOperator)
{
    const Vector4d v1 = Vector4d(1., 2., 3., 4.);
    const Vector4d v2 = Vector4d(4., 5., 6., 7.);
    const Vector4d v = v1 + v2;
    
    EXPECT_DOUBLE_EQ(v.getX(), 5.0);
    EXPECT_DOUBLE_EQ(v.getY(), 7.0);
    EXPECT_DOUBLE_EQ(v.getZ(), 9.0);
    EXPECT_DOUBLE_EQ(v.getW(), 11.0);
}

TEST(TestVec4, subOperator)
{
    const Vector4d v1(1.0, 2.0, 3.0, 4.0);
    const Vector4d v2(8.0, 10.0, 2.0, 4.0);

    const Vector4d v = v1 - v2;

    EXPECT_DOUBLE_EQ(v.getX(), -7.0);
    EXPECT_DOUBLE_EQ(v.getY(), -8.0);
    EXPECT_DOUBLE_EQ(v.getZ(),  1.0);
    EXPECT_DOUBLE_EQ(v.getW(),  0.0);
}

TEST(TestVec4, Dot)
{
    {
        const Vector4d v1 = Vector4d::unitX();
        const Vector4d v2 = Vector4d::unitZ();
        EXPECT_DOUBLE_EQ(Vector4d::dot(v1, v2), 0.0);
    }

    {
        const Vector4d v1 = Vector4d::unitX();
        const Vector4d v2 = Vector4d::unitW();
        EXPECT_DOUBLE_EQ(Vector4d::dot(v1, v2), 0.0);
    }

    {
        const Vector4d v1 = Vector4d::unitY();
        const Vector4d v2 = Vector4d::unitW();
        EXPECT_DOUBLE_EQ(Vector4d::dot(v1, v2), 0.0);
    }

    {
        const Vector4d v1 = Vector4d::unitZ();
        const Vector4d v2 = Vector4d::unitX();
        EXPECT_DOUBLE_EQ(Vector4d::dot(v1, v2), 0.0);
    }

    {
        const Vector4d v1 = Vector4d::unitW();
        const Vector4d v2 = Vector4d::unitY();
        EXPECT_DOUBLE_EQ(Vector4d::dot(v1, v2), 0.0);
    }

    {
        const Vector4d v1 = Vector4d::unitX();
        EXPECT_DOUBLE_EQ(Vector4d::dot(v1, v1), 1.0);
    }

    {
        const Vector4d v1 = Vector4d::unitY();
        EXPECT_DOUBLE_EQ(Vector4d::dot(v1, v1), 1.0);
    }

    {
        const Vector4d v1 = Vector4d::unitZ();
        EXPECT_DOUBLE_EQ(Vector4d::dot(v1, v1), 1.0);
    }

    {
        const Vector4d v1 = Vector4d::unitW();
        EXPECT_DOUBLE_EQ(Vector4d::dot(v1, v1), 1.0);
    }

    {
        const Vector4d v1(1.0, 2.0, 3.0, 4.0);
        const Vector4d v2(5.0, 6.0, 7.0, 8.0);

        // 1*5 + 2*6 + 3*7 + 4*8 = 70
        EXPECT_DOUBLE_EQ(Vector4d::dot(v1, v2), 70.0);
    }

    {
        const Vector4d v1(1.0, -2.0, 3.0, -4.0);
        const Vector4d v2(-5.0, 6.0, -7.0, 8.0);

        EXPECT_DOUBLE_EQ(Vector4d::dot(v1, v2), -70.0);
    }

    {
        const Vector4d zero(0.0, 0.0, 0.0, 0.0);
        const Vector4d v(1.0, 2.0, 3.0, 4.0);

        EXPECT_DOUBLE_EQ(Vector4d::dot(zero, v), 0.0);
    }

    {
        const Vector4d v1(4.0, -2.0, 6.0, 10.0);
        const Vector4d v2(5.0, 2.0, 3.0, -4.0);

        EXPECT_DOUBLE_EQ(Vector4d::dot(v1, v2), -6.0);
        EXPECT_DOUBLE_EQ(Vector4d::dot(v2, v1), -6.0);
    }

}


// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)