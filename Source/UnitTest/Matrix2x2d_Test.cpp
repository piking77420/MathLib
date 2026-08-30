#include <gtest/gtest.h>

#include <MathLibHeader.hpp>
#include <Matrix2x2.hpp>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

using namespace MathLib;

TEST(TestMatrixd2x2d, constructor)
{
    {
        const Matrix2x2d m(1.0, 2.0, 3.0, 4.0);
        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 2.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 4.0);
    }

    {
        const Matrix2x2d m(Vector2d(1.0, 2.0), Vector2d(3.0, 4.0));
        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 2.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 4.0);
    }
}

TEST(TestMatrixd2x2d, identity)
{
    const Matrix2x2d m = Matrix2x2d::identity();
    EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
    EXPECT_DOUBLE_EQ(m.getM12(), 0.0);

    EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
    EXPECT_DOUBLE_EQ(m.getM22(), 1.0);
}

TEST(TestMatrixd2x2d, setter)
{
    Matrix2x2d m = Matrix2x2d::zero();
    m.setM11(1.0) //
        .setM12(2.0)
        .setM21(3.0)
        .setM22(4.0);
    EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
    EXPECT_DOUBLE_EQ(m.getM12(), 2.0);

    EXPECT_DOUBLE_EQ(m.getM21(), 3.0);
    EXPECT_DOUBLE_EQ(m.getM22(), 4.0);
}

TEST(TestMatrixd2x2d, transpose)
{
    // transpose dont change diagonal
    {
        const Matrix2x2d m = Matrix2x2d::identity().transpose();
        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 1.0);
    }

    // transpose change order element who are dont in the diagonal
    {
        const Matrix2x2d m = Matrix2x2d(1.0, 2.0, 3.0, 4.0).transpose();
        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 3.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 4.0);
    }
}

TEST(TestMatrixd2x2d, getTranspose)
{
    // transpose dont change diagonal
    {
        const Matrix2x2d m = Matrix2x2d::identity().getTranspose();
        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 1.0);
    }

    // transpose change order element who are dont in the diagonal
    {
        const Matrix2x2d m = Matrix2x2d(1.0, 2.0, 3.0, 4.0).getTranspose();
        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 3.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 4.0);
    }
}

TEST(TestMatrixd2x2d, determinant)
{
    // determiant of identity => 1.0
    {
        const double value = Matrix2x2d::identity().determinant();
        EXPECT_DOUBLE_EQ(value, 1.0);
    }

    // determiant of identity => 1.0
    {
        const Matrix2x2d m = Matrix2x2d(Vector2d::zero(), Vector2d::zero());
        EXPECT_DOUBLE_EQ(m.determinant(), 0.0);
    }

    // determinant of non-trivial matrix => 1.0
    {
        const Matrix2x2d m(Vector2d(2.0, 3.0), Vector2d(1.0, 2.0));

        EXPECT_DOUBLE_EQ(m.determinant(), 1.0);
    }

    // determinant of non-trivial matrix
    {
        const Matrix2x2d m(Vector2d(7.0, -3.0), Vector2d(4.0, 5.0));

        EXPECT_DOUBLE_EQ(m.determinant(), 47.0);
    }
}

TEST(TestMatrixd2x2d, inverse)
{
    // Inverse of identity => identity
    {
        const Matrix2x2d m = Matrix2x2d(Vector2d(1.0, 0.0), Vector2d(0.0, 1.0)).inverse();
        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 1.0);
    }

    // Inverse of arbitrary matrix
    {
        const Matrix2x2d m = Matrix2x2d(Vector2d(4.0, 7.0), Vector2d(2.0, 6.0)).inverse();

        EXPECT_DOUBLE_EQ(m.getM11(), 0.6);
        EXPECT_DOUBLE_EQ(m.getM12(), -0.7);
        EXPECT_DOUBLE_EQ(m.getM21(), -0.2);
        EXPECT_DOUBLE_EQ(m.getM22(), 0.4);
    }
}

TEST(TestMatrixd2x2d, getInverse)
{
    // Inverse of identity => identity
    {
        const Matrix2x2d m = Matrix2x2d(Vector2d(1.0, 0.0), Vector2d(0.0, 1.0)).getInverse();
        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 1.0);
    }

    // Inverse of arbitrary matrix
    {
        const Matrix2x2d m = Matrix2x2d(Vector2d(4.0, 7.0), Vector2d(2.0, 6.0)).getInverse();

        EXPECT_DOUBLE_EQ(m.getM11(), 0.6);
        EXPECT_DOUBLE_EQ(m.getM12(), -0.7);
        EXPECT_DOUBLE_EQ(m.getM21(), -0.2);
        EXPECT_DOUBLE_EQ(m.getM22(), 0.4);
    }
}

TEST(TestMatrixd2x2d, addScalarOperator)
{
    {
        Matrix2x2d m(1.0, 2.0, 3.0, 4.0);
        m += 10.0;
        EXPECT_DOUBLE_EQ(m.getM11(), 11.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 12.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 13.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 14.0);
    }

    {
        const Matrix2x2d m = Matrix2x2d(1.0, 2.0, 3.0, 4.0) + 10.0;
        EXPECT_DOUBLE_EQ(m.getM11(), 11.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 12.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 13.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 14.0);
    }
}

TEST(TestMatrixd2x2d, subScalarOperator)
{
    {
        Matrix2x2d m(1.0, 2.0, 3.0, 4.0);
        m -= 10.0;
        EXPECT_DOUBLE_EQ(m.getM11(), -9.0);
        EXPECT_DOUBLE_EQ(m.getM12(), -8.0);

        EXPECT_DOUBLE_EQ(m.getM21(), -7.0);
        EXPECT_DOUBLE_EQ(m.getM22(), -6.0);
    }

    {
        const Matrix2x2d m = Matrix2x2d(1.0, 2.0, 3.0, 4.0) - 10.0;
        EXPECT_DOUBLE_EQ(m.getM11(), -9.0);
        EXPECT_DOUBLE_EQ(m.getM12(), -8.0);

        EXPECT_DOUBLE_EQ(m.getM21(), -7.0);
        EXPECT_DOUBLE_EQ(m.getM22(), -6.0);
    }
}

TEST(TestMatrixd2x2d, mulScalarOperator)
{
    {
        Matrix2x2d m(1.0, 2.0, 3.0, 4.0);
        m *= 10.0;
        EXPECT_DOUBLE_EQ(m.getM11(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 20.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 30.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 40.0);
    }

    {
        const Matrix2x2d m = Matrix2x2d(1.0, 2.0, 3.0, 4.0) * 10.0;
        EXPECT_DOUBLE_EQ(m.getM11(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 20.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 30.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 40.0);
    }
}

TEST(TestMatrixd2x2d, divScalarOperator)
{
    {
        Matrix2x2d m(1.0, 2.0, 3.0, 4.0);
        m /= 10.0;
        EXPECT_DOUBLE_EQ(m.getM11(), 0.10);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.20);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.30);
        EXPECT_DOUBLE_EQ(m.getM22(), 0.40);
    }

    {
        const Matrix2x2d m = Matrix2x2d(1.0, 2.0, 3.0, 4.0) / 10.0;
        EXPECT_DOUBLE_EQ(m.getM11(), 0.10);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.20);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.30);
        EXPECT_DOUBLE_EQ(m.getM22(), 0.40);
    }
}

TEST(TestMatrixd2x2d, addMatrixOperator)
{
    {
        const Matrix2x2d m1(1.0, 2.0, 3.0, 4.0);
        Matrix2x2d m(5.0, 6.0, 7.0, 8.0);
        m += m1;
        EXPECT_DOUBLE_EQ(m.getM11(), 6.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 8.0);
        EXPECT_DOUBLE_EQ(m.getM21(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 12.0);
    }

    {
        const Matrix2x2d m1(1.0, 2.0, 3.0, 4.0);
        const Matrix2x2d m2(5.0, 6.0, 7.0, 8.0);
        const Matrix2x2d m = m1 + m2;
        EXPECT_DOUBLE_EQ(m.getM11(), 6.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 8.0);
        EXPECT_DOUBLE_EQ(m.getM21(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 12.0);
    }
}

TEST(TestMatrixd2x2d, subMatrixOperator)
{
    {
        Matrix2x2d m(1.0, 2.0, 3.0, 4.0);
        const Matrix2x2d m1(5.0, 6.0, 7.0, 8.0);
        m -= m1;
        EXPECT_DOUBLE_EQ(m.getM11(), -4.0);
        EXPECT_DOUBLE_EQ(m.getM12(), -4.0);
        EXPECT_DOUBLE_EQ(m.getM21(), -4.0);
        EXPECT_DOUBLE_EQ(m.getM22(), -4.0);
    }

    {
        const Matrix2x2d m1(1.0, 2.0, 3.0, 4.0);
        const Matrix2x2d m2(5.0, 6.0, 7.0, 8.0);
        const Matrix2x2d m = m1 - m2;
        EXPECT_DOUBLE_EQ(m.getM11(), -4.0);
        EXPECT_DOUBLE_EQ(m.getM12(), -4.0);
        EXPECT_DOUBLE_EQ(m.getM21(), -4.0);
        EXPECT_DOUBLE_EQ(m.getM22(), -4.0);
    }
}

TEST(TestMatrixd2x2d, mulMatrixOperator)
{
    {
        Matrix2x2d m(1.0, 2.0, 3.0, 4.0);

        const Matrix2x2d m1(5.0, 6.0, 7.0, 8.0);

        m *= m1;

        EXPECT_DOUBLE_EQ(m.getM11(), 19.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 22.0);
        EXPECT_DOUBLE_EQ(m.getM21(), 43.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 50.0);
    }

    {
        const Matrix2x2d m1(1.0, 2.0, 3.0, 4.0);

        const Matrix2x2d m2(5.0, 6.0, 7.0, 8.0);

        const Matrix2x2d m = m1 * m2;

        EXPECT_DOUBLE_EQ(m.getM11(), 19.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 22.0);
        EXPECT_DOUBLE_EQ(m.getM21(), 43.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 50.0);
    }
}

TEST(TestMatrixd2x2d, cmpOperator)
{
    {
        const Matrix2x2d m1 = Matrix2x2d(1.0, 2.0, 3.0, 4.0);
        const Matrix2x2d m2 = Matrix2x2d::identity();
        EXPECT_TRUE(m1 == m1);
        EXPECT_FALSE(m1 == m2);
        EXPECT_FALSE(m1 != m1);
        EXPECT_TRUE(m1 != m2);
    }

    constexpr double DoubleEpsilonHalf = 0.5 * DoubleEpsilon;
    constexpr double DoubleEpsilon2 = 2.0 * DoubleEpsilon;

    {
        const Matrix2x2d m1 = Matrix2x2d(1.0, 2.0, 3.0, 4.0);
        const Matrix2x2d m2 = Matrix2x2d(1.0 - DoubleEpsilonHalf, 2.0 - DoubleEpsilonHalf, 3.0 - DoubleEpsilonHalf,
                                         4.0 - DoubleEpsilonHalf);

        EXPECT_TRUE(m1 == m2);
        EXPECT_FALSE(m1 != m2);
    }

    {
        const Matrix2x2d m1 = Matrix2x2d(1.0, 2.0, 3.0, 4.0);
        const Matrix2x2d m2 =
            Matrix2x2d(1.0 - DoubleEpsilon2, 2.0 - DoubleEpsilon2, 3.0 - DoubleEpsilon2, 4.0 - DoubleEpsilon2);

        EXPECT_TRUE(m1 != m2);
        EXPECT_FALSE(m1 == m2);
    }
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
