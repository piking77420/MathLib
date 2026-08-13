#include <gtest/gtest.h>

#include <cmath>
#include <array>
#include <span>

#include <MathLibHeader.hpp>
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
    EXPECT_DOUBLE_EQ(v.getZ(), 1.0);
    EXPECT_DOUBLE_EQ(v.getW(), 0.0);
}

TEST(TestVec4, EqualOperator)
{
    {
        const Vector4d v1 = Vector4d::unitX();
        const Vector4d v2 = Vector4d::unitZ();
        EXPECT_TRUE(v1 == v1);
        EXPECT_FALSE(v1 == v2);
        EXPECT_FALSE(v1 != v1);
        EXPECT_TRUE(v1 != v2);
    }

    constexpr double DoubleEpsilonHalf = 0.5 * DoubleEpsilon;
    constexpr double DoubleEpsilon2 = 2.0 * DoubleEpsilon;

    {
        const Vector4d v1(1.0, 2.0, 3.0, 4.0);
        const Vector4d v2(1.0 - DoubleEpsilonHalf, 2.0 - DoubleEpsilonHalf, 3.0 - DoubleEpsilonHalf,
                          4.0 - DoubleEpsilonHalf);

        EXPECT_TRUE(v1 == v2);
        EXPECT_FALSE(v1 != v2);
    }

    {
        const Vector4d v1(1.0, 2.0, 3.0, 4.0);
        const Vector4d v2(1.0 - DoubleEpsilon2, 2.0 - DoubleEpsilon2, 3.0 - DoubleEpsilon2, 4.0 - DoubleEpsilon2);

        EXPECT_TRUE(v1 != v2);
        EXPECT_FALSE(v1 == v2);
    }
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

TEST(TestVec4, lengthSquare)
{
    // unit vector lengthSquare by definition is 1
    {
        const Vector4d v1 = Vector4d::unitX();
        EXPECT_DOUBLE_EQ(v1.lengthSquare(), 1.0);

        const Vector4d v2 = Vector4d::unitY();
        EXPECT_DOUBLE_EQ(v2.lengthSquare(), 1.0);

        const Vector4d v3 = Vector4d::unitZ();
        EXPECT_DOUBLE_EQ(v3.lengthSquare(), 1.0);

        const Vector4d v4 = Vector4d::unitW();
        EXPECT_DOUBLE_EQ(v4.lengthSquare(), 1.0);
    }
    {
        const Vector4d v1 = Vector4d(-1.0, 0.0, 0.0, 0.0);
        EXPECT_DOUBLE_EQ(v1.lengthSquare(), 1.0);
    }

    {
        const Vector4d v1 = Vector4d(-1.0, -2.0, 4.0, 8.0);
        EXPECT_DOUBLE_EQ(v1.lengthSquare(), 85.0);
    }
}

TEST(TestVec4, length)
{
    // unit vector length by definition is 1
    {
        const Vector4d v1 = Vector4d::unitX();
        EXPECT_DOUBLE_EQ(v1.length(), 1.0);

        const Vector4d v2 = Vector4d::unitY();
        EXPECT_DOUBLE_EQ(v2.length(), 1.0);

        const Vector4d v3 = Vector4d::unitZ();
        EXPECT_DOUBLE_EQ(v3.length(), 1.0);

        const Vector4d v4 = Vector4d::unitW();
        EXPECT_DOUBLE_EQ(v4.length(), 1.0);
    }

    // Same arbitrary vector
    //
    {
        const Vector4d v1 = Vector4d(-1.0, -2.0, 4.0, 8.0);
        EXPECT_DOUBLE_EQ(v1.length(), std::sqrt(85.0));
        EXPECT_DOUBLE_EQ(v1.length(), std::sqrt(v1.lengthSquare()));
    }

    // test negative value
    {
        const Vector4d v1 = Vector4d(-1.0, 0.0, 0.0, 0.0);
        EXPECT_DOUBLE_EQ(v1.length(), 1.0);
    }
}

TEST(TestVec4, distanceSquare)
{
    // unit vector
    {
        const Vector4d v1 = Vector4d::unitX();
        const Vector4d v2 = Vector4d::unitX();

        EXPECT_DOUBLE_EQ(Vector4d::distanceSquare(v1, v2), 0.0);
    }

    // Same arbitrary vector
    {
        const Vector4d v1(10.0, 20.0, -12.0, -44.0);
        const Vector4d v2(10.0, 20.0, -12.0, -44.0);

        EXPECT_DOUBLE_EQ(Vector4d::distanceSquare(v1, v2), 0.0);
    }

    // Difference only on X
    {
        const Vector4d v1(1.0, 2.0, 3.0, 4.0);
        const Vector4d v2(4.0, 2.0, 3.0, 4.0);

        EXPECT_DOUBLE_EQ(Vector4d::distanceSquare(v1, v2), 9.0);
    }

    // Difference only on Y
    {
        const Vector4d v1(1.0, 2.0, 3.0, 4.0);
        const Vector4d v2(1.0, 6.0, 3.0, 4.0);

        EXPECT_DOUBLE_EQ(Vector4d::distanceSquare(v1, v2), 16.0);
    }

    // Difference only on Z
    {
        const Vector4d v1(1.0, 2.0, 3.0, 4.0);
        const Vector4d v2(1.0, 2.0, 8.0, 4.0);

        EXPECT_DOUBLE_EQ(Vector4d::distanceSquare(v1, v2), 25.0);
    }

    // Difference only on W
    {
        const Vector4d v1(1.0, 2.0, 3.0, 4.0);
        const Vector4d v2(1.0, 2.0, 3.0, 10.0);

        EXPECT_DOUBLE_EQ(Vector4d::distanceSquare(v1, v2), 36.0);
    }

    // Difference on every component
    {
        const Vector4d v1(-1.0, -2.0, 4.0, 8.0);
        const Vector4d v2(1.0, 2.0, 0.0, 4.0);

        // (-2)^2 + (-4)^2 + 4^2 + 4^2
        // = 4 + 16 + 16 + 16
        // = 52
        EXPECT_DOUBLE_EQ(Vector4d::distanceSquare(v1, v2), 52.0);
    }

    // Negative and positive values
    {
        const Vector4d v1(-1.0, -2.0, -3.0, -4.0);
        const Vector4d v2(1.0, 2.0, 3.0, 4.0);

        // 2^2 + 4^2 + 6^2 + 8^2
        // = 4 + 16 + 36 + 64
        // = 120
        EXPECT_DOUBLE_EQ(Vector4d::distanceSquare(v1, v2), 120.0);
    }

    // Symmetry
    {
        const Vector4d v1(2.0, -3.0, 5.0, 7.0);
        const Vector4d v2(-4.0, 8.0, 1.0, -2.0);

        EXPECT_DOUBLE_EQ(Vector4d::distanceSquare(v1, v2), Vector4d::distanceSquare(v2, v1));
    }

    // distanceSquare(a, b) == (a - b).lengthSquare()
    {
        const Vector4d v1(-4.0, 7.0, 2.0, 12.0);
        const Vector4d v2(3.0, -2.0, 6.0, 5.0);

        const Vector4d difference = v1 - v2;

        EXPECT_DOUBLE_EQ(Vector4d::distanceSquare(v1, v2), difference.lengthSquare());
    }
}

TEST(TestVec4, distance)
{
    // unit vector
    {
        const Vector4d v1 = Vector4d::unitX();
        const Vector4d v2 = Vector4d::unitX();

        EXPECT_DOUBLE_EQ(Vector4d::distance(v1, v2), 0.0);
    }

    // Same arbitrary vector
    {
        const Vector4d v1(10.0, 20.0, -12.0, -44.0);
        const Vector4d v2(10.0, 20.0, -12.0, -44.0);

        EXPECT_DOUBLE_EQ(Vector4d::distance(v1, v2), 0.0);
    }

    // Difference only on X
    {
        const Vector4d v1(1.0, 2.0, 3.0, 4.0);
        const Vector4d v2(4.0, 2.0, 3.0, 4.0);

        EXPECT_DOUBLE_EQ(Vector4d::distance(v1, v2), 3.0);
    }

    // Difference only on Y
    {
        const Vector4d v1(1.0, 2.0, 3.0, 4.0);
        const Vector4d v2(1.0, 6.0, 3.0, 4.0);

        EXPECT_DOUBLE_EQ(Vector4d::distance(v1, v2), 4.0);
    }

    // Difference only on Z
    {
        const Vector4d v1(1.0, 2.0, 3.0, 4.0);
        const Vector4d v2(1.0, 2.0, 8.0, 4.0);

        EXPECT_DOUBLE_EQ(Vector4d::distance(v1, v2), 5.0);
    }

    // Difference only on W
    {
        const Vector4d v1(1.0, 2.0, 3.0, 4.0);
        const Vector4d v2(1.0, 2.0, 3.0, 10.0);

        EXPECT_DOUBLE_EQ(Vector4d::distance(v1, v2), 6.0);
    }

    // Difference on every component
    {
        const Vector4d v1(-1.0, -2.0, 4.0, 8.0);
        const Vector4d v2(1.0, 2.0, 0.0, 4.0);

        // (-2)^2 + (-4)^2 + 4^2 + 4^2
        // = 4 + 16 + 16 + 16
        // = 52
        EXPECT_DOUBLE_EQ(Vector4d::distance(v1, v2), std::sqrt(52.0));
    }

    // Negative and positive values
    {
        const Vector4d v1(-1.0, -2.0, -3.0, -4.0);
        const Vector4d v2(1.0, 2.0, 3.0, 4.0);

        // 2^2 + 4^2 + 6^2 + 8^2
        // = 4 + 16 + 36 + 64
        // = 120
        EXPECT_DOUBLE_EQ(Vector4d::distance(v1, v2), std::sqrt(120.0));
    }

    // Symmetry
    {
        const Vector4d v1(2.0, -3.0, 5.0, 7.0);
        const Vector4d v2(-4.0, 8.0, 1.0, -2.0);

        EXPECT_DOUBLE_EQ(Vector4d::distance(v1, v2), Vector4d::distance(v2, v1));
    }

    // distance(a, b) == (a - b).length()
    {
        const Vector4d v1(-4.0, 7.0, 2.0, 12.0);
        const Vector4d v2(3.0, -2.0, 6.0, 5.0);

        const Vector4d difference = v1 - v2;

        EXPECT_DOUBLE_EQ(Vector4d::distance(v1, v2), difference.length());
    }
}

TEST(TestVec4, getNormalize)
{
    {
        const Vector4d v(3.0, 4.0, 0.0, 0.0);
        const Vector4d normalized = v.getNormalize();

        EXPECT_NEAR(normalized.getX(), 0.6, DoubleEpsilon);
        EXPECT_NEAR(normalized.getY(), 0.8, DoubleEpsilon);
        EXPECT_NEAR(normalized.getZ(), 0.0, DoubleEpsilon);
        EXPECT_NEAR(normalized.getW(), 0.0, DoubleEpsilon);

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);

        // getNormalize() must not modify the original vector.
        EXPECT_DOUBLE_EQ(v.getX(), 3.0);
        EXPECT_DOUBLE_EQ(v.getY(), 4.0);
        EXPECT_DOUBLE_EQ(v.getZ(), 0.0);
        EXPECT_DOUBLE_EQ(v.getW(), 0.0);
    }

    {
        const Vector4d v(-1.0, -2.0, 4.0, 8.0);
        const Vector4d normalized = v.getNormalize();

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);
    }

    // Already normalized.
    {
        const Vector4d v = Vector4d::unitX();
        const Vector4d normalized = v.getNormalize();

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(normalized.getX(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(normalized.getY(), 0.0, DoubleEpsilon);
        EXPECT_NEAR(normalized.getZ(), 0.0, DoubleEpsilon);
        EXPECT_NEAR(normalized.getW(), 0.0, DoubleEpsilon);
    }

    // Zero vector.
    {
        const Vector4d v(0.0, 0.0, 0.0, 0.0);
        const Vector4d normalized = v.getNormalize();

        EXPECT_DOUBLE_EQ(normalized.getX(), 0.0);
        EXPECT_DOUBLE_EQ(normalized.getY(), 0.0);
        EXPECT_DOUBLE_EQ(normalized.getZ(), 0.0);
        EXPECT_DOUBLE_EQ(normalized.getW(), 0.0);
    }
}

TEST(TestVec4, normalize)
{
    {
        Vector4d v(3.0, 4.0, 0.0, 0.0);

        v.normalize();

        EXPECT_NEAR(v.getX(), 0.6, DoubleEpsilon);
        EXPECT_NEAR(v.getY(), 0.8, DoubleEpsilon);
        EXPECT_NEAR(v.getZ(), 0.0, DoubleEpsilon);
        EXPECT_NEAR(v.getW(), 0.0, DoubleEpsilon);

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
    }

    {
        Vector4d v(-1.0, -2.0, 4.0, 8.0);

        v.normalize();

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
    }

    // Already normalized.
    {
        Vector4d v = Vector4d::unitX();

        v.normalize();

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(v.getX(), 1.0, DoubleEpsilon);
    }

    // Zero vector should remain zero.
    {
        Vector4d v(0.0, 0.0, 0.0, 0.0);

        v.normalize();

        EXPECT_DOUBLE_EQ(v.getX(), 0.0);
        EXPECT_DOUBLE_EQ(v.getY(), 0.0);
        EXPECT_DOUBLE_EQ(v.getZ(), 0.0);
        EXPECT_DOUBLE_EQ(v.getW(), 0.0);
    }

    // normalize() should return *this.
    {
        Vector4d v(3.0, 4.0, 0.0, 0.0);

        Vector4d const& result = v.normalize();

        EXPECT_EQ(&result, &v);
    }
}

TEST(TestVec4, getNormalizeFast)
{
    {
        const Vector4d v(3.0, 4.0, 0.0, 0.0);
        const Vector4d normalized = v.getNormalizeFast();

        EXPECT_NEAR(normalized.getX(), 0.6, DoubleEpsilon);
        EXPECT_NEAR(normalized.getY(), 0.8, DoubleEpsilon);
        EXPECT_NEAR(normalized.getZ(), 0.0, DoubleEpsilon);
        EXPECT_NEAR(normalized.getW(), 0.0, DoubleEpsilon);

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);

        // getNormalizeFast() must not modify the original vector.
        EXPECT_DOUBLE_EQ(v.getX(), 3.0);
        EXPECT_DOUBLE_EQ(v.getY(), 4.0);
        EXPECT_DOUBLE_EQ(v.getZ(), 0.0);
        EXPECT_DOUBLE_EQ(v.getW(), 0.0);
    }

    {
        const Vector4d v(-1.0, -2.0, 4.0, 8.0);
        const Vector4d normalized = v.getNormalizeFast();

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);
    }

    // Already normalized.
    {
        const Vector4d v = Vector4d::unitX();
        const Vector4d normalized = v.getNormalizeFast();

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(normalized.getX(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(normalized.getY(), 0.0, DoubleEpsilon);
        EXPECT_NEAR(normalized.getZ(), 0.0, DoubleEpsilon);
        EXPECT_NEAR(normalized.getW(), 0.0, DoubleEpsilon);
    }

    // Zero vector.
    {
        const Vector4d v(0.0, 0.0, 0.0, 0.0);
        const Vector4d normalized = v.getNormalizeFast();

        EXPECT_DOUBLE_EQ(normalized.getX(), 0.0);
        EXPECT_DOUBLE_EQ(normalized.getY(), 0.0);
        EXPECT_DOUBLE_EQ(normalized.getZ(), 0.0);
        EXPECT_DOUBLE_EQ(normalized.getW(), 0.0);
    }
}

TEST(TestVec4, normalizeFast)
{
    {
        Vector4d v(3.0, 4.0, 0.0, 0.0);

        v.normalizeFast();

        EXPECT_NEAR(v.getX(), 0.6, DoubleEpsilon);
        EXPECT_NEAR(v.getY(), 0.8, DoubleEpsilon);
        EXPECT_NEAR(v.getZ(), 0.0, DoubleEpsilon);
        EXPECT_NEAR(v.getW(), 0.0, DoubleEpsilon);

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
    }

    {
        Vector4d v(-1.0, -2.0, 4.0, 8.0);

        v.normalizeFast();

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
    }

    // Already normalizeFastd.
    {
        Vector4d v = Vector4d::unitX();

        v.normalizeFast();

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(v.getX(), 1.0, DoubleEpsilon);
    }

    // Zero vector should remain zero.
    {
        Vector4d v(0.0, 0.0, 0.0, 0.0);

        v.normalizeFast();

        EXPECT_DOUBLE_EQ(v.getX(), 0.0);
        EXPECT_DOUBLE_EQ(v.getY(), 0.0);
        EXPECT_DOUBLE_EQ(v.getZ(), 0.0);
        EXPECT_DOUBLE_EQ(v.getW(), 0.0);
    }

    // normalizeFast() should return *this.
    {
        Vector4d v(3.0, 4.0, 0.0, 0.0);

        Vector4d const& result = v.normalizeFast();

        EXPECT_EQ(&result, &v);
    }
}

TEST(TestVec4, isHomogeneous)
{
    // Zero with w equal 1
    {
        const Vector4d v(0.0, 0.0, 0.0, 1.0);
        EXPECT_TRUE(v.isHomogeneous());
    }

    // Zero with w not equal 1
    {
        const Vector4d v(0.0, 0.0, 0.0, 0.8);
        EXPECT_FALSE(v.isHomogeneous());
    }

    // Random Vector
    {
        const Vector4d v(1.41, 0.5, -4.0, 1.0);
        EXPECT_TRUE(v.isHomogeneous());
    }

    // Random Vector with w equal 0
    {
        const Vector4d v(1.41, 0.5, -4.0, 0.0);
        EXPECT_FALSE(v.isHomogeneous());
    }
}

TEST(TestVec4, streamToUnAlignedDouble)
{
    {
        std::array<double, 4> data;
        const Vector4d v(1.0, 2.0, 3.0, 4.0);
        v.streamToUnalignedDouble(data.data());
        EXPECT_NEAR(data[0], 1.0, DoubleEpsilon);
        EXPECT_NEAR(data[1], 2.0, DoubleEpsilon);
        EXPECT_NEAR(data[2], 3.0, DoubleEpsilon);
        EXPECT_NEAR(data[3], 4.0, DoubleEpsilon);
    }

    {
        std::array<double, 4> data;
        const Vector4d v(1.0, 2.0, 3.0, 4.0);
        v.streamToUnalignedDouble(std::span<double, 4>(data));
        EXPECT_NEAR(data[0], 1.0, DoubleEpsilon);
        EXPECT_NEAR(data[1], 2.0, DoubleEpsilon);
        EXPECT_NEAR(data[2], 3.0, DoubleEpsilon);
        EXPECT_NEAR(data[3], 4.0, DoubleEpsilon);
    }
}

TEST(TestVec4, streamToUnAlignedFloat)
{
    {
        std::array<float, 4> data;
        const Vector4d v(1.0, 2.0, 3.0, 4.0);
        v.streamToUnAlignedFloat(data.data());
        EXPECT_NEAR(data[0], 1.0f, FloatEpsilon);
        EXPECT_NEAR(data[1], 2.0f, FloatEpsilon);
        EXPECT_NEAR(data[2], 3.0f, FloatEpsilon);
        EXPECT_NEAR(data[3], 4.0f, FloatEpsilon);
    }

    {
        std::array<float, 4> data;
        const Vector4d v(1.0, 2.0, 3.0, 4.0);
        v.streamToUnAlignedFloat(std::span<float, 4>(data));
        EXPECT_NEAR(data[0], 1.0f, FloatEpsilon);
        EXPECT_NEAR(data[1], 2.0f, FloatEpsilon);
        EXPECT_NEAR(data[2], 3.0f, FloatEpsilon);
        EXPECT_NEAR(data[3], 4.0f, FloatEpsilon);
    }
}

TEST(TestVec4, streamToAlignedDouble)
{
    {
        alignas(AVX_AVX2_ALIGNEMENT) std::array<double, 4> data;
        const Vector4d v(1.0, 2.0, 3.0, 4.0);
        v.streamToAlignedDouble(data.data());
        EXPECT_NEAR(data[0], 1.0, DoubleEpsilon);
        EXPECT_NEAR(data[1], 2.0, DoubleEpsilon);
        EXPECT_NEAR(data[2], 3.0, DoubleEpsilon);
        EXPECT_NEAR(data[3], 4.0, DoubleEpsilon);
    }

    {
        alignas(AVX_AVX2_ALIGNEMENT) std::array<double, 4> data;
        const Vector4d v(1.0, 2.0, 3.0, 4.0);
        v.streamToAlignedDouble(std::span<double, 4>(data));
        EXPECT_NEAR(data[0], 1.0, DoubleEpsilon);
        EXPECT_NEAR(data[1], 2.0, DoubleEpsilon);
        EXPECT_NEAR(data[2], 3.0, DoubleEpsilon);
        EXPECT_NEAR(data[3], 4.0, DoubleEpsilon);
    }
}

TEST(TestVec4, streamToUnalignedFloat)
{
    {
        alignas(SSE_ALIGNEMENT) std::array<float, 4> data;
        const Vector4d v(1.0, 2.0, 3.0, 4.0);
        v.streamToAlignedFloat(data.data());
        EXPECT_NEAR(data[0], 1.0f, FloatEpsilon);
        EXPECT_NEAR(data[1], 2.0f, FloatEpsilon);
        EXPECT_NEAR(data[2], 3.0f, FloatEpsilon);
        EXPECT_NEAR(data[3], 4.0f, FloatEpsilon);
    }

    {
        alignas(SSE_ALIGNEMENT) std::array<float, 4> data;
        const Vector4d v(1.0, 2.0, 3.0, 4.0);
        v.streamToAlignedFloat(std::span<float, 4>(data));
        EXPECT_NEAR(data[0], 1.0f, FloatEpsilon);
        EXPECT_NEAR(data[1], 2.0f, FloatEpsilon);
        EXPECT_NEAR(data[2], 3.0f, FloatEpsilon);
        EXPECT_NEAR(data[3], 4.0f, FloatEpsilon);
    }
}

TEST(TestVec4, fromUnAlignedDouble)
{
    {
        std::array<double, 4> data = {1.0, 2.0, 3.0, 4.0};
        Vector4d v;
        v.fromUnalignedDouble(data);
        EXPECT_NEAR(v.getX(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(v.getY(), 2.0, DoubleEpsilon);
        EXPECT_NEAR(v.getZ(), 3.0, DoubleEpsilon);
        EXPECT_NEAR(v.getW(), 4.0, DoubleEpsilon);
    }

    {
        std::array<double, 4> data = {1.0, 2.0, 3.0, 4.0};
        Vector4d v;
        v.fromUnalignedDouble(std::span<const double, 4>(data));
        EXPECT_NEAR(v.getX(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(v.getY(), 2.0, DoubleEpsilon);
        EXPECT_NEAR(v.getZ(), 3.0, DoubleEpsilon);
        EXPECT_NEAR(v.getW(), 4.0, DoubleEpsilon);
    }
}

TEST(TestVec4, fromUnAlignedFloat)
{
    {
        std::array<float, 4> data = {1.0, 2.0, 3.0, 4.0};
        Vector4d v;
        v.fromUnAlignedFloat(data);
        EXPECT_NEAR(v.getX(), 1.0, FloatEpsilon);
        EXPECT_NEAR(v.getY(), 2.0, FloatEpsilon);
        EXPECT_NEAR(v.getZ(), 3.0, FloatEpsilon);
        EXPECT_NEAR(v.getW(), 4.0, FloatEpsilon);
    }

    {
        std::array<float, 4> data = {1.0, 2.0, 3.0, 4.0};
        Vector4d v;
        v.fromUnAlignedFloat(std::span<const float, 4>(data));
        EXPECT_NEAR(v.getX(), 1.0, FloatEpsilon);
        EXPECT_NEAR(v.getY(), 2.0, FloatEpsilon);
        EXPECT_NEAR(v.getZ(), 3.0, FloatEpsilon);
        EXPECT_NEAR(v.getW(), 4.0, FloatEpsilon);
    }
}

TEST(TestVec4, fromAlignedDouble)
{
    {
        alignas(AVX_AVX2_ALIGNEMENT) std::array<double, 4> data{1.0, 2.0, 3.0, 4.};
        Vector4d v;
        v.fromAlignedDouble(data.data());
        EXPECT_NEAR(v.getX(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(v.getY(), 2.0, DoubleEpsilon);
        EXPECT_NEAR(v.getZ(), 3.0, DoubleEpsilon);
        EXPECT_NEAR(v.getW(), 4.0, DoubleEpsilon);
    }

    {
        alignas(AVX_AVX2_ALIGNEMENT) std::array<double, 4> data{1.0, 2.0, 3.0, 4.};
        Vector4d v;
        v.fromAlignedDouble(std::span<double, 4>(data));
        EXPECT_NEAR(v.getX(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(v.getY(), 2.0, DoubleEpsilon);
        EXPECT_NEAR(v.getZ(), 3.0, DoubleEpsilon);
        EXPECT_NEAR(v.getW(), 4.0, DoubleEpsilon);
    }
}

TEST(TestVec4, fromAlignedFloat)
{
    {
        alignas(AVX_AVX2_ALIGNEMENT) std::array<float, 4> data{1.0, 2.0, 3.0, 4.};
        Vector4d v;
        v.fromAlignedFloat(data.data());
        EXPECT_NEAR(v.getX(), 1.0, FloatEpsilon);
        EXPECT_NEAR(v.getY(), 2.0, FloatEpsilon);
        EXPECT_NEAR(v.getZ(), 3.0, FloatEpsilon);
        EXPECT_NEAR(v.getW(), 4.0, FloatEpsilon);
    }

    {
        alignas(AVX_AVX2_ALIGNEMENT) std::array<float, 4> data{1.0, 2.0, 3.0, 4.};
        Vector4d v;
        v.fromAlignedFloat(std::span<float, 4>(data));
        EXPECT_NEAR(v.getX(), 1.0, FloatEpsilon);
        EXPECT_NEAR(v.getY(), 2.0, FloatEpsilon);
        EXPECT_NEAR(v.getZ(), 3.0, FloatEpsilon);
        EXPECT_NEAR(v.getW(), 4.0, FloatEpsilon);
    }
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
