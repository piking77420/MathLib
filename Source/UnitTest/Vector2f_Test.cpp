#include <gtest/gtest.h>

#include <cmath>
#include <array>
#include <span>

#include <MathLibHeader.hpp>
#include <Vector2.hpp>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

using namespace MathLib;

TEST(TestVector2f, Constructor)
{
    {
        const Vector2f v = Vector2f(1.f, 2.f);

        EXPECT_FLOAT_EQ(v.getX(), 1.0f);
        EXPECT_FLOAT_EQ(v.getY(), 2.0f);
    }

    {
        const Vector2f v = Vector2f(3.0f);

        EXPECT_FLOAT_EQ(v.getX(), 3.0f);
        EXPECT_FLOAT_EQ(v.getY(), 3.0f);
    }
}

TEST(TestVector2f, Setter)
{
    Vector2f v{};
    v.setX(8.f);
    v.setY(4.0f);
    EXPECT_FLOAT_EQ(v.getX(), 8.0f);
    EXPECT_FLOAT_EQ(v.getY(), 4.0f);
    v.setX(1.f);
    EXPECT_FLOAT_EQ(v.getX(), 1.0f);
    EXPECT_FLOAT_EQ(v.getY(), 4.0f);
    v.setX(1.f);
    v.setY(2.f);
    EXPECT_FLOAT_EQ(v.getX(), 1.0f);
    EXPECT_FLOAT_EQ(v.getY(), 2.0f);
}

TEST(TestVector2f, addVectorOperator)
{
    {
        Vector2f v = Vector2f(1., 2.);
        v += Vector2f(4., 5.);
        EXPECT_FLOAT_EQ(v.getX(), 5.0);
        EXPECT_FLOAT_EQ(v.getY(), 7.0);
    }

    {
        const Vector2f v1 = Vector2f(1., 2.);
        const Vector2f v2 = Vector2f(4., 5.);
        const Vector2f v = v1 + v2;

        EXPECT_FLOAT_EQ(v.getX(), 5.0);
        EXPECT_FLOAT_EQ(v.getY(), 7.0);
    }
}

TEST(TestVector2f, subVectorOperator)
{
    {
        Vector2f v(1.0, 2.0);
        v -= Vector2f(8.0, 10.0);

        EXPECT_FLOAT_EQ(v.getX(), -7.0);
        EXPECT_FLOAT_EQ(v.getY(), -8.0);
    }

    {
        const Vector2f v1(1.0, 2.0);
        const Vector2f v2(8.0, 10.0);

        const Vector2f v = v1 - v2;

        EXPECT_FLOAT_EQ(v.getX(), -7.0);
        EXPECT_FLOAT_EQ(v.getY(), -8.0);
    }
}

TEST(TestVector2f, mulVectorOperator)
{
    {
        Vector2f v(1.0, 2.0);
        v *= Vector2f(8.0, 10.0);

        EXPECT_FLOAT_EQ(v.getX(), 8.0);
        EXPECT_FLOAT_EQ(v.getY(), 20.0);
    }

    {
        const Vector2f v1(1.0, 2.0);
        const Vector2f v2(8.0, 10.0);

        const Vector2f v = v1 * v2;

        EXPECT_FLOAT_EQ(v.getX(), 8.0);
        EXPECT_FLOAT_EQ(v.getY(), 20.0);
    }
}

TEST(TestVector2f, divVectorOperator)
{
    {
        Vector2f v(1.0, 2.0);
        v /= Vector2f(8.0, 10.0);

        EXPECT_FLOAT_EQ(v.getX(), 0.125);
        EXPECT_FLOAT_EQ(v.getY(), 0.2);
    }

    {
        const Vector2f v1(1.0, 2.0);
        const Vector2f v2(8.0, 10.0);

        const Vector2f v = v1 / v2;

        EXPECT_FLOAT_EQ(v.getX(), 0.125);
        EXPECT_FLOAT_EQ(v.getY(), 0.2);
    }
}

TEST(TestVector2f, addScalarOperator)
{
    {
        Vector2f v = Vector2f(1., 2.);
        v += 5.0;
        EXPECT_FLOAT_EQ(v.getX(), 6.0);
        EXPECT_FLOAT_EQ(v.getY(), 7.0);
    }

    {
        const Vector2f v1 = Vector2f(1., 2.);
        const Vector2f v = v1 + 5;

        EXPECT_FLOAT_EQ(v.getX(), 6.0);
        EXPECT_FLOAT_EQ(v.getY(), 7.0);
    }
}

TEST(TestVector2f, subScalarOperator)
{
    {
        Vector2f v = Vector2f(1., 2.);
        v -= 5.0;
        EXPECT_FLOAT_EQ(v.getX(), -4.0);
        EXPECT_FLOAT_EQ(v.getY(), -3.0);
    }

    {
        const Vector2f v1 = Vector2f(1., 2.);
        const Vector2f v = v1 - 5.0;

        EXPECT_FLOAT_EQ(v.getX(), -4.0);
        EXPECT_FLOAT_EQ(v.getY(), -3.0);
    }
}

TEST(TestVector2f, mulScalarOperator)
{
    {
        Vector2f v(1.0, 2.0);
        v *= 10.0;

        EXPECT_FLOAT_EQ(v.getX(), 10.0);
        EXPECT_FLOAT_EQ(v.getY(), 20.0);
    }

    {
        Vector2f v(1.0, 2.0);
        v *= 1.0;

        EXPECT_FLOAT_EQ(v.getX(), 1.0);
        EXPECT_FLOAT_EQ(v.getY(), 2.0);
    }

    {
        const Vector2f v1(1.0, 2.0);
        const Vector2f v = v1 * 10.0;

        EXPECT_FLOAT_EQ(v.getX(), 10.0);
        EXPECT_FLOAT_EQ(v.getY(), 20.0);
    }

    {
        const Vector2f v1(1.0, 2.0);
        const Vector2f v = v1 * 1.0;

        EXPECT_FLOAT_EQ(v.getX(), 1.0);
        EXPECT_FLOAT_EQ(v.getY(), 2.0);
    }
}

TEST(TestVector2f, divScalarOperator)
{
    {
        Vector2f v(1.0, 2.0);
        v /= 10.0;

        EXPECT_FLOAT_EQ(v.getX(), 0.1);
        EXPECT_FLOAT_EQ(v.getY(), 0.2);
    }

    {
        Vector2f v(1.0, 2.0);
        v /= 1.0;

        EXPECT_FLOAT_EQ(v.getX(), 1.0);
        EXPECT_FLOAT_EQ(v.getY(), 2.0);
    }

    {
        const Vector2f v1(1.0, 2.0);
        const Vector2f v = v1 / 10.0;

        EXPECT_FLOAT_EQ(v.getX(), 0.1);
        EXPECT_FLOAT_EQ(v.getY(), 0.2);
    }

    {
        const Vector2f v1(1.0, 2.0);
        const Vector2f v = v1 / 1.0;

        EXPECT_FLOAT_EQ(v.getX(), 1.0);
        EXPECT_FLOAT_EQ(v.getY(), 2.0);
    }
}

TEST(TestVector2f, CmpOperator)
{
    {
        const Vector2f v1 = Vector2f::unitX();
        const Vector2f v2 = Vector2f::unitY();
        EXPECT_TRUE(v1 == v1);
        EXPECT_FALSE(v1 == v2);
        EXPECT_FALSE(v1 != v1);
        EXPECT_TRUE(v1 != v2);
    }

    constexpr double FloatEpsilonHalf = 0.5 * FloatEpsilon;
    constexpr double FloatEpsilon2 = 2.0 * FloatEpsilon;

    {
        const Vector2f v1(1.0, 2.0);
        const Vector2f v2(1.0 - FloatEpsilonHalf, 2.0 - FloatEpsilonHalf);

        EXPECT_TRUE(v1 == v2);
        EXPECT_FALSE(v1 != v2);
    }

    {
        const Vector2f v1(1.0, 2.0);
        const Vector2f v2(1.0 - FloatEpsilon2, 2.0 - FloatEpsilon2);

        EXPECT_TRUE(v1 != v2);
        EXPECT_FALSE(v1 == v2);
    }
}

TEST(TestVector2f, NegateOperator)
{
    // all positive
    {
        const Vector2f v = -Vector2f(1., 2.);

        EXPECT_FLOAT_EQ(v.getX(), -1.);
        EXPECT_FLOAT_EQ(v.getY(), -2.);
    }

    // all negative
    {
        const Vector2f v = -Vector2f(-1., -2.);

        EXPECT_FLOAT_EQ(v.getX(), 1.);
        EXPECT_FLOAT_EQ(v.getY(), 2.);
    }

    // all randome values
    {
        const Vector2f v = -Vector2f(-1.25, 14.04);

        EXPECT_FLOAT_EQ(v.getX(), 1.25);
        EXPECT_FLOAT_EQ(v.getY(), -14.04);
    }
}

TEST(TestVector2f, Dot)
{
    {
        const Vector2f v1 = Vector2f::unitX();
        const Vector2f v2 = Vector2f::unitY();
        EXPECT_FLOAT_EQ(Vector2f::dot(v1, v2), 0.0);
    }

    {
        const Vector2f v1 = Vector2f::unitX();
        const Vector2f v2 = Vector2f::unitY();
        EXPECT_FLOAT_EQ(Vector2f::dot(v1, v2), 0.0);
    }

    {
        const Vector2f v1 = Vector2f::unitX();
        EXPECT_FLOAT_EQ(Vector2f::dot(v1, v1), 1.0);
    }

    {
        const Vector2f v1 = Vector2f::unitY();
        EXPECT_FLOAT_EQ(Vector2f::dot(v1, v1), 1.0);
    }

    {
        const Vector2f v1(1.0, 2.0);
        const Vector2f v2(5.0, 6.0);

        // 1*5 + 2*6 + 3*7 + 4*8 = 70
        EXPECT_FLOAT_EQ(Vector2f::dot(v1, v2), 17.0);
    }

    {
        const Vector2f v1(1.0, -2.0);
        const Vector2f v2(-5.0, 6.0);

        EXPECT_FLOAT_EQ(Vector2f::dot(v1, v2), -17.0);
    }

    {
        const Vector2f zero(0.0, 0.0);
        const Vector2f v(1.0, 2.0);

        EXPECT_FLOAT_EQ(Vector2f::dot(zero, v), 0.0);
    }

    {
        const Vector2f v1(4.0, -2.0);
        const Vector2f v2(5.0, 2.0);

        EXPECT_FLOAT_EQ(Vector2f::dot(v1, v2), 16.0);
        EXPECT_FLOAT_EQ(Vector2f::dot(v2, v1), 16.0);
    }
}

TEST(TestVector2f, lengthSquare)
{
    // unit vector lengthSquare by definition is 1
    {
        const Vector2f v1 = Vector2f::unitX();
        EXPECT_FLOAT_EQ(v1.lengthSquare(), 1.0);

        const Vector2f v2 = Vector2f::unitY();
        EXPECT_FLOAT_EQ(v2.lengthSquare(), 1.0);
    }
    {
        const Vector2f v1 = Vector2f(-1.0, 0.0);
        EXPECT_FLOAT_EQ(v1.lengthSquare(), 1.0);
    }

    {
        const Vector2f v1 = Vector2f(-1.0, -2.0);
        EXPECT_FLOAT_EQ(v1.lengthSquare(), 5);
    }
}

TEST(TestVector2f, length)
{

    // unit vector length by definition is 1
    {
        const Vector2f v1 = Vector2f::unitX();
        EXPECT_FLOAT_EQ(v1.length(), 1.0);

        const Vector2f v2 = Vector2f::unitY();
        EXPECT_FLOAT_EQ(v2.length(), 1.0);
    }

    // Some arbitrary vector
    //
    {
        const Vector2f v1 = Vector2f(-1.0, -2.0);
        EXPECT_FLOAT_EQ(v1.length(), std::sqrt(5.0));
        EXPECT_FLOAT_EQ(v1.length(), std::sqrt(v1.lengthSquare()));
    }

    // test negative value
    {
        const Vector2f v1 = Vector2f(-1.0, 0.0);
        EXPECT_FLOAT_EQ(v1.length(), 1.0);
    }
}

TEST(TestVector2f, distanceSquare)
{
    // unit vector
    {
        const Vector2f v1 = Vector2f::unitX();
        const Vector2f v2 = Vector2f::unitX();

        EXPECT_FLOAT_EQ(Vector2f::distanceSquare(v1, v2), 0.0);
    }

    // Same arbitrary vector
    {
        const Vector2f v1(10.0, 20.0);
        const Vector2f v2(10.0, 20.0);

        EXPECT_FLOAT_EQ(Vector2f::distanceSquare(v1, v2), 0.0);
    }

    // Difference only on X
    {
        const Vector2f v1(1.0, 2.0);
        const Vector2f v2(4.0, 2.0);

        EXPECT_FLOAT_EQ(Vector2f::distanceSquare(v1, v2), 9.0);
    }

    // Difference only on Y
    {
        const Vector2f v1(1.0, 2.0);
        const Vector2f v2(1.0, 6.0);

        EXPECT_FLOAT_EQ(Vector2f::distanceSquare(v1, v2), 16.0);
    }

    // Difference on every component
    {
        const Vector2f v1(-1.0, -2.0);
        const Vector2f v2(1.0, 2.0);

        // (-2)^2 + (-4)^2
        // = 4 + 16
        // = 20
        EXPECT_FLOAT_EQ(Vector2f::distanceSquare(v1, v2), 20.0);
    }

    // Negative and positive values
    {
        const Vector2f v1(-1.0, -2.0);
        const Vector2f v2(1.0, 2.0);

        // 2^2 + 4^2
        // = 4 + 16
        // = 20
        EXPECT_FLOAT_EQ(Vector2f::distanceSquare(v1, v2), 20.0);
    }

    // Symmetry
    {
        const Vector2f v1(2.0, -3.0);
        const Vector2f v2(-4.0, 8.0);

        EXPECT_FLOAT_EQ(Vector2f::distanceSquare(v1, v2), Vector2f::distanceSquare(v2, v1));
    }

    // distanceSquare(a, b) == (a - b).lengthSquare()
    {
        const Vector2f v1(-4.0, 7.0);
        const Vector2f v2(3.0, -2.0);

        const Vector2f difference = v1 - v2;

        EXPECT_FLOAT_EQ(Vector2f::distanceSquare(v1, v2), difference.lengthSquare());
    }
}

TEST(TestVector2f, distance)
{
    // unit vector
    {
        const Vector2f v1 = Vector2f::unitX();
        const Vector2f v2 = Vector2f::unitX();

        EXPECT_FLOAT_EQ(Vector2f::distance(v1, v2), 0.0);
    }

    // Same arbitrary vector
    {
        const Vector2f v1(10.0, 20.0);
        const Vector2f v2(10.0, 20.0);

        EXPECT_FLOAT_EQ(Vector2f::distance(v1, v2), 0.0);
    }

    // Difference only on X
    {
        const Vector2f v1(1.0, 2.0);
        const Vector2f v2(4.0, 2.0);

        EXPECT_FLOAT_EQ(Vector2f::distance(v1, v2), 3.0);
    }

    // Difference only on Y
    {
        const Vector2f v1(1.0, 2.0);
        const Vector2f v2(1.0, 6.0);

        EXPECT_FLOAT_EQ(Vector2f::distance(v1, v2), 4.0);
    }

    // Difference on every component
    {
        const Vector2f v1(-1.0, -2.0);
        const Vector2f v2(1.0, 2.0);

        // (-2)^2 + (-4)^2
        // = 4 + 16
        // = 20
        EXPECT_FLOAT_EQ(Vector2f::distance(v1, v2), std::sqrt(20.0));
    }

    // Negative and positive values
    {
        const Vector2f v1(-1.0, -2.0);
        const Vector2f v2(1.0, 2.0);

        // 2^2 + 4^2
        // = 4 + 16
        // = 20
        EXPECT_FLOAT_EQ(Vector2f::distance(v1, v2), std::sqrt(20.0));
    }

    // Symmetry
    {
        const Vector2f v1(2.0, -3.0);
        const Vector2f v2(-4.0, 8.0);

        EXPECT_FLOAT_EQ(Vector2f::distance(v1, v2), Vector2f::distance(v2, v1));
    }

    // distance(a, b) == (a - b).length()
    {
        const Vector2f v1(-4.0, 7.0);
        const Vector2f v2(3.0, -2.0);

        const Vector2f difference = v1 - v2;

        EXPECT_FLOAT_EQ(Vector2f::distance(v1, v2), difference.length());
    }
}

TEST(TestVector2f, getNormalize)
{
    {
        const Vector2f v(3.0, 4.0);
        const Vector2f normalized = v.getNormalize();

        EXPECT_NEAR(normalized.getX(), 0.6, DoubleEpsilon);
        EXPECT_NEAR(normalized.getY(), 0.8, DoubleEpsilon);

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);

        // getNormalize() must not modify the original vector.
        EXPECT_FLOAT_EQ(v.getX(), 3.0);
        EXPECT_FLOAT_EQ(v.getY(), 4.0);
    }

    {
        const Vector2f v(-1.0, -2.0);
        const Vector2f normalized = v.getNormalize();

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);
    }

    // Already normalized.
    {
        const Vector2f v = Vector2f::unitX();
        const Vector2f normalized = v.getNormalize();

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(normalized.getX(), 1.0, DoubleEpsilon);
    }

    // Zero vector.
    {
        const Vector2f v(Vector2f::zero());
        const Vector2f normalized = v.getNormalize();

        EXPECT_FLOAT_EQ(normalized.getX(), 0.0);
        EXPECT_FLOAT_EQ(normalized.getY(), 0.0);
    }
}

TEST(TestVector2f, normalize)
{
    {
        Vector2f v(3.0, 4.0);

        v.normalize();

        EXPECT_NEAR(v.getX(), 0.6, DoubleEpsilon);
        EXPECT_NEAR(v.getY(), 0.8, DoubleEpsilon);

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
    }

    {
        Vector2f v(-1.0, -2.0);

        v.normalize();

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
    }

    // Already normalized.
    {
        Vector2f v = Vector2f::unitX();

        v.normalize();

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(v.getX(), 1.0, DoubleEpsilon);
    }

    // Zero vector should remain zero.
    {
        Vector2f v(Vector2f::zero());

        v.normalize();

        EXPECT_FLOAT_EQ(v.getX(), 0.0);
        EXPECT_FLOAT_EQ(v.getY(), 0.0);
    }

    // normalize() should return *this.
    {
        Vector2f v(3.0, 4.0);

        Vector2f const& result = v.normalize();

        EXPECT_EQ(&result, &v);
    }
}

TEST(TestVector2f, getNormalizeFast)
{
    {
        const Vector2f v(3.0, 4.0);
        const Vector2f normalized = v.getNormalizeFast();

        EXPECT_NEAR(normalized.getX(), 0.6, DoubleEpsilon);
        EXPECT_NEAR(normalized.getY(), 0.8, DoubleEpsilon);

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);

        // getNormalizeFast() must not modify the original vector.
        EXPECT_FLOAT_EQ(v.getX(), 3.0);
        EXPECT_FLOAT_EQ(v.getY(), 4.0);
    }

    {
        const Vector2f v(-1.0, -2.0);
        const Vector2f normalized = v.getNormalizeFast();

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);
    }

    // Already normalized.
    {
        const Vector2f v = Vector2f::unitX();
        const Vector2f normalized = v.getNormalizeFast();

        EXPECT_NEAR(normalized.length(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(normalized.getX(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(normalized.getY(), 0.0, DoubleEpsilon);
    }

    // Zero vector.
    {
        const Vector2f v(0.0, 0.0);
        const Vector2f normalized = v.getNormalizeFast();

        EXPECT_FLOAT_EQ(normalized.getX(), 0.0);
        EXPECT_FLOAT_EQ(normalized.getY(), 0.0);
    }
}

TEST(TestVector2f, normalizeFast)
{
    {
        Vector2f v(3.0, 4.0);

        v.normalizeFast();

        EXPECT_NEAR(v.getX(), 0.6, DoubleEpsilon);
        EXPECT_NEAR(v.getY(), 0.8, DoubleEpsilon);

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
    }

    {
        Vector2f v(-1.0, -2.0);

        v.normalizeFast();

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
    }

    // Already normalizeFastd.
    {
        Vector2f v = Vector2f::unitX();

        v.normalizeFast();

        EXPECT_NEAR(v.length(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(v.getX(), 1.0, DoubleEpsilon);
    }

    // Zero vector should remain zero.
    {
        Vector2f v(0.0, 0.0);

        v.normalizeFast();

        EXPECT_FLOAT_EQ(v.getX(), 0.0);
        EXPECT_FLOAT_EQ(v.getY(), 0.0);
    }

    // normalizeFast() should return *this.
    {
        Vector2f v(3.0, 4.0);

        Vector2f const& result = v.normalizeFast();

        EXPECT_EQ(&result, &v);
    }
}

TEST(TestVector2f, cross)
{
    { // Collinear => 0.0
        const Vector2f v0 = Vector2f::unitX();

        const double cross = Vector2f::cross(v0, v0);

        EXPECT_NEAR(cross, 0.0, DoubleEpsilon);
    }

    { // Perpendicular CCW => 1.0
        const Vector2f v0 = Vector2f::unitX();
        const Vector2f v1 = Vector2f::unitY();

        const double cross = Vector2f::cross(v0, v1);

        EXPECT_NEAR(cross, 1.0, DoubleEpsilon);
    }

    { // Perpendicular => cross magnitude equals product of magnitudes
        const Vector2f v0(8.0, 0.0);
        const Vector2f v1(0.0, 12.0);

        const double cross = Vector2f::cross(v0, v1);

        EXPECT_NEAR(cross, v0.length() * v1.length(), DoubleEpsilon);
    }
}

TEST(TestVector2f, min)
{
    {
        const Vector2f v0(1.0, 2.0);
        const Vector2f v1(3.0, 4.0);

        const Vector2f result = Vector2f::min(v0, v1);

        EXPECT_FLOAT_EQ(result.getX(), 1.0);
        EXPECT_FLOAT_EQ(result.getY(), 2.0);
    }

    { // Minimum comes from different vectors
        const Vector2f v0(8.0, -4.0);
        const Vector2f v1(2.0, 12.0);

        const Vector2f result = Vector2f::min(v0, v1);

        EXPECT_FLOAT_EQ(result.getX(), 2.0);
        EXPECT_FLOAT_EQ(result.getY(), -4.0);
    }

    { // Equal components
        const Vector2f v0(5.0, 3.0);
        const Vector2f v1(5.0, 3.0);

        const Vector2f result = Vector2f::min(v0, v1);

        EXPECT_FLOAT_EQ(result.getX(), 5.0);
        EXPECT_FLOAT_EQ(result.getY(), 3.0);
    }

    { // Negative values
        const Vector2f v0(-10.0, -2.0);
        const Vector2f v1(-4.0, -8.0);

        const Vector2f result = Vector2f::min(v0, v1);

        EXPECT_FLOAT_EQ(result.getX(), -10.0);
        EXPECT_FLOAT_EQ(result.getY(), -8.0);
    }
}

TEST(TestVector2f, max)
{
    {
        const Vector2f v0(1.0, 2.0);
        const Vector2f v1(3.0, 4.0);

        const Vector2f result = Vector2f::max(v0, v1);

        EXPECT_FLOAT_EQ(result.getX(), 3.0);
        EXPECT_FLOAT_EQ(result.getY(), 4.0);
    }

    { // Maximum comes from different vectors
        const Vector2f v0(8.0, -4.0);
        const Vector2f v1(2.0, 12.0);

        const Vector2f result = Vector2f::max(v0, v1);

        EXPECT_FLOAT_EQ(result.getX(), 8.0);
        EXPECT_FLOAT_EQ(result.getY(), 12.0);
    }

    { // Equal components
        const Vector2f v0(5.0, 3.0);
        const Vector2f v1(5.0, 3.0);

        const Vector2f result = Vector2f::max(v0, v1);

        EXPECT_FLOAT_EQ(result.getX(), 5.0);
        EXPECT_FLOAT_EQ(result.getY(), 3.0);
    }

    { // Negative values
        const Vector2f v0(-10.0, -2.0);
        const Vector2f v1(-4.0, -8.0);

        const Vector2f result = Vector2f::max(v0, v1);

        EXPECT_FLOAT_EQ(result.getX(), -4.0);
        EXPECT_FLOAT_EQ(result.getY(), -2.0);
    }
}

TEST(TestVector2f, abs)
{
    // Full Positive
    {
        const Vector2f result = Vector2f(1.0, 2.0).abs();
        EXPECT_FLOAT_EQ(result.getX(), 1.0);
        EXPECT_FLOAT_EQ(result.getY(), 2.0);
    }

    // X negative
    {
        const Vector2f result = Vector2f(-1.0, 2.0).abs();
        EXPECT_FLOAT_EQ(result.getX(), 1.0);
        EXPECT_FLOAT_EQ(result.getY(), 2.0);
    }

    // Y negative
    {
        const Vector2f result = Vector2f(1.0, -2.0).abs();
        EXPECT_FLOAT_EQ(result.getX(), 1.0);
        EXPECT_FLOAT_EQ(result.getY(), 2.0);
    }

    // X and Y negative
    {
        const Vector2f result = Vector2f(-1.0, -2.0).abs();
        EXPECT_FLOAT_EQ(result.getX(), 1.0);
        EXPECT_FLOAT_EQ(result.getY(), 2.0);
    }
}

TEST(TestVector2f, IsFinite)
{
    {
        const Vector2f v = Vector2f(1., 2.);
        EXPECT_TRUE(v.isFinite());
    }

#if !defined(NDEBUG)
    EXPECT_DEATH(
        {
            const Vector2f v(NAN, 2.0);
            (void)v;
        },
        ".*");

    EXPECT_DEATH(
        {
            const Vector2f v(0.0, INFINITY);
            (void)v;
        },
        ".*");
#else
    {
        const Vector2f v = Vector2f(NAN, 2.0);
        EXPECT_FALSE(v.isFinite());
    }

    {
        const Vector2f v = Vector2f(0.0, INFINITY);
        EXPECT_FALSE(v.isFinite());
    }
#endif
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
