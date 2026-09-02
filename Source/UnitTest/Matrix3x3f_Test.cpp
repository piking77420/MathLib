#include <gtest/gtest.h>

#include <numbers>

#include <MathLibHeader.hpp>
#include <MatrixTransformation.hpp>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

using namespace MathLib;

TEST(TestMatrix3x3f, constructor)
{
    {
        // clang-format off
        const Matrix3x3f m(1.0, 2.0, 3.0, 
                           4.0, 5.0, 6.0,
                           7.0, 8.0,9.0);
        // clang-format on
        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 2.0);
        EXPECT_FLOAT_EQ(m.getM13(), 3.0);

        EXPECT_FLOAT_EQ(m.getM21(), 4.0);
        EXPECT_FLOAT_EQ(m.getM22(), 5.0);
        EXPECT_FLOAT_EQ(m.getM23(), 6.0);

        EXPECT_FLOAT_EQ(m.getM31(), 7.0);
        EXPECT_FLOAT_EQ(m.getM32(), 8.0);
        EXPECT_FLOAT_EQ(m.getM33(), 9.0);
    }

    {
        // clang-format off
        const Matrix3x3f m(Vector3f(1.0, 2.0, 3.0), 
                           Vector3f(4.0, 5.0, 6.0),
                           Vector3f(7.0, 8.0, 9.0));
        // clang-format on
        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 2.0);
        EXPECT_FLOAT_EQ(m.getM13(), 3.0);

        EXPECT_FLOAT_EQ(m.getM21(), 4.0);
        EXPECT_FLOAT_EQ(m.getM22(), 5.0);
        EXPECT_FLOAT_EQ(m.getM23(), 6.0);

        EXPECT_FLOAT_EQ(m.getM31(), 7.0);
        EXPECT_FLOAT_EQ(m.getM32(), 8.0);
        EXPECT_FLOAT_EQ(m.getM33(), 9.0);
    }
}

TEST(TestMatrix3x3f, identity)
{
    const Matrix3x3f m = Matrix3x3f::identity();

    EXPECT_FLOAT_EQ(m.getM11(), 1.0);
    EXPECT_FLOAT_EQ(m.getM12(), 0.0);
    EXPECT_FLOAT_EQ(m.getM13(), 0.0);

    EXPECT_FLOAT_EQ(m.getM21(), 0.0);
    EXPECT_FLOAT_EQ(m.getM22(), 1.0);
    EXPECT_FLOAT_EQ(m.getM23(), 0.0);

    EXPECT_FLOAT_EQ(m.getM31(), 0.0);
    EXPECT_FLOAT_EQ(m.getM32(), 0.0);
    EXPECT_FLOAT_EQ(m.getM33(), 1.0);
}

TEST(TestMatrix3x3f, setter)
{
    Matrix3x3f m = Matrix3x3f::zero();
    m.setM11(1.0) //
        .setM12(2.0)
        .setM13(3.0)
        .setM21(4.0) //
        .setM22(5.0)
        .setM23(6.0)
        .setM31(7.0) //
        .setM32(8.0)
        .setM33(9.0);

    EXPECT_FLOAT_EQ(m.getM11(), 1.0);
    EXPECT_FLOAT_EQ(m.getM12(), 2.0);
    EXPECT_FLOAT_EQ(m.getM13(), 3.0);

    EXPECT_FLOAT_EQ(m.getM21(), 4.0);
    EXPECT_FLOAT_EQ(m.getM22(), 5.0);
    EXPECT_FLOAT_EQ(m.getM23(), 6.0);

    EXPECT_FLOAT_EQ(m.getM31(), 7.0);
    EXPECT_FLOAT_EQ(m.getM32(), 8.0);
    EXPECT_FLOAT_EQ(m.getM33(), 9.0);
}

TEST(TestMatrix3x3f, transpose)
{
    // Transposing identity does not change anything.
    {
        const Matrix3x3f m = Matrix3x3f::identity().transpose();

        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 0.0);
        EXPECT_FLOAT_EQ(m.getM13(), 0.0);

        EXPECT_FLOAT_EQ(m.getM21(), 0.0);
        EXPECT_FLOAT_EQ(m.getM22(), 1.0);
        EXPECT_FLOAT_EQ(m.getM23(), 0.0);

        EXPECT_FLOAT_EQ(m.getM31(), 0.0);
        EXPECT_FLOAT_EQ(m.getM32(), 0.0);
        EXPECT_FLOAT_EQ(m.getM33(), 1.0);
    }

    // Transpose swaps rows and columns.
    {
        // clang-format off

        const Matrix3x3f m = Matrix3x3f(1.0, 2.0, 3.0, 
                                        4.0, 5.0, 6.0, 
                                        7.0, 8.0, 9.0).transpose();
        // clang-format on

        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 4.0);
        EXPECT_FLOAT_EQ(m.getM13(), 7.0);

        EXPECT_FLOAT_EQ(m.getM21(), 2.0);
        EXPECT_FLOAT_EQ(m.getM22(), 5.0);
        EXPECT_FLOAT_EQ(m.getM23(), 8.0);

        EXPECT_FLOAT_EQ(m.getM31(), 3.0);
        EXPECT_FLOAT_EQ(m.getM32(), 6.0);
        EXPECT_FLOAT_EQ(m.getM33(), 9.0);
    }
}

TEST(TestMatrix3x3f, getTranspose)
{
    // Transposing identity does not change anything.
    {
        const Matrix3x3f m = Matrix3x3f::identity().getTranspose();

        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 0.0);
        EXPECT_FLOAT_EQ(m.getM13(), 0.0);

        EXPECT_FLOAT_EQ(m.getM21(), 0.0);
        EXPECT_FLOAT_EQ(m.getM22(), 1.0);
        EXPECT_FLOAT_EQ(m.getM23(), 0.0);

        EXPECT_FLOAT_EQ(m.getM31(), 0.0);
        EXPECT_FLOAT_EQ(m.getM32(), 0.0);
        EXPECT_FLOAT_EQ(m.getM33(), 1.0);
    }

    // Transpose swaps rows and columns.
    {
        // clang-format off

        const Matrix3x3f m = Matrix3x3f(1.0, 2.0, 3.0, 
                                        4.0, 5.0, 6.0, 
                                        7.0, 8.0, 9.0).getTranspose();
        // clang-format on

        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 4.0);
        EXPECT_FLOAT_EQ(m.getM13(), 7.0);

        EXPECT_FLOAT_EQ(m.getM21(), 2.0);
        EXPECT_FLOAT_EQ(m.getM22(), 5.0);
        EXPECT_FLOAT_EQ(m.getM23(), 8.0);

        EXPECT_FLOAT_EQ(m.getM31(), 3.0);
        EXPECT_FLOAT_EQ(m.getM32(), 6.0);
        EXPECT_FLOAT_EQ(m.getM33(), 9.0);
    }
}

TEST(TestMatrix3x3f, determinant)
{
    // determinant of identity => 1.0
    {
        const float value = Matrix3x3f::identity().determinant();
        EXPECT_FLOAT_EQ(value, 1.0);
    }

    // determinant of zero matrix => 0.0
    {
        const Matrix3x3f m(Vector3f::zero(), Vector3f::zero(), Vector3f::zero());

        EXPECT_FLOAT_EQ(m.determinant(), 0.0);
    }

    // determinant of non-trivial matrix => 1.0
    {
        const Matrix3x3f m(Vector3f(1.0, 2.0, 3.0), Vector3f(0.0, 1.0, 4.0), Vector3f(5.0, 6.0, 0.0));

        EXPECT_FLOAT_EQ(m.determinant(), 1.0);
    }

    // determinant of non-trivial matrix => -306.0
    {
        const Matrix3x3f m(Vector3f(6.0, 1.0, 1.0), Vector3f(4.0, -2.0, 5.0), Vector3f(2.0, 8.0, 7.0));

        EXPECT_FLOAT_EQ(m.determinant(), -306.0);
    }

    // linearly dependent rows => determinant 0.0
    {
        const Matrix3x3f m(Vector3f(1.0, 2.0, 3.0), Vector3f(2.0, 4.0, 6.0), Vector3f(4.0, 5.0, 6.0));

        EXPECT_FLOAT_EQ(m.determinant(), 0.0);
    }
}

TEST(TestMatrix3x3f, inverse)
{
    // inverse of identity => identity
    {
        Matrix3x3f m = Matrix3x3f::identity();
        m.inverse();

        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 0.0);
        EXPECT_FLOAT_EQ(m.getM13(), 0.0);

        EXPECT_FLOAT_EQ(m.getM21(), 0.0);
        EXPECT_FLOAT_EQ(m.getM22(), 1.0);
        EXPECT_FLOAT_EQ(m.getM23(), 0.0);

        EXPECT_FLOAT_EQ(m.getM31(), 0.0);
        EXPECT_FLOAT_EQ(m.getM32(), 0.0);
        EXPECT_FLOAT_EQ(m.getM33(), 1.0);
    }

    // inverse of diagonal matrix
    {
        Matrix3x3f m(Vector3f(2.0, 0.0, 0.0), Vector3f(0.0, 4.0, 0.0), Vector3f(0.0, 0.0, 5.0));

        m.inverse();

        EXPECT_FLOAT_EQ(m.getM11(), 0.5);
        EXPECT_FLOAT_EQ(m.getM12(), 0.0);
        EXPECT_FLOAT_EQ(m.getM13(), 0.0);

        EXPECT_FLOAT_EQ(m.getM21(), 0.0);
        EXPECT_FLOAT_EQ(m.getM22(), 0.25);
        EXPECT_FLOAT_EQ(m.getM23(), 0.0);

        EXPECT_FLOAT_EQ(m.getM31(), 0.0);
        EXPECT_FLOAT_EQ(m.getM32(), 0.0);
        EXPECT_FLOAT_EQ(m.getM33(), 0.2);
    }

    // inverse of non-trivial matrix
    {
        // determinant = 1
        //
        // [1 2 3]^-1   [-24  18   5]
        // [0 1 4]    = [ 20 -15  -4]
        // [5 6 0]      [ -5   4   1]
        Matrix3x3f m(Vector3f(1.0, 2.0, 3.0), Vector3f(0.0, 1.0, 4.0), Vector3f(5.0, 6.0, 0.0));

        m.inverse();

        EXPECT_FLOAT_EQ(m.getM11(), -24.0);
        EXPECT_FLOAT_EQ(m.getM12(), 18.0);
        EXPECT_FLOAT_EQ(m.getM13(), 5.0);

        EXPECT_FLOAT_EQ(m.getM21(), 20.0);
        EXPECT_FLOAT_EQ(m.getM22(), -15.0);
        EXPECT_FLOAT_EQ(m.getM23(), -4.0);

        EXPECT_FLOAT_EQ(m.getM31(), -5.0);
        EXPECT_FLOAT_EQ(m.getM32(), 4.0);
        EXPECT_FLOAT_EQ(m.getM33(), 1.0);
    }

    // singular matrix => inverse leaves matrix unchanged
    {
        Matrix3x3f m(Vector3f(1.0, 2.0, 3.0), Vector3f(2.0, 4.0, 6.0), Vector3f(3.0, 6.0, 9.0));

        m.inverse();

        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 2.0);
        EXPECT_FLOAT_EQ(m.getM13(), 3.0);

        EXPECT_FLOAT_EQ(m.getM21(), 2.0);
        EXPECT_FLOAT_EQ(m.getM22(), 4.0);
        EXPECT_FLOAT_EQ(m.getM23(), 6.0);

        EXPECT_FLOAT_EQ(m.getM31(), 3.0);
        EXPECT_FLOAT_EQ(m.getM32(), 6.0);
        EXPECT_FLOAT_EQ(m.getM33(), 9.0);
    }
}

TEST(TestMatrix3x3f, getInverse)
{
    // inverse of identity => identity
    {
        Matrix3x3f m = Matrix3x3f::identity().getInverse();

        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 0.0);
        EXPECT_FLOAT_EQ(m.getM13(), 0.0);

        EXPECT_FLOAT_EQ(m.getM21(), 0.0);
        EXPECT_FLOAT_EQ(m.getM22(), 1.0);
        EXPECT_FLOAT_EQ(m.getM23(), 0.0);

        EXPECT_FLOAT_EQ(m.getM31(), 0.0);
        EXPECT_FLOAT_EQ(m.getM32(), 0.0);
        EXPECT_FLOAT_EQ(m.getM33(), 1.0);
    }

    // inverse of diagonal matrix
    {
        Matrix3x3f m =
            Matrix3x3f(Vector3f(2.0, 0.0, 0.0), Vector3f(0.0, 4.0, 0.0), Vector3f(0.0, 0.0, 5.0)).getInverse();

        EXPECT_FLOAT_EQ(m.getM11(), 0.5);
        EXPECT_FLOAT_EQ(m.getM12(), 0.0);
        EXPECT_FLOAT_EQ(m.getM13(), 0.0);

        EXPECT_FLOAT_EQ(m.getM21(), 0.0);
        EXPECT_FLOAT_EQ(m.getM22(), 0.25);
        EXPECT_FLOAT_EQ(m.getM23(), 0.0);

        EXPECT_FLOAT_EQ(m.getM31(), 0.0);
        EXPECT_FLOAT_EQ(m.getM32(), 0.0);
        EXPECT_FLOAT_EQ(m.getM33(), 0.2);
    }

    // inverse of non-trivial matrix
    {
        // determinant = 1
        //
        // [1 2 3]^-1   [-24  18   5]
        // [0 1 4]    = [ 20 -15  -4]
        // [5 6 0]      [ -5   4   1]
        Matrix3x3f m =
            Matrix3x3f(Vector3f(1.0, 2.0, 3.0), Vector3f(0.0, 1.0, 4.0), Vector3f(5.0, 6.0, 0.0)).getInverse();

        EXPECT_FLOAT_EQ(m.getM11(), -24.0);
        EXPECT_FLOAT_EQ(m.getM12(), 18.0);
        EXPECT_FLOAT_EQ(m.getM13(), 5.0);

        EXPECT_FLOAT_EQ(m.getM21(), 20.0);
        EXPECT_FLOAT_EQ(m.getM22(), -15.0);
        EXPECT_FLOAT_EQ(m.getM23(), -4.0);

        EXPECT_FLOAT_EQ(m.getM31(), -5.0);
        EXPECT_FLOAT_EQ(m.getM32(), 4.0);
        EXPECT_FLOAT_EQ(m.getM33(), 1.0);
    }

    // singular matrix => inverse leaves matrix unchanged
    {
        Matrix3x3f m =
            Matrix3x3f(Vector3f(1.0, 2.0, 3.0), Vector3f(2.0, 4.0, 6.0), Vector3f(3.0, 6.0, 9.0)).getInverse();

        EXPECT_FLOAT_EQ(m.getM11(), 1.0);
        EXPECT_FLOAT_EQ(m.getM12(), 2.0);
        EXPECT_FLOAT_EQ(m.getM13(), 3.0);

        EXPECT_FLOAT_EQ(m.getM21(), 2.0);
        EXPECT_FLOAT_EQ(m.getM22(), 4.0);
        EXPECT_FLOAT_EQ(m.getM23(), 6.0);

        EXPECT_FLOAT_EQ(m.getM31(), 3.0);
        EXPECT_FLOAT_EQ(m.getM32(), 6.0);
        EXPECT_FLOAT_EQ(m.getM33(), 9.0);
    }
}

TEST(TestMatrix3x3f, addScalarOperator)
{
    {
        Matrix3x3f m(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

        m += 10.0;

        EXPECT_FLOAT_EQ(m.getM11(), 11.0);
        EXPECT_FLOAT_EQ(m.getM12(), 12.0);
        EXPECT_FLOAT_EQ(m.getM13(), 13.0);

        EXPECT_FLOAT_EQ(m.getM21(), 14.0);
        EXPECT_FLOAT_EQ(m.getM22(), 15.0);
        EXPECT_FLOAT_EQ(m.getM23(), 16.0);

        EXPECT_FLOAT_EQ(m.getM31(), 17.0);
        EXPECT_FLOAT_EQ(m.getM32(), 18.0);
        EXPECT_FLOAT_EQ(m.getM33(), 19.0);
    }

    {
        const Matrix3x3f m = Matrix3x3f(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0) + 10.0;

        EXPECT_FLOAT_EQ(m.getM11(), 11.0);
        EXPECT_FLOAT_EQ(m.getM12(), 12.0);
        EXPECT_FLOAT_EQ(m.getM13(), 13.0);

        EXPECT_FLOAT_EQ(m.getM21(), 14.0);
        EXPECT_FLOAT_EQ(m.getM22(), 15.0);
        EXPECT_FLOAT_EQ(m.getM23(), 16.0);

        EXPECT_FLOAT_EQ(m.getM31(), 17.0);
        EXPECT_FLOAT_EQ(m.getM32(), 18.0);
        EXPECT_FLOAT_EQ(m.getM33(), 19.0);
    }
}

TEST(TestMatrix3x3f, subScalarOperator)
{
    {
        Matrix3x3f m(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

        m -= 10.0;

        EXPECT_FLOAT_EQ(m.getM11(), -9.0);
        EXPECT_FLOAT_EQ(m.getM12(), -8.0);
        EXPECT_FLOAT_EQ(m.getM13(), -7.0);

        EXPECT_FLOAT_EQ(m.getM21(), -6.0);
        EXPECT_FLOAT_EQ(m.getM22(), -5.0);
        EXPECT_FLOAT_EQ(m.getM23(), -4.0);

        EXPECT_FLOAT_EQ(m.getM31(), -3.0);
        EXPECT_FLOAT_EQ(m.getM32(), -2.0);
        EXPECT_FLOAT_EQ(m.getM33(), -1.0);
    }

    {
        const Matrix3x3f m = Matrix3x3f(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0) - 10.0;

        EXPECT_FLOAT_EQ(m.getM11(), -9.0);
        EXPECT_FLOAT_EQ(m.getM12(), -8.0);
        EXPECT_FLOAT_EQ(m.getM13(), -7.0);

        EXPECT_FLOAT_EQ(m.getM21(), -6.0);
        EXPECT_FLOAT_EQ(m.getM22(), -5.0);
        EXPECT_FLOAT_EQ(m.getM23(), -4.0);

        EXPECT_FLOAT_EQ(m.getM31(), -3.0);
        EXPECT_FLOAT_EQ(m.getM32(), -2.0);
        EXPECT_FLOAT_EQ(m.getM33(), -1.0);
    }
}

TEST(TestMatrix3x3f, mulScalarOperator)
{
    {
        Matrix3x3f m(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

        m *= 10.0;

        EXPECT_FLOAT_EQ(m.getM11(), 10.0);
        EXPECT_FLOAT_EQ(m.getM12(), 20.0);
        EXPECT_FLOAT_EQ(m.getM13(), 30.0);

        EXPECT_FLOAT_EQ(m.getM21(), 40.0);
        EXPECT_FLOAT_EQ(m.getM22(), 50.0);
        EXPECT_FLOAT_EQ(m.getM23(), 60.0);

        EXPECT_FLOAT_EQ(m.getM31(), 70.0);
        EXPECT_FLOAT_EQ(m.getM32(), 80.0);
        EXPECT_FLOAT_EQ(m.getM33(), 90.0);
    }

    {
        const Matrix3x3f m = Matrix3x3f(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0) * 10.0;

        EXPECT_FLOAT_EQ(m.getM11(), 10.0);
        EXPECT_FLOAT_EQ(m.getM12(), 20.0);
        EXPECT_FLOAT_EQ(m.getM13(), 30.0);

        EXPECT_FLOAT_EQ(m.getM21(), 40.0);
        EXPECT_FLOAT_EQ(m.getM22(), 50.0);
        EXPECT_FLOAT_EQ(m.getM23(), 60.0);

        EXPECT_FLOAT_EQ(m.getM31(), 70.0);
        EXPECT_FLOAT_EQ(m.getM32(), 80.0);
        EXPECT_FLOAT_EQ(m.getM33(), 90.0);
    }
}

TEST(TestMatrix3x3f, divScalarOperator)
{
    {
        Matrix3x3f m(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

        m /= 10.0;

        EXPECT_FLOAT_EQ(m.getM11(), 0.1);
        EXPECT_FLOAT_EQ(m.getM12(), 0.2);
        EXPECT_FLOAT_EQ(m.getM13(), 0.3);

        EXPECT_FLOAT_EQ(m.getM21(), 0.4);
        EXPECT_FLOAT_EQ(m.getM22(), 0.5);
        EXPECT_FLOAT_EQ(m.getM23(), 0.6);

        EXPECT_FLOAT_EQ(m.getM31(), 0.7);
        EXPECT_FLOAT_EQ(m.getM32(), 0.8);
        EXPECT_FLOAT_EQ(m.getM33(), 0.9);
    }

    {
        const Matrix3x3f m = Matrix3x3f(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0) / 10.0;

        EXPECT_FLOAT_EQ(m.getM11(), 0.1);
        EXPECT_FLOAT_EQ(m.getM12(), 0.2);
        EXPECT_FLOAT_EQ(m.getM13(), 0.3);

        EXPECT_FLOAT_EQ(m.getM21(), 0.4);
        EXPECT_FLOAT_EQ(m.getM22(), 0.5);
        EXPECT_FLOAT_EQ(m.getM23(), 0.6);

        EXPECT_FLOAT_EQ(m.getM31(), 0.7);
        EXPECT_FLOAT_EQ(m.getM32(), 0.8);
        EXPECT_FLOAT_EQ(m.getM33(), 0.9);
    }
}

TEST(TestMatrix3x3f, addMatrixOperator)
{
    const Matrix3x3f m1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

    const Matrix3x3f m2(9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0);

    {
        Matrix3x3f m = m1;
        m += m2;

        EXPECT_FLOAT_EQ(m.getM11(), 10.0);
        EXPECT_FLOAT_EQ(m.getM12(), 10.0);
        EXPECT_FLOAT_EQ(m.getM13(), 10.0);

        EXPECT_FLOAT_EQ(m.getM21(), 10.0);
        EXPECT_FLOAT_EQ(m.getM22(), 10.0);
        EXPECT_FLOAT_EQ(m.getM23(), 10.0);

        EXPECT_FLOAT_EQ(m.getM31(), 10.0);
        EXPECT_FLOAT_EQ(m.getM32(), 10.0);
        EXPECT_FLOAT_EQ(m.getM33(), 10.0);
    }

    {
        const Matrix3x3f m = m1 + m2;

        EXPECT_FLOAT_EQ(m.getM11(), 10.0);
        EXPECT_FLOAT_EQ(m.getM12(), 10.0);
        EXPECT_FLOAT_EQ(m.getM13(), 10.0);

        EXPECT_FLOAT_EQ(m.getM21(), 10.0);
        EXPECT_FLOAT_EQ(m.getM22(), 10.0);
        EXPECT_FLOAT_EQ(m.getM23(), 10.0);

        EXPECT_FLOAT_EQ(m.getM31(), 10.0);
        EXPECT_FLOAT_EQ(m.getM32(), 10.0);
        EXPECT_FLOAT_EQ(m.getM33(), 10.0);
    }
}

TEST(TestMatrix3x3f, subMatrixOperator)
{
    const Matrix3x3f m1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

    const Matrix3x3f m2(9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0);

    {
        Matrix3x3f m = m1;
        m -= m2;

        EXPECT_FLOAT_EQ(m.getM11(), -8.0);
        EXPECT_FLOAT_EQ(m.getM12(), -6.0);
        EXPECT_FLOAT_EQ(m.getM13(), -4.0);

        EXPECT_FLOAT_EQ(m.getM21(), -2.0);
        EXPECT_FLOAT_EQ(m.getM22(), 0.0);
        EXPECT_FLOAT_EQ(m.getM23(), 2.0);

        EXPECT_FLOAT_EQ(m.getM31(), 4.0);
        EXPECT_FLOAT_EQ(m.getM32(), 6.0);
        EXPECT_FLOAT_EQ(m.getM33(), 8.0);
    }

    {
        const Matrix3x3f m = m1 - m2;

        EXPECT_FLOAT_EQ(m.getM11(), -8.0);
        EXPECT_FLOAT_EQ(m.getM12(), -6.0);
        EXPECT_FLOAT_EQ(m.getM13(), -4.0);

        EXPECT_FLOAT_EQ(m.getM21(), -2.0);
        EXPECT_FLOAT_EQ(m.getM22(), 0.0);
        EXPECT_FLOAT_EQ(m.getM23(), 2.0);

        EXPECT_FLOAT_EQ(m.getM31(), 4.0);
        EXPECT_FLOAT_EQ(m.getM32(), 6.0);
        EXPECT_FLOAT_EQ(m.getM33(), 8.0);
    }
}

TEST(TestMatrix3x3f, mulMatrixOperator)
{
    const Matrix3x3f m1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

    const Matrix3x3f m2(9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0);

    {
        Matrix3x3f m = m1;
        m *= m2;

        EXPECT_FLOAT_EQ(m.getM11(), 30.0);
        EXPECT_FLOAT_EQ(m.getM12(), 24.0);
        EXPECT_FLOAT_EQ(m.getM13(), 18.0);

        EXPECT_FLOAT_EQ(m.getM21(), 84.0);
        EXPECT_FLOAT_EQ(m.getM22(), 69.0);
        EXPECT_FLOAT_EQ(m.getM23(), 54.0);

        EXPECT_FLOAT_EQ(m.getM31(), 138.0);
        EXPECT_FLOAT_EQ(m.getM32(), 114.0);
        EXPECT_FLOAT_EQ(m.getM33(), 90.0);
    }

    {
        const Matrix3x3f m = m1 * m2;

        EXPECT_FLOAT_EQ(m.getM11(), 30.0);
        EXPECT_FLOAT_EQ(m.getM12(), 24.0);
        EXPECT_FLOAT_EQ(m.getM13(), 18.0);

        EXPECT_FLOAT_EQ(m.getM21(), 84.0);
        EXPECT_FLOAT_EQ(m.getM22(), 69.0);
        EXPECT_FLOAT_EQ(m.getM23(), 54.0);

        EXPECT_FLOAT_EQ(m.getM31(), 138.0);
        EXPECT_FLOAT_EQ(m.getM32(), 114.0);
        EXPECT_FLOAT_EQ(m.getM33(), 90.0);
    }
}

TEST(TestMatrix3x3f, cmpOperator)
{
    {
        const Matrix3x3f m1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

        const Matrix3x3f m2 = Matrix3x3f::identity();

        EXPECT_TRUE(m1 == m1);
        EXPECT_FALSE(m1 == m2);
        EXPECT_FALSE(m1 != m1);
        EXPECT_TRUE(m1 != m2);
    }

    constexpr float FloatEpsilonHalf = 0.5 * FloatEpsilon;
    constexpr float FloatEpsilon2 = 2.0 * FloatEpsilon;

    {
        const Matrix3x3f m1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

        const Matrix3x3f m2(1.0 - FloatEpsilonHalf, 2.0 - FloatEpsilonHalf, 3.0 - FloatEpsilonHalf,
                            4.0 - FloatEpsilonHalf, 5.0 - FloatEpsilonHalf, 6.0 - FloatEpsilonHalf,
                            7.0 - FloatEpsilonHalf, 8.0 - FloatEpsilonHalf, 9.0 - FloatEpsilonHalf);

        EXPECT_TRUE(m1 == m2);
        EXPECT_FALSE(m1 != m2);
    }

    {
        const Matrix3x3f m1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

        const Matrix3x3f m2(1.0 - FloatEpsilon2, 2.0 - FloatEpsilon2, 3.0 - FloatEpsilon2, 4.0 - FloatEpsilon2,
                            5.0 - FloatEpsilon2, 6.0 - FloatEpsilon2, 7.0 - FloatEpsilon2, 8.0 - FloatEpsilon2,
                            9.0 - FloatEpsilon2);

        EXPECT_TRUE(m1 != m2);
        EXPECT_FALSE(m1 == m2);
    }
}

TEST(TestMatrix3x3f, rotationX)
{
    {
        const float angle = 0.0;
        const Matrix3x3f m = MathLib::rotationX<Matrix3x3f>(angle);

        EXPECT_NEAR(m.getM11(), 1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM12(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM13(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM21(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM22(), 1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM23(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM31(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM32(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM33(), 1.0, FloatEpsilon);
    }

    {
        const float angle = std::numbers::pi;
        const Matrix3x3f m = MathLib::rotationX<Matrix3x3f>(angle);

        EXPECT_NEAR(m.getM11(), 1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM12(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM13(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM21(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM22(), -1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM23(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM31(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM32(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM33(), -1.0, FloatEpsilon);
    }

    {
        const float angle = std::numbers::pi * 0.5;
        const Matrix3x3f m = MathLib::rotationX<Matrix3x3f>(angle);

        EXPECT_NEAR(m.getM11(), 1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM12(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM13(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM21(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM22(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM23(), -1.0, FloatEpsilon);

        EXPECT_NEAR(m.getM31(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM32(), 1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM33(), 0.0, FloatEpsilon);
    }

    {
        const float angle = -std::numbers::pi * 0.5;
        const Matrix3x3f m = MathLib::rotationX<Matrix3x3f>(angle);

        EXPECT_NEAR(m.getM11(), 1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM12(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM13(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM21(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM22(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM23(), 1.0, FloatEpsilon);

        EXPECT_NEAR(m.getM31(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM32(), -1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM33(), 0.0, FloatEpsilon);
    }
}

TEST(TestMatrix3x3f, rotationY)
{
    {
        const float angle = 0.0;
        const Matrix3x3f m = MathLib::rotationY<Matrix3x3f>(angle);

        EXPECT_NEAR(m.getM11(), 1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM12(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM13(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM21(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM22(), 1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM23(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM31(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM32(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM33(), 1.0, FloatEpsilon);
    }

    {
        const float angle = std::numbers::pi;
        const Matrix3x3f m = MathLib::rotationY<Matrix3x3f>(angle);

        EXPECT_NEAR(m.getM11(), -1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM12(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM13(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM21(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM22(), 1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM23(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM31(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM32(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM33(), -1.0, FloatEpsilon);
    }

    {
        const float angle = std::numbers::pi * 0.5;
        const Matrix3x3f m = MathLib::rotationY<Matrix3x3f>(angle);

        EXPECT_NEAR(m.getM11(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM12(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM13(), 1.0, FloatEpsilon);

        EXPECT_NEAR(m.getM21(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM22(), 1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM23(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM31(), -1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM32(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM33(), 0.0, FloatEpsilon);
    }

    {
        const float angle = -std::numbers::pi * 0.5;
        const Matrix3x3f m = MathLib::rotationY<Matrix3x3f>(angle);

        EXPECT_NEAR(m.getM11(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM12(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM13(), -1.0, FloatEpsilon);

        EXPECT_NEAR(m.getM21(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM22(), 1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM23(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM31(), 1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM32(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM33(), 0.0, FloatEpsilon);
    }
}

TEST(TestMatrix3x3f, rotationZ)
{
    {
        const float angle = 0.0;
        const Matrix3x3f m = MathLib::rotationZ<Matrix3x3f>(angle);

        EXPECT_NEAR(m.getM11(), 1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM12(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM13(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM21(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM22(), 1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM23(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM31(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM32(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM33(), 1.0, FloatEpsilon);
    }

    {
        const float angle = std::numbers::pi;
        const Matrix3x3f m = MathLib::rotationZ<Matrix3x3f>(angle);

        EXPECT_NEAR(m.getM11(), -1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM12(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM13(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM21(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM22(), -1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM23(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM31(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM32(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM33(), 1.0, FloatEpsilon);
    }

    {
        const float angle = std::numbers::pi * 0.5;
        const Matrix3x3f m = MathLib::rotationZ<Matrix3x3f>(angle);

        EXPECT_NEAR(m.getM11(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM12(), -1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM13(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM21(), 1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM22(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM23(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM31(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM32(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM33(), 1.0, FloatEpsilon);
    }

    {
        const float angle = -std::numbers::pi * 0.5;
        const Matrix3x3f m = MathLib::rotationZ<Matrix3x3f>(angle);

        EXPECT_NEAR(m.getM11(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM12(), 1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM13(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM21(), -1.0, FloatEpsilon);
        EXPECT_NEAR(m.getM22(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM23(), 0.0, FloatEpsilon);

        EXPECT_NEAR(m.getM31(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM32(), 0.0, FloatEpsilon);
        EXPECT_NEAR(m.getM33(), 1.0, FloatEpsilon);
    }
}

TEST(TestMatrix3x3f, rotationXYZ)
{
    const Vector3f rotation(0.0, std::numbers::pi * 0.5, -std::numbers::pi * 0.5);
    {
        {
            const Matrix3x3f m = MathLib::rotationXYZ<Matrix3x3f>(rotation.getX(), rotation.getY(), rotation.getZ());

            EXPECT_NEAR(m.getM11(), 0.0, FloatEpsilon);
            EXPECT_NEAR(m.getM12(), 1.0, FloatEpsilon);
            EXPECT_NEAR(m.getM13(), 0.0, FloatEpsilon);

            EXPECT_NEAR(m.getM21(), 0.0, FloatEpsilon);
            EXPECT_NEAR(m.getM22(), 0.0, FloatEpsilon);
            EXPECT_NEAR(m.getM23(), -1.0, FloatEpsilon);

            EXPECT_NEAR(m.getM31(), -1.0, FloatEpsilon);
            EXPECT_NEAR(m.getM32(), 0.0, FloatEpsilon);
            EXPECT_NEAR(m.getM33(), 0.0, FloatEpsilon);
        }

        {
            const Matrix3x3f m = MathLib::rotationXYZ<Matrix3x3f>(rotation);

            EXPECT_NEAR(m.getM11(), 0.0, FloatEpsilon);
            EXPECT_NEAR(m.getM12(), 1.0, FloatEpsilon);
            EXPECT_NEAR(m.getM13(), 0.0, FloatEpsilon);

            EXPECT_NEAR(m.getM21(), 0.0, FloatEpsilon);
            EXPECT_NEAR(m.getM22(), 0.0, FloatEpsilon);
            EXPECT_NEAR(m.getM23(), -1.0, FloatEpsilon);

            EXPECT_NEAR(m.getM31(), -1.0, FloatEpsilon);
            EXPECT_NEAR(m.getM32(), 0.0, FloatEpsilon);
            EXPECT_NEAR(m.getM33(), 0.0, FloatEpsilon);
        }
    }

    {
        const Vector3f rotation(0.37, -0.81, 1.24);
        {
            const Matrix3x3f m = MathLib::rotationXYZ<Matrix3x3f>(rotation.getX(), rotation.getY(), rotation.getZ());

            EXPECT_NEAR(m.getM11(), 0.22394652914908608, FloatEpsilon);
            EXPECT_NEAR(m.getM12(), -0.96684879119784306, FloatEpsilon);
            EXPECT_NEAR(m.getM13(), 0.12268401298191708, FloatEpsilon);

            EXPECT_NEAR(m.getM21(), 0.65211658553129300, FloatEpsilon);
            EXPECT_NEAR(m.getM22(), 0.05510293639876843, FloatEpsilon);
            EXPECT_NEAR(m.getM23(), -0.75611350025987570, FloatEpsilon);

            EXPECT_NEAR(m.getM31(), 0.72428717437014260, FloatEpsilon);
            EXPECT_NEAR(m.getM32(), 0.24933327367101035, FloatEpsilon);
            EXPECT_NEAR(m.getM33(), 0.64283824379342260, FloatEpsilon);
        }

        {
            const Matrix3x3f m = MathLib::rotationXYZ<Matrix3x3f>(rotation);

            EXPECT_NEAR(m.getM11(), 0.22394652914908608, FloatEpsilon);
            EXPECT_NEAR(m.getM12(), -0.96684879119784306, FloatEpsilon);
            EXPECT_NEAR(m.getM13(), 0.12268401298191708, FloatEpsilon);

            EXPECT_NEAR(m.getM21(), 0.65211658553129300, FloatEpsilon);
            EXPECT_NEAR(m.getM22(), 0.05510293639876843, FloatEpsilon);
            EXPECT_NEAR(m.getM23(), -0.75611350025987570, FloatEpsilon);

            EXPECT_NEAR(m.getM31(), 0.72428717437014260, FloatEpsilon);
            EXPECT_NEAR(m.getM32(), 0.24933327367101035, FloatEpsilon);
            EXPECT_NEAR(m.getM33(), 0.64283824379342260, FloatEpsilon);
        }
    }
}

TEST(TestMatrix3x3f, translation)
{
    const Vector2f t = Vector2f(1.0, 2.0);
    auto test = [](const Matrix3x3f& m)
    {
        EXPECT_DOUBLE_EQ(m.getM11(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 1.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 2.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
    };

    test(translation<Matrix3x3f>(t.getX(), t.getY()));
    test(translation<Matrix3x3f>(t));
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
