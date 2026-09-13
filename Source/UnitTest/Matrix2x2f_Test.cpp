#include <gtest/gtest.h>

#include <numbers>

#include <MathLibHeader.hpp>
#include <MatrixTransformation.hpp>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

using namespace MathLib;

TEST(TestMatrixd2x2f, constructor)
{
    {
        const Matrix2x2f m(1.0, 2.0, 3.0, 4.0);
        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 2.0);

        EXPECT_FLOAT_EQ(m.getM21(), 3.0);
        EXPECT_FLOAT_EQ(m.getM22(), 4.0);
    }

    {
        const Matrix2x2f m(Vector2f(1.0, 2.0), Vector2f(3.0, 4.0));
        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 2.0);

        EXPECT_FLOAT_EQ(m.getM21(), 3.0);
        EXPECT_FLOAT_EQ(m.getM22(), 4.0);
    }
}

TEST(TestMatrixd2x2f, identity)
{
    const Matrix2x2f m = Matrix2x2f::identity();
    EXPECT_FLOAT_EQ(m.getM11(), 1.0);
    EXPECT_FLOAT_EQ(m.getM12(), 0.0);

    EXPECT_FLOAT_EQ(m.getM21(), 0.0);
    EXPECT_FLOAT_EQ(m.getM22(), 1.0);
}

TEST(TestMatrixd2x2f, setter)
{
    Matrix2x2f m = Matrix2x2f::zero();
    m.setM11(1.0) //
        .setM12(2.0)
        .setM21(3.0)
        .setM22(4.0);
    EXPECT_FLOAT_EQ(m.getM11(), 1.0);
    EXPECT_FLOAT_EQ(m.getM12(), 2.0);

    EXPECT_FLOAT_EQ(m.getM21(), 3.0);
    EXPECT_FLOAT_EQ(m.getM22(), 4.0);
}

TEST(TestMatrixd2x2f, transpose)
{
    // transpose dont change diagonal
    {
        const Matrix2x2f m = Matrix2x2f::identity().transpose();
        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 0.0);

        EXPECT_FLOAT_EQ(m.getM21(), 0.0);
        EXPECT_FLOAT_EQ(m.getM22(), 1.0);
    }

    // transpose change order element who are dont in the diagonal
    {
        const Matrix2x2f m = Matrix2x2f(1.0, 2.0, 3.0, 4.0).transpose();
        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 3.0);

        EXPECT_FLOAT_EQ(m.getM21(), 2.0);
        EXPECT_FLOAT_EQ(m.getM22(), 4.0);
    }
}

TEST(TestMatrixd2x2f, getTranspose)
{
    // transpose dont change diagonal
    {
        const Matrix2x2f m = Matrix2x2f::identity().getTranspose();
        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 0.0);

        EXPECT_FLOAT_EQ(m.getM21(), 0.0);
        EXPECT_FLOAT_EQ(m.getM22(), 1.0);
    }

    // transpose change order element who are dont in the diagonal
    {
        const Matrix2x2f m = Matrix2x2f(1.0, 2.0, 3.0, 4.0).getTranspose();
        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 3.0);

        EXPECT_FLOAT_EQ(m.getM21(), 2.0);
        EXPECT_FLOAT_EQ(m.getM22(), 4.0);
    }
}

TEST(TestMatrixd2x2f, determinant)
{
    // determiant of identity => 1.0
    {
        const float value = Matrix2x2f::identity().determinant();
        EXPECT_FLOAT_EQ(value, 1.0);
    }

    // determiant of identity => 1.0
    {
        const Matrix2x2f m = Matrix2x2f(Vector2f::zero(), Vector2f::zero());
        EXPECT_FLOAT_EQ(m.determinant(), 0.0);
    }

    // determinant of non-trivial matrix => 1.0
    {
        const Matrix2x2f m(Vector2f(2.0, 3.0), Vector2f(1.0, 2.0));

        EXPECT_FLOAT_EQ(m.determinant(), 1.0);
    }

    // determinant of non-trivial matrix
    {
        const Matrix2x2f m(Vector2f(7.0, -3.0), Vector2f(4.0, 5.0));

        EXPECT_FLOAT_EQ(m.determinant(), 47.0);
    }
}

TEST(TestMatrixd2x2f, inverse)
{
    // Inverse of identity => identity
    {
        const Matrix2x2f m = Matrix2x2f(Vector2f(1.0, 0.0), Vector2f(0.0, 1.0)).inverse();
        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 0.0);
        EXPECT_FLOAT_EQ(m.getM21(), 0.0);
        EXPECT_FLOAT_EQ(m.getM22(), 1.0);
    }

    // Inverse of arbitrary matrix
    {
        const Matrix2x2f m = Matrix2x2f(Vector2f(4.0, 7.0), Vector2f(2.0, 6.0)).inverse();

        EXPECT_FLOAT_EQ(m.getM11(), 0.6);
        EXPECT_FLOAT_EQ(m.getM12(), -0.7);
        EXPECT_FLOAT_EQ(m.getM21(), -0.2);
        EXPECT_FLOAT_EQ(m.getM22(), 0.4);
    }
}

TEST(TestMatrixd2x2f, getInverse)
{
    // Inverse of identity => identity
    {
        const Matrix2x2f m = Matrix2x2f(Vector2f(1.0, 0.0), Vector2f(0.0, 1.0)).getInverse();
        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 0.0);
        EXPECT_FLOAT_EQ(m.getM21(), 0.0);
        EXPECT_FLOAT_EQ(m.getM22(), 1.0);
    }

    // Inverse of arbitrary matrix
    {
        const Matrix2x2f m = Matrix2x2f(Vector2f(4.0, 7.0), Vector2f(2.0, 6.0)).getInverse();

        EXPECT_FLOAT_EQ(m.getM11(), 0.6);
        EXPECT_FLOAT_EQ(m.getM12(), -0.7);
        EXPECT_FLOAT_EQ(m.getM21(), -0.2);
        EXPECT_FLOAT_EQ(m.getM22(), 0.4);
    }
}

TEST(TestMatrixd2x2f, addScalarOperator)
{
    {
        Matrix2x2f m(1.0, 2.0, 3.0, 4.0);
        m += 10.0;
        EXPECT_FLOAT_EQ(m.getM11(), 11.0);
        EXPECT_FLOAT_EQ(m.getM12(), 12.0);

        EXPECT_FLOAT_EQ(m.getM21(), 13.0);
        EXPECT_FLOAT_EQ(m.getM22(), 14.0);
    }

    {
        const Matrix2x2f m = Matrix2x2f(1.0, 2.0, 3.0, 4.0) + 10.0;
        EXPECT_FLOAT_EQ(m.getM11(), 11.0);
        EXPECT_FLOAT_EQ(m.getM12(), 12.0);

        EXPECT_FLOAT_EQ(m.getM21(), 13.0);
        EXPECT_FLOAT_EQ(m.getM22(), 14.0);
    }
}

TEST(TestMatrixd2x2f, subScalarOperator)
{
    {
        Matrix2x2f m(1.0, 2.0, 3.0, 4.0);
        m -= 10.0;
        EXPECT_FLOAT_EQ(m.getM11(), -9.0);
        EXPECT_FLOAT_EQ(m.getM12(), -8.0);

        EXPECT_FLOAT_EQ(m.getM21(), -7.0);
        EXPECT_FLOAT_EQ(m.getM22(), -6.0);
    }

    {
        const Matrix2x2f m = Matrix2x2f(1.0, 2.0, 3.0, 4.0) - 10.0;
        EXPECT_FLOAT_EQ(m.getM11(), -9.0);
        EXPECT_FLOAT_EQ(m.getM12(), -8.0);

        EXPECT_FLOAT_EQ(m.getM21(), -7.0);
        EXPECT_FLOAT_EQ(m.getM22(), -6.0);
    }
}

TEST(TestMatrixd2x2f, mulScalarOperator)
{
    {
        Matrix2x2f m(1.0, 2.0, 3.0, 4.0);
        m *= 10.0;
        EXPECT_FLOAT_EQ(m.getM11(), 10.0);
        EXPECT_FLOAT_EQ(m.getM12(), 20.0);

        EXPECT_FLOAT_EQ(m.getM21(), 30.0);
        EXPECT_FLOAT_EQ(m.getM22(), 40.0);
    }

    {
        const Matrix2x2f m = Matrix2x2f(1.0, 2.0, 3.0, 4.0) * 10.0;
        EXPECT_FLOAT_EQ(m.getM11(), 10.0);
        EXPECT_FLOAT_EQ(m.getM12(), 20.0);

        EXPECT_FLOAT_EQ(m.getM21(), 30.0);
        EXPECT_FLOAT_EQ(m.getM22(), 40.0);
    }
}

TEST(TestMatrixd2x2f, divScalarOperator)
{
    {
        Matrix2x2f m(1.0, 2.0, 3.0, 4.0);
        m /= 10.0;
        EXPECT_FLOAT_EQ(m.getM11(), 0.10);
        EXPECT_FLOAT_EQ(m.getM12(), 0.20);

        EXPECT_FLOAT_EQ(m.getM21(), 0.30);
        EXPECT_FLOAT_EQ(m.getM22(), 0.40);
    }

    {
        const Matrix2x2f m = Matrix2x2f(1.0, 2.0, 3.0, 4.0) / 10.0;
        EXPECT_FLOAT_EQ(m.getM11(), 0.10);
        EXPECT_FLOAT_EQ(m.getM12(), 0.20);

        EXPECT_FLOAT_EQ(m.getM21(), 0.30);
        EXPECT_FLOAT_EQ(m.getM22(), 0.40);
    }
}

TEST(TestMatrixd2x2f, addMatrixOperator)
{
    {
        const Matrix2x2f m1(1.0, 2.0, 3.0, 4.0);
        Matrix2x2f m(5.0, 6.0, 7.0, 8.0);
        m += m1;
        EXPECT_FLOAT_EQ(m.getM11(), 6.0);
        EXPECT_FLOAT_EQ(m.getM12(), 8.0);
        EXPECT_FLOAT_EQ(m.getM21(), 10.0);
        EXPECT_FLOAT_EQ(m.getM22(), 12.0);
    }

    {
        const Matrix2x2f m1(1.0, 2.0, 3.0, 4.0);
        const Matrix2x2f m2(5.0, 6.0, 7.0, 8.0);
        const Matrix2x2f m = m1 + m2;
        EXPECT_FLOAT_EQ(m.getM11(), 6.0);
        EXPECT_FLOAT_EQ(m.getM12(), 8.0);
        EXPECT_FLOAT_EQ(m.getM21(), 10.0);
        EXPECT_FLOAT_EQ(m.getM22(), 12.0);
    }
}

TEST(TestMatrixd2x2f, subMatrixOperator)
{
    {
        Matrix2x2f m(1.0, 2.0, 3.0, 4.0);
        const Matrix2x2f m1(5.0, 6.0, 7.0, 8.0);
        m -= m1;
        EXPECT_FLOAT_EQ(m.getM11(), -4.0);
        EXPECT_FLOAT_EQ(m.getM12(), -4.0);
        EXPECT_FLOAT_EQ(m.getM21(), -4.0);
        EXPECT_FLOAT_EQ(m.getM22(), -4.0);
    }

    {
        const Matrix2x2f m1(1.0, 2.0, 3.0, 4.0);
        const Matrix2x2f m2(5.0, 6.0, 7.0, 8.0);
        const Matrix2x2f m = m1 - m2;
        EXPECT_FLOAT_EQ(m.getM11(), -4.0);
        EXPECT_FLOAT_EQ(m.getM12(), -4.0);
        EXPECT_FLOAT_EQ(m.getM21(), -4.0);
        EXPECT_FLOAT_EQ(m.getM22(), -4.0);
    }
}

TEST(TestMatrixd2x2f, mulMatrixOperator)
{
    {
        Matrix2x2f m(1.0, 2.0, 3.0, 4.0);

        const Matrix2x2f m1(5.0, 6.0, 7.0, 8.0);

        m *= m1;

        EXPECT_FLOAT_EQ(m.getM11(), 19.0);
        EXPECT_FLOAT_EQ(m.getM12(), 22.0);
        EXPECT_FLOAT_EQ(m.getM21(), 43.0);
        EXPECT_FLOAT_EQ(m.getM22(), 50.0);
    }

    {
        const Matrix2x2f m1(1.0, 2.0, 3.0, 4.0);

        const Matrix2x2f m2(5.0, 6.0, 7.0, 8.0);

        const Matrix2x2f m = m1 * m2;

        EXPECT_FLOAT_EQ(m.getM11(), 19.0);
        EXPECT_FLOAT_EQ(m.getM12(), 22.0);
        EXPECT_FLOAT_EQ(m.getM21(), 43.0);
        EXPECT_FLOAT_EQ(m.getM22(), 50.0);
    }
}

TEST(TestMatrixd2x2f, cmpOperator)
{
    {
        const Matrix2x2f m1 = Matrix2x2f(1.0, 2.0, 3.0, 4.0);
        const Matrix2x2f m2 = Matrix2x2f::identity();
        EXPECT_TRUE(m1 == m1);
        EXPECT_FALSE(m1 == m2);
        EXPECT_FALSE(m1 != m1);
        EXPECT_TRUE(m1 != m2);
    }

    constexpr float FloatEpsilonHalf = 0.5 * FloatEpsilon;
    constexpr float FloatEpsilon2 = 2.0 * FloatEpsilon;

    {
        const Matrix2x2f m1 = Matrix2x2f(1.0, 2.0, 3.0, 4.0);
        const Matrix2x2f m2 =
            Matrix2x2f(1.0 - FloatEpsilonHalf, 2.0 - FloatEpsilonHalf, 3.0 - FloatEpsilonHalf, 4.0 - FloatEpsilonHalf);

        EXPECT_TRUE(m1 == m2);
        EXPECT_FALSE(m1 != m2);
    }

    {
        const Matrix2x2f m1 = Matrix2x2f(1.0, 2.0, 3.0, 4.0);
        const Matrix2x2f m2 =
            Matrix2x2f(1.0 - FloatEpsilon2, 2.0 - FloatEpsilon2, 3.0 - FloatEpsilon2, 4.0 - FloatEpsilon2);

        EXPECT_TRUE(m1 != m2);
        EXPECT_FALSE(m1 == m2);
    }
}

TEST(TestMatrixd2x2f, rotation)
{
    {
        const float angle = 0.0;
        const Matrix2x2f m = MathLib::rotation(angle);

        EXPECT_NEAR(m.getM11(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(m.getM12(), 0.0, DoubleEpsilon);

        EXPECT_NEAR(m.getM21(), 0.0, DoubleEpsilon);
        EXPECT_NEAR(m.getM22(), 1.0, DoubleEpsilon);
    }

    {
        const float angle = std::numbers::pi;
        const Matrix2x2f m = MathLib::rotation(angle);

        EXPECT_NEAR(m.getM11(), -1.0, DoubleEpsilon);
        EXPECT_NEAR(m.getM12(), 0.0, DoubleEpsilon);

        EXPECT_NEAR(m.getM21(), 0.0, DoubleEpsilon);
        EXPECT_NEAR(m.getM22(), -1.0, DoubleEpsilon);
    }

    {
        const float angle = std::numbers::pi * 0.5;
        const Matrix2x2f m = MathLib::rotation(angle);

        EXPECT_NEAR(m.getM11(), 0.0, DoubleEpsilon);
        EXPECT_NEAR(m.getM12(), -1.0, DoubleEpsilon);

        EXPECT_NEAR(m.getM21(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(m.getM22(), 0.0, DoubleEpsilon);
    }

    {
        const float angle = -std::numbers::pi * 0.5;
        const Matrix2x2f m = MathLib::rotation(angle);

        EXPECT_NEAR(m.getM11(), 0.0, DoubleEpsilon);
        EXPECT_NEAR(m.getM12(), 1.0, DoubleEpsilon);

        EXPECT_NEAR(m.getM21(), -1.0, DoubleEpsilon);
        EXPECT_NEAR(m.getM22(), 0.0, DoubleEpsilon);
    }
}

TEST(TestMatrixd2x2f, scale)
{
    const Vector2f scale(1.0, 2.0);
    {
        const Matrix2x2f m = MathLib::scale(scale.getX(), scale.getY());

        EXPECT_NEAR(m.getM11(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(m.getM12(), 0.0, DoubleEpsilon);

        EXPECT_NEAR(m.getM21(), 0.0, DoubleEpsilon);
        EXPECT_NEAR(m.getM22(), 2.0, DoubleEpsilon);
    }

    {
        const Matrix2x2f m = MathLib::scale(scale);

        EXPECT_NEAR(m.getM11(), 1.0, DoubleEpsilon);
        EXPECT_NEAR(m.getM12(), 0.0, DoubleEpsilon);

        EXPECT_NEAR(m.getM21(), 0.0, DoubleEpsilon);
        EXPECT_NEAR(m.getM22(), 2.0, DoubleEpsilon);
    }
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
