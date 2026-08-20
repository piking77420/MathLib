#include <gtest/gtest.h>

#include <cmath>
#include <array>
#include <span>

#include <MathLibHeader.hpp>
#include <Vector2d.hpp>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

using namespace MathLib;

TEST(TestVector2d, Constructor)
{
    {
        const Vector2d v = Vector2d(1., 2.);

        EXPECT_DOUBLE_EQ(v.getX(), 1.0);
        EXPECT_DOUBLE_EQ(v.getY(), 2.0);
    }

    {
        const Vector2d v = Vector2d(3.0);

        EXPECT_DOUBLE_EQ(v.getX(), 3.0);
        EXPECT_DOUBLE_EQ(v.getY(), 3.0);
    }
}

TEST(TestVector2d, Setter)
{
    Vector2d v{};
    v.setX(8.);
    v.setY(4.0);
    EXPECT_DOUBLE_EQ(v.getX(), 8.0);
    EXPECT_DOUBLE_EQ(v.getY(), 4.0);
    v.setX(1.);
    EXPECT_DOUBLE_EQ(v.getX(), 1.0);
    EXPECT_DOUBLE_EQ(v.getY(), 4.0);
    v.setX(1.);
    v.setY(2.);
    EXPECT_DOUBLE_EQ(v.getX(), 1.0);
    EXPECT_DOUBLE_EQ(v.getY(), 2.0);
}

TEST(TestVector2d, addVectorOperator)
{
    {
        Vector2d v = Vector2d(1., 2.);
        v += Vector2d(4., 5.);
        EXPECT_DOUBLE_EQ(v.getX(), 5.0);
        EXPECT_DOUBLE_EQ(v.getY(), 7.0);
    }

    {
        const Vector2d v1 = Vector2d(1., 2.);
        const Vector2d v2 = Vector2d(4., 5.);
        const Vector2d v = v1 + v2;

        EXPECT_DOUBLE_EQ(v.getX(), 5.0);
        EXPECT_DOUBLE_EQ(v.getY(), 7.0);
    }
}

TEST(TestVector2d, subVectorOperator)
{
    {
        Vector2d v(1.0, 2.0);
        v -= Vector2d(8.0, 10.0);

        EXPECT_DOUBLE_EQ(v.getX(), -7.0);
        EXPECT_DOUBLE_EQ(v.getY(), -8.0);
    }

    {
        const Vector2d v1(1.0, 2.0);
        const Vector2d v2(8.0, 10.0);

        const Vector2d v = v1 - v2;

        EXPECT_DOUBLE_EQ(v.getX(), -7.0);
        EXPECT_DOUBLE_EQ(v.getY(), -8.0);
    }
}

TEST(TestVector2d, mulVectorOperator)
{
    {
        Vector2d v(1.0, 2.0);
        v *= Vector2d(8.0, 10.0);

        EXPECT_DOUBLE_EQ(v.getX(), 8.0);
        EXPECT_DOUBLE_EQ(v.getY(), 20.0);
    }

    {
        const Vector2d v1(1.0, 2.0);
        const Vector2d v2(8.0, 10.0);

        const Vector2d v = v1 * v2;

        EXPECT_DOUBLE_EQ(v.getX(), 8.0);
        EXPECT_DOUBLE_EQ(v.getY(), 20.0);
    }
}

TEST(TestVector2d, divVectorOperator)
{
    {
        Vector2d v(1.0, 2.0);
        v /= Vector2d(8.0, 10.0);

        EXPECT_DOUBLE_EQ(v.getX(), 0.125);
        EXPECT_DOUBLE_EQ(v.getY(), 0.2);
    }

    {
        const Vector2d v1(1.0, 2.0);
        const Vector2d v2(8.0, 10.0);

        const Vector2d v = v1 / v2;

        EXPECT_DOUBLE_EQ(v.getX(), 0.125);
        EXPECT_DOUBLE_EQ(v.getY(), 0.2);
    }
}

TEST(TestVector2d, addScalarOperator)
{
    {
        Vector2d v = Vector2d(1., 2.);
        v += 5.0;
        EXPECT_DOUBLE_EQ(v.getX(), 6.0);
        EXPECT_DOUBLE_EQ(v.getY(), 7.0);
    }

    {
        const Vector2d v1 = Vector2d(1., 2.);
        const Vector2d v = v1 + 5;

        EXPECT_DOUBLE_EQ(v.getX(), 6.0);
        EXPECT_DOUBLE_EQ(v.getY(), 7.0);
    }
}

TEST(TestVector2d, subScalarOperator)
{
    {
        Vector2d v = Vector2d(1., 2.);
        v -= 5.0;
        EXPECT_DOUBLE_EQ(v.getX(), -4.0);
        EXPECT_DOUBLE_EQ(v.getY(), -3.0);
    }

    {
        const Vector2d v1 = Vector2d(1., 2.);
        const Vector2d v = v1 - 5.0;

        EXPECT_DOUBLE_EQ(v.getX(), -4.0);
        EXPECT_DOUBLE_EQ(v.getY(), -3.0);
    }
}

TEST(TestVector2d, mulScalarOperator)
{
    {
        Vector2d v(1.0, 2.0);
        v *= 10.0;

        EXPECT_DOUBLE_EQ(v.getX(), 10.0);
        EXPECT_DOUBLE_EQ(v.getY(), 20.0);
    }

    {
        Vector2d v(1.0, 2.0);
        v *= 1.0;

        EXPECT_DOUBLE_EQ(v.getX(), 1.0);
        EXPECT_DOUBLE_EQ(v.getY(), 2.0);
    }

    {
        const Vector2d v1(1.0, 2.0);
        const Vector2d v = v1 * 10.0;

        EXPECT_DOUBLE_EQ(v.getX(), 10.0);
        EXPECT_DOUBLE_EQ(v.getY(), 20.0);
    }

    {
        const Vector2d v1(1.0, 2.0);
        const Vector2d v = v1 * 1.0;

        EXPECT_DOUBLE_EQ(v.getX(), 1.0);
        EXPECT_DOUBLE_EQ(v.getY(), 2.0);
    }
}

TEST(TestVector2d, divScalarOperator)
{
    {
        Vector2d v(1.0, 2.0);
        v /= 10.0;

        EXPECT_DOUBLE_EQ(v.getX(), 0.1);
        EXPECT_DOUBLE_EQ(v.getY(), 0.2);
    }

    {
        Vector2d v(1.0, 2.0);
        v /= 1.0;

        EXPECT_DOUBLE_EQ(v.getX(), 1.0);
        EXPECT_DOUBLE_EQ(v.getY(), 2.0);
    }

    {
        const Vector2d v1(1.0, 2.0);
        const Vector2d v = v1 / 10.0;

        EXPECT_DOUBLE_EQ(v.getX(), 0.1);
        EXPECT_DOUBLE_EQ(v.getY(), 0.2);
    }

    {
        const Vector2d v1(1.0, 2.0);
        const Vector2d v = v1 / 1.0;

        EXPECT_DOUBLE_EQ(v.getX(), 1.0);
        EXPECT_DOUBLE_EQ(v.getY(), 2.0);
    }
}

TEST(TestVector2d, CmpOperator)
{
    {
        const Vector2d v1 = Vector2d::unitX();
        const Vector2d v2 = Vector2d::unitY();
        EXPECT_TRUE(v1 == v1);
        EXPECT_FALSE(v1 == v2);
        EXPECT_FALSE(v1 != v1);
        EXPECT_TRUE(v1 != v2);
    }

    constexpr double DoubleEpsilonHalf = 0.5 * DoubleEpsilon;
    constexpr double DoubleEpsilon2 = 2.0 * DoubleEpsilon;

    {
        const Vector2d v1(1.0, 2.0);
        const Vector2d v2(1.0 - DoubleEpsilonHalf, 2.0 - DoubleEpsilonHalf);

        EXPECT_TRUE(v1 == v2);
        EXPECT_FALSE(v1 != v2);
    }

    {
        const Vector2d v1(1.0, 2.0);
        const Vector2d v2(1.0 - DoubleEpsilon2, 2.0 - DoubleEpsilon2);

        EXPECT_TRUE(v1 != v2);
        EXPECT_FALSE(v1 == v2);
    }
}

TEST(TestVector2, NegateOperator)
{
    // all positive
    {
        const Vector2d v = -Vector2d(1., 2.);

        EXPECT_DOUBLE_EQ(v.getX(), -1.);
        EXPECT_DOUBLE_EQ(v.getY(), -2.);
    }

    // all negative
    {
        const Vector2d v = -Vector2d(-1., -2.);

        EXPECT_DOUBLE_EQ(v.getX(), 1.);
        EXPECT_DOUBLE_EQ(v.getY(), 2.);
    }

    // all randome values
    {
        const Vector2d v = -Vector2d(-1.25, 14.04);

        EXPECT_DOUBLE_EQ(v.getX(), 1.25);
        EXPECT_DOUBLE_EQ(v.getY(), -14.04);
    }
}

TEST(TestVector2d, Dot)
{
    {
        const Vector2d v1 = Vector2d::unitX();
        const Vector2d v2 = Vector2d::unitY();
        EXPECT_DOUBLE_EQ(Vector2d::dot(v1, v2), 0.0);
    }

    {
        const Vector2d v1 = Vector2d::unitX();
        const Vector2d v2 = Vector2d::unitY();
        EXPECT_DOUBLE_EQ(Vector2d::dot(v1, v2), 0.0);
    }

    {
        const Vector2d v1 = Vector2d::unitX();
        EXPECT_DOUBLE_EQ(Vector2d::dot(v1, v1), 1.0);
    }

    {
        const Vector2d v1 = Vector2d::unitY();
        EXPECT_DOUBLE_EQ(Vector2d::dot(v1, v1), 1.0);
    }

    {
        const Vector2d v1(1.0, 2.0);
        const Vector2d v2(5.0, 6.0);

        // 1*5 + 2*6 + 3*7 + 4*8 = 70
        EXPECT_DOUBLE_EQ(Vector2d::dot(v1, v2), 17.0);
    }

    {
        const Vector2d v1(1.0, -2.0);
        const Vector2d v2(-5.0, 6.0);

        EXPECT_DOUBLE_EQ(Vector2d::dot(v1, v2), -17.0);
    }

    {
        const Vector2d zero(0.0, 0.0);
        const Vector2d v(1.0, 2.0);

        EXPECT_DOUBLE_EQ(Vector2d::dot(zero, v), 0.0);
    }

    {
        const Vector2d v1(4.0, -2.0);
        const Vector2d v2(5.0, 2.0);

        EXPECT_DOUBLE_EQ(Vector2d::dot(v1, v2), 16.0);
        EXPECT_DOUBLE_EQ(Vector2d::dot(v2, v1), 16.0);
    }
}

TEST(TestVector2d, lengthSquare)
{
    // unit vector lengthSquare by definition is 1
    {
        const Vector2d v1 = Vector2d::unitX();
        EXPECT_DOUBLE_EQ(v1.lengthSquare(), 1.0);

        const Vector2d v2 = Vector2d::unitY();
        EXPECT_DOUBLE_EQ(v2.lengthSquare(), 1.0);
    }
    {
        const Vector2d v1 = Vector2d(-1.0, 0.0);
        EXPECT_DOUBLE_EQ(v1.lengthSquare(), 1.0);
    }

    {
        const Vector2d v1 = Vector2d(-1.0, -2.0);
        EXPECT_DOUBLE_EQ(v1.lengthSquare(), 5);
    }
}

TEST(TestVector2d, length)
{

    // unit vector length by definition is 1
    {
        const Vector2d v1 = Vector2d::unitX();
        EXPECT_DOUBLE_EQ(v1.length(), 1.0);

        const Vector2d v2 = Vector2d::unitY();
        EXPECT_DOUBLE_EQ(v2.length(), 1.0);
    }

    // Some arbitrary vector
    //
    {
        const Vector2d v1 = Vector2d(-1.0, -2.0);
        EXPECT_DOUBLE_EQ(v1.length(), std::sqrt(5.0));
        EXPECT_DOUBLE_EQ(v1.length(), std::sqrt(v1.lengthSquare()));
    }

    // test negative value
    {
        const Vector2d v1 = Vector2d(-1.0, 0.0);
        EXPECT_DOUBLE_EQ(v1.length(), 1.0);
    }
}

TEST(TestVector2d, distanceSquare)
{
    // unit vector
    {
        const Vector2d v1 = Vector2d::unitX();
        const Vector2d v2 = Vector2d::unitX();

        EXPECT_DOUBLE_EQ(Vector2d::distanceSquare(v1, v2), 0.0);
    }

    // Same arbitrary vector
    {
        const Vector2d v1(10.0, 20.0);
        const Vector2d v2(10.0, 20.0);

        EXPECT_DOUBLE_EQ(Vector2d::distanceSquare(v1, v2), 0.0);
    }

    // Difference only on X
    {
        const Vector2d v1(1.0, 2.0);
        const Vector2d v2(4.0, 2.0);

        EXPECT_DOUBLE_EQ(Vector2d::distanceSquare(v1, v2), 9.0);
    }

    // Difference only on Y
    {
        const Vector2d v1(1.0, 2.0);
        const Vector2d v2(1.0, 6.0);

        EXPECT_DOUBLE_EQ(Vector2d::distanceSquare(v1, v2), 16.0);
    }

    // Difference on every component
    {
        const Vector2d v1(-1.0, -2.0);
        const Vector2d v2(1.0, 2.0);

        // (-2)^2 + (-4)^2
        // = 4 + 16
        // = 20
        EXPECT_DOUBLE_EQ(Vector2d::distanceSquare(v1, v2), 20.0);
    }

    // Negative and positive values
    {
        const Vector2d v1(-1.0, -2.0);
        const Vector2d v2(1.0, 2.0);

        // 2^2 + 4^2
        // = 4 + 16
        // = 20
        EXPECT_DOUBLE_EQ(Vector2d::distanceSquare(v1, v2), 20.0);
    }

    // Symmetry
    {
        const Vector2d v1(2.0, -3.0);
        const Vector2d v2(-4.0, 8.0);

        EXPECT_DOUBLE_EQ(Vector2d::distanceSquare(v1, v2), Vector2d::distanceSquare(v2, v1));
    }

    // distanceSquare(a, b) == (a - b).lengthSquare()
    {
        const Vector2d v1(-4.0, 7.0);
        const Vector2d v2(3.0, -2.0);

        const Vector2d difference = v1 - v2;

        EXPECT_DOUBLE_EQ(Vector2d::distanceSquare(v1, v2), difference.lengthSquare());
    }
}

TEST(TestVector2d, distance)
{
    // unit vector
    {
        const Vector2d v1 = Vector2d::unitX();
        const Vector2d v2 = Vector2d::unitX();

        EXPECT_DOUBLE_EQ(Vector2d::distance(v1, v2), 0.0);
    }

    // Same arbitrary vector
    {
        const Vector2d v1(10.0, 20.0);
        const Vector2d v2(10.0, 20.0);

        EXPECT_DOUBLE_EQ(Vector2d::distance(v1, v2), 0.0);
    }

    // Difference only on X
    {
        const Vector2d v1(1.0, 2.0);
        const Vector2d v2(4.0, 2.0);

        EXPECT_DOUBLE_EQ(Vector2d::distance(v1, v2), 3.0);
    }

    // Difference only on Y
    {
        const Vector2d v1(1.0, 2.0);
        const Vector2d v2(1.0, 6.0);

        EXPECT_DOUBLE_EQ(Vector2d::distance(v1, v2), 4.0);
    }

    // Difference on every component
    {
        const Vector2d v1(-1.0, -2.0);
        const Vector2d v2(1.0, 2.0);

        // (-2)^2 + (-4)^2
        // = 4 + 16
        // = 20
        EXPECT_DOUBLE_EQ(Vector2d::distance(v1, v2), std::sqrt(20.0));
    }

    // Negative and positive values
    {
        const Vector2d v1(-1.0, -2.0);
        const Vector2d v2(1.0, 2.0);

        // 2^2 + 4^2
        // = 4 + 16
        // = 20
        EXPECT_DOUBLE_EQ(Vector2d::distance(v1, v2), std::sqrt(20.0));
    }

    // Symmetry
    {
        const Vector2d v1(2.0, -3.0);
        const Vector2d v2(-4.0, 8.0);

        EXPECT_DOUBLE_EQ(Vector2d::distance(v1, v2), Vector2d::distance(v2, v1));
    }

    // distance(a, b) == (a - b).length()
    {
        const Vector2d v1(-4.0, 7.0);
        const Vector2d v2(3.0, -2.0);

        const Vector2d difference = v1 - v2;

        EXPECT_DOUBLE_EQ(Vector2d::distance(v1, v2), difference.length());
    }
}

TEST(TestVector2d, getNormalize)
{
    {
        const Vector2d v(3.0, 4.0);
        const Vector2d normalized = v.getNormalize();

        EXPECT_NEAR(normalized.getX(), 0.6, DoubleEpsilon);
        EXPECT_NEAR(normalized.getY(), 0.8, DoubleEpsilon);

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);

        // getNormalize() must not modify the original vector.
        EXPECT_DOUBLE_EQ(v.getX(), 3.0);
        EXPECT_DOUBLE_EQ(v.getY(), 4.0);
    }

    {
        const Vector2d v(-1.0, -2.0);
        const Vector2d normalized = v.getNormalize();

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);
    }

    // Already normalized.
    {
        const Vector2d v = Vector2d::unitX();
        const Vector2d normalized = v.getNormalize();

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(normalized.getX(), 1.0, DoubleEpsilon);
    }

    // Zero vector.
    {
        const Vector2d v(Vector2d::zero());
        const Vector2d normalized = v.getNormalize();

        EXPECT_DOUBLE_EQ(normalized.getX(), 0.0);
        EXPECT_DOUBLE_EQ(normalized.getY(), 0.0);
    }
}

TEST(TestVector2d, normalize)
{
    {
        Vector2d v(3.0, 4.0);

        v.normalize();

        EXPECT_NEAR(v.getX(), 0.6, DoubleEpsilon);
        EXPECT_NEAR(v.getY(), 0.8, DoubleEpsilon);

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
    }

    {
        Vector2d v(-1.0, -2.0);

        v.normalize();

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
    }

    // Already normalized.
    {
        Vector2d v = Vector2d::unitX();

        v.normalize();

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(v.getX(), 1.0, DoubleEpsilon);
    }

    // Zero vector should remain zero.
    {
        Vector2d v(Vector2d::zero());

        v.normalize();

        EXPECT_DOUBLE_EQ(v.getX(), 0.0);
        EXPECT_DOUBLE_EQ(v.getY(), 0.0);
    }

    // normalize() should return *this.
    {
        Vector2d v(3.0, 4.0);

        Vector2d const& result = v.normalize();

        EXPECT_EQ(&result, &v);
    }
}

TEST(TestVector2d, getNormalizeFast)
{
    {
        const Vector2d v(3.0, 4.0);
        const Vector2d normalized = v.getNormalizeFast();

        EXPECT_NEAR(normalized.getX(), 0.6, DoubleEpsilon);
        EXPECT_NEAR(normalized.getY(), 0.8, DoubleEpsilon);

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);

        // getNormalizeFast() must not modify the original vector.
        EXPECT_DOUBLE_EQ(v.getX(), 3.0);
        EXPECT_DOUBLE_EQ(v.getY(), 4.0);
    }

    {
        const Vector2d v(-1.0, -2.0);
        const Vector2d normalized = v.getNormalizeFast();

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);
    }

    // Already normalized.
    {
        const Vector2d v = Vector2d::unitX();
        const Vector2d normalized = v.getNormalizeFast();

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(normalized.getX(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(normalized.getY(), 0.0, DoubleEpsilon);
    }

    // Zero vector.
    {
        const Vector2d v(0.0, 0.0);
        const Vector2d normalized = v.getNormalizeFast();

        EXPECT_DOUBLE_EQ(normalized.getX(), 0.0);
        EXPECT_DOUBLE_EQ(normalized.getY(), 0.0);
    }
}

TEST(TestVector2d, normalizeFast)
{
    {
        Vector2d v(3.0, 4.0);

        v.normalizeFast();

        EXPECT_NEAR(v.getX(), 0.6, DoubleEpsilon);
        EXPECT_NEAR(v.getY(), 0.8, DoubleEpsilon);

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
    }

    {
        Vector2d v(-1.0, -2.0);

        v.normalizeFast();

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
    }

    // Already normalizeFastd.
    {
        Vector2d v = Vector2d::unitX();

        v.normalizeFast();

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(v.getX(), 1.0, DoubleEpsilon);
    }

    // Zero vector should remain zero.
    {
        Vector2d v(0.0, 0.0);

        v.normalizeFast();

        EXPECT_DOUBLE_EQ(v.getX(), 0.0);
        EXPECT_DOUBLE_EQ(v.getY(), 0.0);
    }

    // normalizeFast() should return *this.
    {
        Vector2d v(3.0, 4.0);

        Vector2d const& result = v.normalizeFast();

        EXPECT_EQ(&result, &v);
    }
}

TEST(TestVector2d, cross)
{
    { // Collinear => 0.0
        const Vector2d v0 = Vector2d::unitX();

        const double cross = Vector2d::cross(v0, v0);

        EXPECT_NEAR(cross, 0.0, DoubleEpsilon);
    }

    { // Perpendicular CCW => 1.0
        const Vector2d v0 = Vector2d::unitX();
        const Vector2d v1 = Vector2d::unitY();

        const double cross = Vector2d::cross(v0, v1);

        EXPECT_NEAR(cross, 1.0, DoubleEpsilon);
    }

    { // Perpendicular => cross magnitude equals product of magnitudes
        const Vector2d v0(8.0, 0.0);
        const Vector2d v1(0.0, 12.0);

        const double cross = Vector2d::cross(v0, v1);

        EXPECT_NEAR(cross, v0.length() * v1.length(), DoubleEpsilon);
    }
}

TEST(TestVector2d, min)
{
    {
        const Vector2d v0(1.0, 2.0);
        const Vector2d v1(3.0, 4.0);

        const Vector2d result = Vector2d::min(v0, v1);

        EXPECT_DOUBLE_EQ(result.getX(), 1.0);
        EXPECT_DOUBLE_EQ(result.getY(), 2.0);
    }

    { // Minimum comes from different vectors
        const Vector2d v0(8.0, -4.0);
        const Vector2d v1(2.0, 12.0);

        const Vector2d result = Vector2d::min(v0, v1);

        EXPECT_DOUBLE_EQ(result.getX(), 2.0);
        EXPECT_DOUBLE_EQ(result.getY(), -4.0);
    }

    { // Equal components
        const Vector2d v0(5.0, 3.0);
        const Vector2d v1(5.0, 3.0);

        const Vector2d result = Vector2d::min(v0, v1);

        EXPECT_DOUBLE_EQ(result.getX(), 5.0);
        EXPECT_DOUBLE_EQ(result.getY(), 3.0);
    }

    { // Negative values
        const Vector2d v0(-10.0, -2.0);
        const Vector2d v1(-4.0, -8.0);

        const Vector2d result = Vector2d::min(v0, v1);

        EXPECT_DOUBLE_EQ(result.getX(), -10.0);
        EXPECT_DOUBLE_EQ(result.getY(), -8.0);
    }
}

TEST(TestVector2d, max)
{
    {
        const Vector2d v0(1.0, 2.0);
        const Vector2d v1(3.0, 4.0);

        const Vector2d result = Vector2d::max(v0, v1);

        EXPECT_DOUBLE_EQ(result.getX(), 3.0);
        EXPECT_DOUBLE_EQ(result.getY(), 4.0);
    }

    { // Maximum comes from different vectors
        const Vector2d v0(8.0, -4.0);
        const Vector2d v1(2.0, 12.0);

        const Vector2d result = Vector2d::max(v0, v1);

        EXPECT_DOUBLE_EQ(result.getX(), 8.0);
        EXPECT_DOUBLE_EQ(result.getY(), 12.0);
    }

    { // Equal components
        const Vector2d v0(5.0, 3.0);
        const Vector2d v1(5.0, 3.0);

        const Vector2d result = Vector2d::max(v0, v1);

        EXPECT_DOUBLE_EQ(result.getX(), 5.0);
        EXPECT_DOUBLE_EQ(result.getY(), 3.0);
    }

    { // Negative values
        const Vector2d v0(-10.0, -2.0);
        const Vector2d v1(-4.0, -8.0);

        const Vector2d result = Vector2d::max(v0, v1);

        EXPECT_DOUBLE_EQ(result.getX(), -4.0);
        EXPECT_DOUBLE_EQ(result.getY(), -2.0);
    }
}

TEST(TestVector2d, abs)
{
    // Full Positive
    {
        const Vector2d result = Vector2d(1.0, 2.0).abs();
        EXPECT_DOUBLE_EQ(result.getX(), 1.0);
        EXPECT_DOUBLE_EQ(result.getY(), 2.0);
    }

    // X negative
    {
        const Vector2d result = Vector2d(-1.0, 2.0).abs();
        EXPECT_DOUBLE_EQ(result.getX(), 1.0);
        EXPECT_DOUBLE_EQ(result.getY(), 2.0);
    }

    // Y negative
    {
        const Vector2d result = Vector2d(1.0, -2.0).abs();
        EXPECT_DOUBLE_EQ(result.getX(), 1.0);
        EXPECT_DOUBLE_EQ(result.getY(), 2.0);
    }

    // X and Y negative
    {
        const Vector2d result = Vector2d(-1.0, -2.0).abs();
        EXPECT_DOUBLE_EQ(result.getX(), 1.0);
        EXPECT_DOUBLE_EQ(result.getY(), 2.0);
    }
}

TEST(TestVector2d, stroreToUnAlignedDouble)
{
    {
        std::array<double, 2> data;
        const Vector2d v(1.0, 2.0);
        v.storeToUnalignedDouble(data.data());
        EXPECT_NEAR(data[0], 1.0, DoubleEpsilon);
        EXPECT_NEAR(data[1], 2.0, DoubleEpsilon);
    }

    {
        std::array<double, 2> data;
        const Vector2d v(1.0, 2.0);
        v.storeToUnalignedDouble(std::span<double, 2>(data));
        EXPECT_NEAR(data[0], 1.0, DoubleEpsilon);
        EXPECT_NEAR(data[1], 2.0, DoubleEpsilon);
    }
}

TEST(TestVector2d, storeToUnAlignedFloat)
{
    {
        std::array<float, 2> data;
        const Vector2d v(1.0, 2.0);
        v.storeToUnAlignedFloat(data.data());
        EXPECT_NEAR(data[0], 1.0f, FloatEpsilon);
        EXPECT_NEAR(data[1], 2.0f, FloatEpsilon);
    }

    {
        std::array<float, 2> data;
        const Vector2d v(1.0, 2.0);
        v.storeToUnAlignedFloat(std::span<float, 2>(data));
        EXPECT_NEAR(data[0], 1.0f, FloatEpsilon);
        EXPECT_NEAR(data[1], 2.0f, FloatEpsilon);
    }
}

TEST(TestVector2d, storeToAlignedDouble)
{
    {
        alignas(AVX_ALIGNEMENT) std::array<double, 2> data;
        const Vector2d v(1.0, 2.0);
        v.storeToAlignedDouble(data.data());
        EXPECT_NEAR(data[0], 1.0, DoubleEpsilon);
        EXPECT_NEAR(data[1], 2.0, DoubleEpsilon);
    }

    {
        alignas(AVX_ALIGNEMENT) std::array<double, 2> data;
        const Vector2d v(1.0, 2.0);
        v.storeToAlignedDouble(std::span<double, 2>(data));
        EXPECT_NEAR(data[0], 1.0, DoubleEpsilon);
        EXPECT_NEAR(data[1], 2.0, DoubleEpsilon);
    }
}

TEST(TestVector2d, streamToUnalignedFloat)
{
    {
        alignas(SSE_ALIGNEMENT) std::array<float, 2> data;
        const Vector2d v(1.0, 2.0);
        v.storeToAlignedFloat(data.data());
        EXPECT_NEAR(data[0], 1.0f, FloatEpsilon);
        EXPECT_NEAR(data[1], 2.0f, FloatEpsilon);
    }

    {
        alignas(SSE_ALIGNEMENT) std::array<float, 2> data;
        const Vector2d v(1.0, 2.0);
        v.storeToAlignedFloat(std::span<float, 2>(data));
        EXPECT_NEAR(data[0], 1.0f, FloatEpsilon);
        EXPECT_NEAR(data[1], 2.0f, FloatEpsilon);
    }
}

TEST(TestVector2d, fromUnAlignedDouble)
{
    {
        std::array<double, 2> data = {1.0, 2.0};
        Vector2d v;
        v.fromUnalignedDouble(data);
        EXPECT_NEAR(v.getX(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(v.getY(), 2.0, DoubleEpsilon);
    }

    {
        std::array<double, 2> data = {1.0, 2.0};
        Vector2d v;
        v.fromUnalignedDouble(std::span<const double, 2>(data));
        EXPECT_NEAR(v.getX(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(v.getY(), 2.0, DoubleEpsilon);
    }
}

TEST(TestVector2d, fromUnAlignedFloat)
{
    {
        std::array<float, 2> data = {1.0, 2.0};
        Vector2d v;
        v.fromUnAlignedFloat(data);
        EXPECT_NEAR(v.getX(), 1.0, FloatEpsilon);
        EXPECT_NEAR(v.getY(), 2.0, FloatEpsilon);
    }

    {
        std::array<float, 2> data = {1.0, 2.0};
        Vector2d v;
        v.fromUnAlignedFloat(std::span<const float, 2>(data));
        EXPECT_NEAR(v.getX(), 1.0, FloatEpsilon);
        EXPECT_NEAR(v.getY(), 2.0, FloatEpsilon);
    }
}

TEST(TestVector2d, fromAlignedDouble)
{
    {
        alignas(AVX_ALIGNEMENT) std::array<double, 4> data{1.0, 2.0};
        Vector2d v;
        v.fromAlignedDouble(data.data());
        EXPECT_NEAR(v.getX(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(v.getY(), 2.0, DoubleEpsilon);
        ;
    }

    {
        alignas(AVX_ALIGNEMENT) std::array<double, 2> data{1.0, 2.0};
        Vector2d v;
        v.fromAlignedDouble(std::span<double, 2>(data));
        EXPECT_NEAR(v.getX(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(v.getY(), 2.0, DoubleEpsilon);
    }
}

TEST(TestVector2d, fromAlignedFloat)
{
    {
        alignas(AVX_ALIGNEMENT) std::array<float, 2> data{1.0, 2.0};
        Vector2d v;
        v.fromAlignedFloat(data.data());
        EXPECT_NEAR(v.getX(), 1.0, FloatEpsilon);
        EXPECT_NEAR(v.getY(), 2.0, FloatEpsilon);
    }

    {
        alignas(AVX_ALIGNEMENT) std::array<float, 2> data{1.0, 2.0};
        Vector2d v;
        v.fromAlignedFloat(std::span<float, 2>(data));
        EXPECT_NEAR(v.getX(), 1.0, FloatEpsilon);
        EXPECT_NEAR(v.getY(), 2.0, FloatEpsilon);
    }
}

TEST(TestVector2, IsFinite)
{
    {
        const Vector2d v = Vector2d(1., 2.);
        EXPECT_TRUE(v.isFinite());
    }

#if !defined(NDEBUG)
    EXPECT_DEATH(
        {
            const Vector2d v(NAN, 2.0);
            (void)v;
        },
        ".*");

    EXPECT_DEATH(
        {
            const Vector2d v(0.0, INFINITY);
            (void)v;
        },
        ".*");
#else
    {
        const Vector2d v = Vector2d(NAN, 2.0);
        EXPECT_FALSE(v.isFinite());
    }

    {
        const Vector2d v = Vector2d(0.0, INFINITY);
        EXPECT_FALSE(v.isFinite());
    }
#endif
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
