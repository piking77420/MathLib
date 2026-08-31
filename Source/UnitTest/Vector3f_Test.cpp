#include <gtest/gtest.h>
#include <MathLibHeader.hpp>
#include <Vector3.hpp>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
using namespace MathLib;

TEST(TestVector3f, Constructor)
{
    const Vector3f v = Vector3f(1., 2., 3.);

    EXPECT_FLOAT_EQ(v.getX(), 1.0);
    EXPECT_FLOAT_EQ(v.getY(), 2.0);
    EXPECT_FLOAT_EQ(v.getZ(), 3.0);
}

TEST(TestVector3f, Setter)
{
    Vector3f v{};
    v.setX(1.);
    v.setY(2.);
    v.setZ(3.);

    EXPECT_FLOAT_EQ(v.getX(), 1.0);
    EXPECT_FLOAT_EQ(v.getY(), 2.0);
    EXPECT_FLOAT_EQ(v.getZ(), 3.0);
}

TEST(TestVector3f, addVectorOperator)
{
    {
        Vector3f v = Vector3f(1., 2., 3.);
        const Vector3f v1 = Vector3f(4., 5., 6.);
        v += v1;

        EXPECT_FLOAT_EQ(v.getX(), 5.0);
        EXPECT_FLOAT_EQ(v.getY(), 7.0);
        EXPECT_FLOAT_EQ(v.getZ(), 9.0);
    }

    {
        const Vector3f v1 = Vector3f(1., 2., 3.);
        const Vector3f v2 = Vector3f(4., 5., 6.);
        const Vector3f v = v1 + v2;

        EXPECT_FLOAT_EQ(v.getX(), 5.0);
        EXPECT_FLOAT_EQ(v.getY(), 7.0);
        EXPECT_FLOAT_EQ(v.getZ(), 9.0);
    }
}

TEST(TestVector3f, subVectorOperator)
{
    {
        Vector3f v(1.0, 2.0, 3.0);
        const Vector3f v2(8.0, 10.0, 2.0);

        v -= v2;

        EXPECT_FLOAT_EQ(v.getX(), -7.0);
        EXPECT_FLOAT_EQ(v.getY(), -8.0);
        EXPECT_FLOAT_EQ(v.getZ(), 1.0);
    }

    {
        const Vector3f v1(1.0, 2.0, 3.0);
        const Vector3f v2(8.0, 10.0, 2.0);

        const Vector3f v = v1 - v2;

        EXPECT_FLOAT_EQ(v.getX(), -7.0);
        EXPECT_FLOAT_EQ(v.getY(), -8.0);
        EXPECT_FLOAT_EQ(v.getZ(), 1.0);
    }
}

TEST(TestVector3f, mulVectorOperator)
{
    {
        Vector3f v(1.0, 2.0, 3.0);
        const Vector3f v2(8.0, 10.0, 2.0);

        v *= v2;

        EXPECT_FLOAT_EQ(v.getX(), 8.0);
        EXPECT_FLOAT_EQ(v.getY(), 20.0);
        EXPECT_FLOAT_EQ(v.getZ(), 6.0);
    }

    {
        const Vector3f v1(1.0, 2.0, 3.0);
        const Vector3f v2(8.0, 10.0, 2.0);

        const Vector3f v = v1 * v2;

        EXPECT_FLOAT_EQ(v.getX(), 8.0);
        EXPECT_FLOAT_EQ(v.getY(), 20.0);
        EXPECT_FLOAT_EQ(v.getZ(), 6.0);
    }
}

TEST(TestVector3f, divVectorOperator)
{
    {
        Vector3f v(1.0, 2.0, 3.0);
        const Vector3f v2(8.0, 10.0, 2.0);

        v /= v2;

        EXPECT_FLOAT_EQ(v.getX(), 1.0 / 8.0);
        EXPECT_FLOAT_EQ(v.getY(), 0.20);
        EXPECT_FLOAT_EQ(v.getZ(), 3.0 / 2.0);
    }

    {
        const Vector3f v1(1.0, 2.0, 3.0);
        const Vector3f v2(8.0, 10.0, 2.0);

        const Vector3f v = v1 / v2;

        EXPECT_FLOAT_EQ(v.getX(), 1.0 / 8.0);
        EXPECT_FLOAT_EQ(v.getY(), 0.20);
        EXPECT_FLOAT_EQ(v.getZ(), 3.0 / 2.0);
    }
}

TEST(TestVector3f, addScalarOperator)
{
    {
        Vector3f v = Vector3f(1., 2., 3.);
        v += 5.0;

        EXPECT_FLOAT_EQ(v.getX(), 6.0);
        EXPECT_FLOAT_EQ(v.getY(), 7.0);
        EXPECT_FLOAT_EQ(v.getZ(), 8.0);
    }

    {
        const Vector3f v = Vector3f(1., 2., 3.) + 5.0;

        EXPECT_FLOAT_EQ(v.getX(), 6.0);
        EXPECT_FLOAT_EQ(v.getY(), 7.0);
        EXPECT_FLOAT_EQ(v.getZ(), 8.0);
    }
}

TEST(TestVector3f, subScalarOperator)
{
    {
        Vector3f v = Vector3f(1., 2., 3.);
        v -= 5.0;

        EXPECT_FLOAT_EQ(v.getX(), -4.0);
        EXPECT_FLOAT_EQ(v.getY(), -3.0);
        EXPECT_FLOAT_EQ(v.getZ(), -2.0);
    }

    {
        const Vector3f v = Vector3f(1., 2., 3.) - 5.0;

        EXPECT_FLOAT_EQ(v.getX(), -4.0);
        EXPECT_FLOAT_EQ(v.getY(), -3.0);
        EXPECT_FLOAT_EQ(v.getZ(), -2.0);
    }
}

TEST(TestVector3f, mulScalarOperator)
{

    {
        Vector3f v = Vector3f(1., 2., 3.);
        v *= 1.0;

        EXPECT_FLOAT_EQ(v.getX(), 1.0);
        EXPECT_FLOAT_EQ(v.getY(), 2.0);
        EXPECT_FLOAT_EQ(v.getZ(), 3.0);
    }

    {
        const Vector3f v = Vector3f(1., 2., 3.) * 1.0;

        EXPECT_FLOAT_EQ(v.getX(), 1.0);
        EXPECT_FLOAT_EQ(v.getY(), 2.0);
        EXPECT_FLOAT_EQ(v.getZ(), 3.0);
    }

    {
        Vector3f v = Vector3f(1., 2., 3.);
        v *= 10.0;

        EXPECT_FLOAT_EQ(v.getX(), 10.0);
        EXPECT_FLOAT_EQ(v.getY(), 20.0);
        EXPECT_FLOAT_EQ(v.getZ(), 30.0);
    }

    {
        const Vector3f v = Vector3f(1., 2., 3.) * 10.0;

        EXPECT_FLOAT_EQ(v.getX(), 10.0);
        EXPECT_FLOAT_EQ(v.getY(), 20.0);
        EXPECT_FLOAT_EQ(v.getZ(), 30.0);
    }
}

TEST(TestVector3f, divScalarOperator)
{

    {
        Vector3f v = Vector3f(1., 2., 3.);
        v /= 1.0;

        EXPECT_FLOAT_EQ(v.getX(), 1.0);
        EXPECT_FLOAT_EQ(v.getY(), 2.0);
        EXPECT_FLOAT_EQ(v.getZ(), 3.0);
    }

    {
        const Vector3f v = Vector3f(1., 2., 3.) / 1.0;

        EXPECT_FLOAT_EQ(v.getX(), 1.0);
        EXPECT_FLOAT_EQ(v.getY(), 2.0);
        EXPECT_FLOAT_EQ(v.getZ(), 3.0);
    }

    {
        Vector3f v = Vector3f(1., 2., 3.);
        v /= 10.0;

        EXPECT_FLOAT_EQ(v.getX(), 0.1);
        EXPECT_FLOAT_EQ(v.getY(), 0.2);
        EXPECT_FLOAT_EQ(v.getZ(), 0.3);
    }

    {
        const Vector3f v = Vector3f(1., 2., 3.) / 10.0;

        EXPECT_FLOAT_EQ(v.getX(), 0.1);
        EXPECT_FLOAT_EQ(v.getY(), 0.2);
        EXPECT_FLOAT_EQ(v.getZ(), 0.3);
    }
}

TEST(TestVector3f, cmpOperator)
{
    {
        const Vector3f v1 = Vector3f::unitX();
        const Vector3f v2 = Vector3f::unitZ();
        EXPECT_TRUE(v1 == v1);
        EXPECT_FALSE(v1 == v2);
        EXPECT_FALSE(v1 != v1);
        EXPECT_TRUE(v1 != v2);
    }

    constexpr float FloatEpsilonHalf = 0.5 * FloatEpsilon;
    constexpr float FloatEpsilon2 = 2.0 * FloatEpsilon;

    {
        const Vector3f v1(1.0, 2.0, 3.0);
        const Vector3f v2(1.0 - FloatEpsilonHalf, 2.0 - FloatEpsilonHalf, 3.0 - FloatEpsilonHalf);

        EXPECT_TRUE(v1 == v2);
        EXPECT_FALSE(v1 != v2);
    }

    {
        const Vector3f v1(1.0, 2.0, 3.0);
        const Vector3f v2(1.0 - FloatEpsilon2, 2.0 - FloatEpsilon2, 3.0 - FloatEpsilon2);

        EXPECT_TRUE(v1 != v2);
        EXPECT_FALSE(v1 == v2);
    }
}

TEST(TestVector3f, negateOperator)
{
    // all positive
    {
        const Vector3f v = -Vector3f(1., 2., 3.);

        EXPECT_FLOAT_EQ(v.getX(), -1.);
        EXPECT_FLOAT_EQ(v.getY(), -2.);
        EXPECT_FLOAT_EQ(v.getZ(), -3.);
    }

    // all negative
    {
        const Vector3f v = -Vector3f(-1., -2., -3.);

        EXPECT_FLOAT_EQ(v.getX(), 1.);
        EXPECT_FLOAT_EQ(v.getY(), 2.);
        EXPECT_FLOAT_EQ(v.getZ(), 3.);
    }

    // all randome values
    {
        const Vector3f v = -Vector3f(-1.25, 14.04, 45.0);

        EXPECT_FLOAT_EQ(v.getX(), 1.25);
        EXPECT_FLOAT_EQ(v.getY(), -14.04);
        EXPECT_FLOAT_EQ(v.getZ(), -45.0);
    }
}

TEST(TestVector3f, dot)
{
    {
        const Vector3f v1 = Vector3f::unitX();
        const Vector3f v2 = Vector3f::unitY();
        EXPECT_FLOAT_EQ(Vector3f::dot(v1, v2), 0.0);
    }

    {
        const Vector3f v1 = Vector3f::unitY();
        const Vector3f v2 = Vector3f::unitZ();
        EXPECT_FLOAT_EQ(Vector3f::dot(v1, v2), 0.0);
    }

    {
        const Vector3f v1 = Vector3f::unitX();
        const Vector3f v2 = Vector3f::unitZ();
        EXPECT_FLOAT_EQ(Vector3f::dot(v1, v2), 0.0);
    }

    {
        const Vector3f v1 = Vector3f::unitZ();
        const Vector3f v2 = Vector3f::unitX();
        EXPECT_FLOAT_EQ(Vector3f::dot(v1, v2), 0.0);
    }

    {
        const Vector3f v1 = Vector3f::unitX();
        EXPECT_FLOAT_EQ(Vector3f::dot(v1, v1), 1.0);
    }

    {
        const Vector3f v1 = Vector3f::unitY();
        EXPECT_FLOAT_EQ(Vector3f::dot(v1, v1), 1.0);
    }

    {
        const Vector3f v1 = Vector3f::unitZ();
        EXPECT_FLOAT_EQ(Vector3f::dot(v1, v1), 1.0);
    }

    {
        const Vector3f v1(1.0, 2.0, 3.0);
        const Vector3f v2(5.0, 6.0, 7.0);

        // 1*5 + 2*6 + 3*7 =
        // 5 + 12 + 21 = 38
        EXPECT_FLOAT_EQ(Vector3f::dot(v1, v2), 38.0);
    }

    {
        const Vector3f v1(1.0, -2.0, 3.0);
        const Vector3f v2(-5.0, 6.0, -7.0);

        // 1*-5 + -2*6 + 3*-7 =
        // -5 + -12 + -21 = -38
        EXPECT_FLOAT_EQ(Vector3f::dot(v1, v2), -38.0);
    }

    {
        const Vector3f zero(0.0, 0.0, 0.0);
        const Vector3f v(1.0, 2.0, 3.0);

        EXPECT_FLOAT_EQ(Vector3f::dot(zero, v), 0.0);
    }

    {
        const Vector3f v1(4.0, -2.0, 6.0);
        const Vector3f v2(5.0, 2.0, 3.0);
        // 4*5 + -2*2 + 6*3 =
        // 20 + -4 + 18 = 39
        EXPECT_FLOAT_EQ(Vector3f::dot(v1, v2), 34);
        EXPECT_FLOAT_EQ(Vector3f::dot(v2, v1), 34);
    }
}

TEST(TestVector3f, cross)
{
    // Cross self
    {
        const Vector3f x = Vector3f::unitX();
        const Vector3f result = Vector3f::cross(x, x);
        EXPECT_FLOAT_EQ(result.getX(), 0.0);
        EXPECT_FLOAT_EQ(result.getY(), 0.0);
        EXPECT_FLOAT_EQ(result.getZ(), 0.0);
    }

    // Check cross product magnitude
    {
        const Vector3f a(3.0, 0.0, 0.0);
        const Vector3f b(0.0, 4.0, 0.0);

        const Vector3f result = Vector3f::cross(a, b);

        // a cross b = (0, 0, 12)
        EXPECT_FLOAT_EQ(result.getX(), 0.0);
        EXPECT_FLOAT_EQ(result.getY(), 0.0);
        EXPECT_FLOAT_EQ(result.getZ(), 12.0);

        EXPECT_FLOAT_EQ(result.length(), a.length() * b.length());
    }

    // x cross y = z , y cross x = -z
    {
        const Vector3f x = Vector3f::unitX();
        const Vector3f y = Vector3f::unitY();

        const Vector3f z = Vector3f::cross(x, y);
        const Vector3f minusZ = Vector3f::cross(y, x);

        EXPECT_FLOAT_EQ(z.getX(), 0.0);
        EXPECT_FLOAT_EQ(z.getY(), 0.0);
        EXPECT_FLOAT_EQ(z.getZ(), 1.0);

        EXPECT_FLOAT_EQ(minusZ.getX(), 0.0);
        EXPECT_FLOAT_EQ(minusZ.getY(), 0.0);
        EXPECT_FLOAT_EQ(minusZ.getZ(), -1.0);
    }

    // x cross z = -y, z cross x = y
    {
        const Vector3f x = Vector3f::unitX();
        const Vector3f z = Vector3f::unitZ();

        const Vector3f minusY = Vector3f::cross(x, z);
        const Vector3f y = Vector3f::cross(z, x);

        EXPECT_FLOAT_EQ(minusY.getX(), 0.0);
        EXPECT_FLOAT_EQ(minusY.getY(), -1.0);
        EXPECT_FLOAT_EQ(minusY.getZ(), 0.0);

        EXPECT_FLOAT_EQ(y.getX(), 0.0);
        EXPECT_FLOAT_EQ(y.getY(), 1.0);
        EXPECT_FLOAT_EQ(y.getZ(), 0.0);
    }

    // y cross z = x, z cross y = -x
    {
        const Vector3f y = Vector3f::unitY();
        const Vector3f z = Vector3f::unitZ();

        const Vector3f x = Vector3f::cross(y, z);
        const Vector3f minusX = Vector3f::cross(z, y);

        EXPECT_FLOAT_EQ(x.getX(), 1.0);
        EXPECT_FLOAT_EQ(x.getY(), 0.0);
        EXPECT_FLOAT_EQ(x.getZ(), 0.0);

        EXPECT_FLOAT_EQ(minusX.getX(), -1.0);
        EXPECT_FLOAT_EQ(minusX.getY(), 0.0);
        EXPECT_FLOAT_EQ(minusX.getZ(), 0.0);
    }
    // random
    {
        const Vector3f a = Vector3f(3.0, -2.0, 5.0);
        const Vector3f b = Vector3f(-1.0, 4.0, 2.0);

        const Vector3f result = Vector3f::cross(a, b);
        EXPECT_FLOAT_EQ(result.getX(), -24.0);
        EXPECT_FLOAT_EQ(result.getY(), -11.0);
        EXPECT_FLOAT_EQ(result.getZ(), 10.0);
    }
}

TEST(TestVector3f, mix)
{
    {
        const Vector3f a(1.0, 2.0, 3.0);
        const Vector3f b(4.0, 5.0, 6.0);
        const Vector3f c(7.0, 8.0, 10.0);

        const float result = Vector3f::mix(a, b, c);

        EXPECT_FLOAT_EQ(result, -3.0);
    }
}

TEST(TestVector3f, lengthSquare)
{
    // unit vector lengthSquare by definition is 1
    {
        const Vector3f v1 = Vector3f::unitX();
        EXPECT_FLOAT_EQ(v1.lengthSquare(), 1.0);

        const Vector3f v2 = Vector3f::unitY();
        EXPECT_FLOAT_EQ(v2.lengthSquare(), 1.0);

        const Vector3f v3 = Vector3f::unitZ();
        EXPECT_FLOAT_EQ(v3.lengthSquare(), 1.0);
    }
    {
        const Vector3f v1 = Vector3f(-1.0, 0.0, 0.0);
        EXPECT_FLOAT_EQ(v1.lengthSquare(), 1.0);
    }

    {
        const Vector3f v1 = Vector3f(-1.0, -2.0, 4.0);
        EXPECT_FLOAT_EQ(v1.lengthSquare(), 21.0);
    }
}

TEST(TestVector3f, length)
{
    // Unit vector length by definition is 1
    {
        const Vector3f v1 = Vector3f::unitX();
        EXPECT_FLOAT_EQ(v1.length(), 1.0);

        const Vector3f v2 = Vector3f::unitY();
        EXPECT_FLOAT_EQ(v2.length(), 1.0);

        const Vector3f v3 = Vector3f::unitZ();
        EXPECT_FLOAT_EQ(v3.length(), 1.0);
    }

    // Arbitrary vector
    {
        const Vector3f v1(-1.0, -2.0, 4.0);

        EXPECT_FLOAT_EQ(v1.length(), std::sqrt(21.0));
        EXPECT_FLOAT_EQ(v1.length(), std::sqrt(v1.lengthSquare()));
    }

    // Negative component
    {
        const Vector3f v1(-1.0, 0.0, 0.0);

        EXPECT_FLOAT_EQ(v1.length(), 1.0);
    }
}

TEST(TestVector3f, distanceSquare)
{
    // Unit vector
    {
        const Vector3f v1 = Vector3f::unitX();
        const Vector3f v2 = Vector3f::unitX();

        EXPECT_FLOAT_EQ(Vector3f::distanceSquare(v1, v2), 0.0);
    }

    // Same arbitrary vector
    {
        const Vector3f v1(10.0, 20.0, -12.0);
        const Vector3f v2(10.0, 20.0, -12.0);

        EXPECT_FLOAT_EQ(Vector3f::distanceSquare(v1, v2), 0.0);
    }

    // Difference only on X
    {
        const Vector3f v1(1.0, 2.0, 3.0);
        const Vector3f v2(4.0, 2.0, 3.0);

        EXPECT_FLOAT_EQ(Vector3f::distanceSquare(v1, v2), 9.0);
    }

    // Difference only on Y
    {
        const Vector3f v1(1.0, 2.0, 3.0);
        const Vector3f v2(1.0, 6.0, 3.0);

        EXPECT_FLOAT_EQ(Vector3f::distanceSquare(v1, v2), 16.0);
    }

    // Difference only on Z
    {
        const Vector3f v1(1.0, 2.0, 3.0);
        const Vector3f v2(1.0, 2.0, 8.0);

        EXPECT_FLOAT_EQ(Vector3f::distanceSquare(v1, v2), 25.0);
    }

    // Difference on every component
    {
        const Vector3f v1(-1.0, -2.0, 4.0);
        const Vector3f v2(1.0, 2.0, 0.0);

        // (-2)^2 + (-4)^2 + 4^2
        // = 4 + 16 + 16
        // = 36
        EXPECT_FLOAT_EQ(Vector3f::distanceSquare(v1, v2), 36.0);
    }

    // Negative and positive values
    {
        const Vector3f v1(-1.0, -2.0, -3.0);
        const Vector3f v2(1.0, 2.0, 3.0);

        // (-2)^2 + (-4)^2 + (-6)^2
        // = 4 + 16 + 36
        // = 56
        EXPECT_FLOAT_EQ(Vector3f::distanceSquare(v1, v2), 56.0);
    }

    // Symmetry
    {
        const Vector3f v1(2.0, -3.0, 5.0);
        const Vector3f v2(-4.0, 8.0, 1.0);

        EXPECT_FLOAT_EQ(Vector3f::distanceSquare(v1, v2), Vector3f::distanceSquare(v2, v1));
    }

    // distanceSquare(a, b) == (a - b).lengthSquare()
    {
        const Vector3f v1(-4.0, 7.0, 2.0);
        const Vector3f v2(3.0, -2.0, 6.0);

        const Vector3f difference = v1 - v2;

        EXPECT_FLOAT_EQ(Vector3f::distanceSquare(v1, v2), difference.lengthSquare());
    }
}

TEST(TestVector3f, distance)
{
    // Unit vector
    {
        const Vector3f v1 = Vector3f::unitX();
        const Vector3f v2 = Vector3f::unitX();

        EXPECT_FLOAT_EQ(Vector3f::distance(v1, v2), 0.0);
    }

    // Same arbitrary vector
    {
        const Vector3f v1(10.0, 20.0, -12.0);
        const Vector3f v2(10.0, 20.0, -12.0);

        EXPECT_FLOAT_EQ(Vector3f::distance(v1, v2), 0.0);
    }

    // Difference only on X
    {
        const Vector3f v1(1.0, 2.0, 3.0);
        const Vector3f v2(4.0, 2.0, 3.0);

        EXPECT_FLOAT_EQ(Vector3f::distance(v1, v2), 3.0);
    }

    // Difference only on Y
    {
        const Vector3f v1(1.0, 2.0, 3.0);
        const Vector3f v2(1.0, 6.0, 3.0);

        EXPECT_FLOAT_EQ(Vector3f::distance(v1, v2), 4.0);
    }

    // Difference only on Z
    {
        const Vector3f v1(1.0, 2.0, 3.0);
        const Vector3f v2(1.0, 2.0, 8.0);

        EXPECT_FLOAT_EQ(Vector3f::distance(v1, v2), 5.0);
    }

    // Difference on every component
    {
        const Vector3f v1(-1.0, -2.0, 4.0);
        const Vector3f v2(1.0, 2.0, 0.0);

        // (-2)^2 + (-4)^2 + 4^2
        // = 4 + 16 + 16
        // = 36
        EXPECT_FLOAT_EQ(Vector3f::distance(v1, v2), 6.0);
    }

    // Negative and positive values
    {
        const Vector3f v1(-1.0, -2.0, -3.0);
        const Vector3f v2(1.0, 2.0, 3.0);

        // (-2)^2 + (-4)^2 + (-6)^2
        // = 4 + 16 + 36
        // = 56
        EXPECT_FLOAT_EQ(Vector3f::distance(v1, v2), std::sqrt(56.0));
    }

    // Symmetry
    {
        const Vector3f v1(2.0, -3.0, 5.0);
        const Vector3f v2(-4.0, 8.0, 1.0);

        EXPECT_FLOAT_EQ(Vector3f::distance(v1, v2), Vector3f::distance(v2, v1));
    }

    // distance(a, b) == (a - b).length()
    {
        const Vector3f v1(-4.0, 7.0, 2.0);
        const Vector3f v2(3.0, -2.0, 6.0);

        const Vector3f difference = v1 - v2;

        EXPECT_FLOAT_EQ(Vector3f::distance(v1, v2), difference.length());
    }

    // distance(a, b)^2 == distanceSquare(a, b)
    {
        const Vector3f v1(2.0, -5.0, 7.0);
        const Vector3f v2(-3.0, 1.0, 4.0);

        const float distance = Vector3f::distance(v1, v2);

        EXPECT_FLOAT_EQ(distance * distance, Vector3f::distanceSquare(v1, v2));
    }
}

TEST(TestVector3f, getNormalize)
{
    {
        const Vector3f v(3.0, 4.0, 0.0);
        const Vector3f normalized = v.getNormalize();

        EXPECT_NEAR(normalized.getX(), 0.6, FloatEpsilon);
        EXPECT_NEAR(normalized.getY(), 0.8, FloatEpsilon);
        EXPECT_NEAR(normalized.getZ(), 0.0, FloatEpsilon);

        EXPECT_NEAR(normalized.length(), 1.0, FloatEpsilon);

        // getNormalize() must not modify the original vector.
        EXPECT_FLOAT_EQ(v.getX(), 3.0);
        EXPECT_FLOAT_EQ(v.getY(), 4.0);
        EXPECT_FLOAT_EQ(v.getZ(), 0.0);
    }

    {
        const Vector3f v(-1.0, -2.0, 4.0);
        const Vector3f normalized = v.getNormalize();

        EXPECT_NEAR(normalized.length(), 1.0, FloatEpsilon);
    }

    // Already normalized.
    {
        const Vector3f v = Vector3f::unitX();
        const Vector3f normalized = v.getNormalize();

        EXPECT_NEAR(normalized.length(), 1.0, FloatEpsilon);
        EXPECT_NEAR(normalized.getX(), 1.0, FloatEpsilon);
        EXPECT_NEAR(normalized.getY(), 0.0, FloatEpsilon);
        EXPECT_NEAR(normalized.getZ(), 0.0, FloatEpsilon);
    }

    // Zero vector.
    {
        const Vector3f v(0.0, 0.0, 0.0);
        const Vector3f normalized = v.getNormalize();

        EXPECT_FLOAT_EQ(normalized.getX(), 0.0);
        EXPECT_FLOAT_EQ(normalized.getY(), 0.0);
        EXPECT_FLOAT_EQ(normalized.getZ(), 0.0);
    }
}

TEST(TestVector3f, normalize)
{
    {
        Vector3f v(3.0, 4.0, 0.0);

        v.normalize();

        EXPECT_NEAR(v.getX(), 0.6, FloatEpsilon);
        EXPECT_NEAR(v.getY(), 0.8, FloatEpsilon);
        EXPECT_NEAR(v.getZ(), 0.0, FloatEpsilon);

        EXPECT_NEAR(v.length(), 1.0, FloatEpsilon);
    }

    {
        Vector3f v(-1.0, -2.0, 4.0);

        v.normalize();

        EXPECT_NEAR(v.length(), 1.0, FloatEpsilon);
    }

    // Already normalized.
    {
        Vector3f v = Vector3f::unitX();

        v.normalize();

        EXPECT_NEAR(v.length(), 1.0, FloatEpsilon);
        EXPECT_NEAR(v.getX(), 1.0, FloatEpsilon);
        EXPECT_NEAR(v.getY(), 0.0, FloatEpsilon);
        EXPECT_NEAR(v.getZ(), 0.0, FloatEpsilon);
    }

    // Zero vector should remain zero.
    {
        Vector3f v(0.0, 0.0, 0.0);

        v.normalize();

        EXPECT_FLOAT_EQ(v.getX(), 0.0);
        EXPECT_FLOAT_EQ(v.getY(), 0.0);
        EXPECT_FLOAT_EQ(v.getZ(), 0.0);
    }

    // normalize() should return *this.
    {
        Vector3f v(3.0, 4.0, 0.0);

        const Vector3f& result = v.normalize();

        EXPECT_EQ(&result, &v);
    }
}

TEST(TestVector3f, getNormalizeFast)
{
    {
        const Vector3f v(3.0, 4.0, 0.0);
        const Vector3f normalized = v.getNormalizeFast();

        EXPECT_NEAR(normalized.getX(), 0.6, FloatEpsilon);
        EXPECT_NEAR(normalized.getY(), 0.8, FloatEpsilon);
        EXPECT_NEAR(normalized.getZ(), 0.0, FloatEpsilon);

        EXPECT_NEAR(normalized.length(), 1.0, FloatEpsilon);

        // getNormalizeFast() must not modify the original vector.
        EXPECT_FLOAT_EQ(v.getX(), 3.0);
        EXPECT_FLOAT_EQ(v.getY(), 4.0);
        EXPECT_FLOAT_EQ(v.getZ(), 0.0);
    }

    {
        const Vector3f v(-1.0, -2.0, 4.0);
        const Vector3f normalized = v.getNormalizeFast();

        EXPECT_NEAR(normalized.length(), 1.0, FloatEpsilon);
    }

    // Already normalized.
    {
        const Vector3f v = Vector3f::unitX();
        const Vector3f normalized = v.getNormalizeFast();

        EXPECT_NEAR(normalized.length(), 1.0, FloatEpsilon);
        EXPECT_NEAR(normalized.getX(), 1.0, FloatEpsilon);
        EXPECT_NEAR(normalized.getY(), 0.0, FloatEpsilon);
        EXPECT_NEAR(normalized.getZ(), 0.0, FloatEpsilon);
    }

    // Zero vector.
    {
        const Vector3f v(0.0, 0.0, 0.0);
        const Vector3f normalized = v.getNormalizeFast();

        EXPECT_FLOAT_EQ(normalized.getX(), 0.0);
        EXPECT_FLOAT_EQ(normalized.getY(), 0.0);
        EXPECT_FLOAT_EQ(normalized.getZ(), 0.0);
    }
}

TEST(TestVector3f, normalizeFast)
{
    {
        Vector3f v(3.0, 4.0, 0.0);

        v.normalizeFast();

        EXPECT_NEAR(v.getX(), 0.6, FloatEpsilon);
        EXPECT_NEAR(v.getY(), 0.8, FloatEpsilon);
        EXPECT_NEAR(v.getZ(), 0.0, FloatEpsilon);

        EXPECT_NEAR(v.length(), 1.0, FloatEpsilon);
    }

    {
        Vector3f v(-1.0, -2.0, 4.0);

        v.normalizeFast();

        EXPECT_NEAR(v.length(), 1.0, FloatEpsilon);
    }

    // Already normalized.
    {
        Vector3f v = Vector3f::unitX();

        v.normalizeFast();

        EXPECT_NEAR(v.length(), 1.0, FloatEpsilon);
        EXPECT_NEAR(v.getX(), 1.0, FloatEpsilon);
        EXPECT_NEAR(v.getY(), 0.0, FloatEpsilon);
        EXPECT_NEAR(v.getZ(), 0.0, FloatEpsilon);
    }

    // Zero vector should remain zero.
    {
        Vector3f v(0.0, 0.0, 0.0);

        v.normalizeFast();

        EXPECT_FLOAT_EQ(v.getX(), 0.0);
        EXPECT_FLOAT_EQ(v.getY(), 0.0);
        EXPECT_FLOAT_EQ(v.getZ(), 0.0);
    }

    // normalizeFast() should return *this.
    {
        Vector3f v(3.0, 4.0, 0.0);

        const Vector3f& result = v.normalizeFast();

        EXPECT_EQ(&result, &v);
    }
}

TEST(TestVector3f, min)
{
    {
        const Vector3f v0(1.0, 2.0, 3.0);
        const Vector3f v1(5.0, 6.0, 7.0);

        const Vector3f result = Vector3f::min(v0, v1);

        EXPECT_FLOAT_EQ(result.getX(), 1.0);
        EXPECT_FLOAT_EQ(result.getY(), 2.0);
        EXPECT_FLOAT_EQ(result.getZ(), 3.0);
    }

    { // Minimum comes from different vectors
        const Vector3f v0(8.0, -4.0, 15.0);
        const Vector3f v1(2.0, 12.0, -3.0);

        const Vector3f result = Vector3f::min(v0, v1);

        EXPECT_FLOAT_EQ(result.getX(), 2.0);
        EXPECT_FLOAT_EQ(result.getY(), -4.0);
        EXPECT_FLOAT_EQ(result.getZ(), -3.0);
    }

    { // Equal components
        const Vector3f v0(5.0, 3.0, -2.0);
        const Vector3f v1(5.0, 3.0, -2.0);

        const Vector3f result = Vector3f::min(v0, v1);

        EXPECT_FLOAT_EQ(result.getX(), 5.0);
        EXPECT_FLOAT_EQ(result.getY(), 3.0);
        EXPECT_FLOAT_EQ(result.getZ(), -2.0);
    }
}

TEST(TestVector3fd, max)
{
    {
        const Vector3f v0(1.0, 2.0, 3.0);
        const Vector3f v1(5.0, 6.0, 7.0);

        const Vector3f result = Vector3f::max(v0, v1);

        EXPECT_FLOAT_EQ(result.getX(), 5.0);
        EXPECT_FLOAT_EQ(result.getY(), 6.0);
        EXPECT_FLOAT_EQ(result.getZ(), 7.0);
    }

    { // Maximum comes from different vectors
        const Vector3f v0(8.0, -4.0, 15.0);
        const Vector3f v1(2.0, 12.0, -3.0);

        const Vector3f result = Vector3f::max(v0, v1);

        EXPECT_FLOAT_EQ(result.getX(), 8.0);
        EXPECT_FLOAT_EQ(result.getY(), 12.0);
        EXPECT_FLOAT_EQ(result.getZ(), 15.0);
    }

    { // Equal components
        const Vector3f v0(5.0, 3.0, -2.0);
        const Vector3f v1(5.0, 3.0, -2.0);

        const Vector3f result = Vector3f::max(v0, v1);

        EXPECT_FLOAT_EQ(result.getX(), 5.0);
        EXPECT_FLOAT_EQ(result.getY(), 3.0);
        EXPECT_FLOAT_EQ(result.getZ(), -2.0);
    }
}

TEST(TestVector3f, IsFinite)
{
    {
        const Vector3f v = Vector3f(1., 2., 3.);
        EXPECT_TRUE(v.isFinite());
    }
#if !defined(NDEBUG)
    EXPECT_DEATH(
        {
            const Vector3f v(NAN, 2.0, 3.0);
            (void)v;
        },
        ".*");

    EXPECT_DEATH(
        {
            const Vector3f v(0.0, INFINITY, 3.0);
            (void)v;
        },
        ".*");
#else
    {
        const Vector3f v = Vector3f(NAN, 2.0, 3.0);
        EXPECT_FALSE(v.isFinite());
    }

    {
        const Vector3f v = Vector3f(0.0, INFINITY, 3.0);
        EXPECT_FALSE(v.isFinite());
    }
#endif
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
