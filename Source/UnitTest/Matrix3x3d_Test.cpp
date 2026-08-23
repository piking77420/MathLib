#include <gtest/gtest.h>

#include <MathLibHeader.hpp>
#include <Matrix3x3d.hpp>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

using namespace MathLib;

TEST(TestMatrix3x3d, constructor)
{
    {
        // clang-format off
        const Matrix3x3d m(1.0, 2.0, 3.0, 
                           4.0, 5.0, 6.0,
                           7.0, 8.0,9.0);
        // clang-format on
        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 3.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 5.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 6.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 7.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 8.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 9.0);
    }

    {
        // clang-format off
        const Matrix3x3d m(Vector3d(1.0, 2.0, 3.0), 
                           Vector3d(4.0, 5.0, 6.0),
                           Vector3d(7.0, 8.0, 9.0));
        // clang-format on
        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 3.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 5.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 6.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 7.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 8.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 9.0);
    }
}

TEST(TestMatrix3x3d, identity)
{
    const Matrix3x3d m = Matrix3x3d::identity();

    EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
    EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
    EXPECT_DOUBLE_EQ(m.getM13(), 0.0);

    EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
    EXPECT_DOUBLE_EQ(m.getM22(), 1.0);
    EXPECT_DOUBLE_EQ(m.getM23(), 0.0);

    EXPECT_DOUBLE_EQ(m.getM31(), 0.0);
    EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
    EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
}

TEST(TestMatrix3x3d, setter)
{
    Matrix3x3d m;
    m.setM11(1.0) //
        .setM12(2.0)
        .setM13(3.0)
        .setM21(4.0) //
        .setM22(5.0)
        .setM23(6.0)
        .setM31(7.0) //
        .setM32(8.0)
        .setM33(9.0);

    EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
    EXPECT_DOUBLE_EQ(m.getM12(), 2.0);
    EXPECT_DOUBLE_EQ(m.getM13(), 3.0);

    EXPECT_DOUBLE_EQ(m.getM21(), 4.0);
    EXPECT_DOUBLE_EQ(m.getM22(), 5.0);
    EXPECT_DOUBLE_EQ(m.getM23(), 6.0);

    EXPECT_DOUBLE_EQ(m.getM31(), 7.0);
    EXPECT_DOUBLE_EQ(m.getM32(), 8.0);
    EXPECT_DOUBLE_EQ(m.getM33(), 9.0);
}

TEST(TestMatrix3x3d, transpose)
{
    // Transposing identity does not change anything.
    {
        const Matrix3x3d m = Matrix3x3d::identity().transpose();

        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
    }

    // Transpose swaps rows and columns.
    {
        // clang-format off

        const Matrix3x3d m = Matrix3x3d(1.0, 2.0, 3.0, 
                                        4.0, 5.0, 6.0, 
                                        7.0, 8.0, 9.0).transpose();
        // clang-format on

        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 7.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 5.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 8.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 6.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 9.0);
    }
}

TEST(TestMatrix3x3d, getTranspose)
{
    // Transposing identity does not change anything.
    {
        const Matrix3x3d m = Matrix3x3d::identity().getTranspose();

        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
    }

    // Transpose swaps rows and columns.
    {
        // clang-format off

        const Matrix3x3d m = Matrix3x3d(1.0, 2.0, 3.0, 
                                        4.0, 5.0, 6.0, 
                                        7.0, 8.0, 9.0).getTranspose();
        // clang-format on

        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 7.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 5.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 8.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 6.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 9.0);
    }
}

TEST(TestMatrix3x3d, determinant)
{
    // determinant of identity => 1.0
    {
        const double value = Matrix3x3d::identity().determinant();
        EXPECT_DOUBLE_EQ(value, 1.0);
    }

    // determinant of zero matrix => 0.0
    {
        const Matrix3x3d m(Vector3d::zero(), Vector3d::zero(), Vector3d::zero());

        EXPECT_DOUBLE_EQ(m.determinant(), 0.0);
    }

    // determinant of non-trivial matrix => 1.0
    {
        const Matrix3x3d m(Vector3d(1.0, 2.0, 3.0), Vector3d(0.0, 1.0, 4.0), Vector3d(5.0, 6.0, 0.0));

        EXPECT_DOUBLE_EQ(m.determinant(), 1.0);
    }

    // determinant of non-trivial matrix => -306.0
    {
        const Matrix3x3d m(Vector3d(6.0, 1.0, 1.0), Vector3d(4.0, -2.0, 5.0), Vector3d(2.0, 8.0, 7.0));

        EXPECT_DOUBLE_EQ(m.determinant(), -306.0);
    }

    // linearly dependent rows => determinant 0.0
    {
        const Matrix3x3d m(Vector3d(1.0, 2.0, 3.0), Vector3d(2.0, 4.0, 6.0), Vector3d(4.0, 5.0, 6.0));

        EXPECT_DOUBLE_EQ(m.determinant(), 0.0);
    }
}

TEST(TestMatrix3x3d, inverse)
{
    // inverse of identity => identity
    {
        Matrix3x3d m = Matrix3x3d::identity();
        m.inverse();

        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
    }

    // inverse of diagonal matrix
    {
        Matrix3x3d m(Vector3d(2.0, 0.0, 0.0), Vector3d(0.0, 4.0, 0.0), Vector3d(0.0, 0.0, 5.0));

        m.inverse();

        EXPECT_DOUBLE_EQ(m.getM11(), 0.5);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 0.25);
        EXPECT_DOUBLE_EQ(m.getM23(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 0.2);
    }

    // inverse of non-trivial matrix
    {
        // determinant = 1
        //
        // [1 2 3]^-1   [-24  18   5]
        // [0 1 4]    = [ 20 -15  -4]
        // [5 6 0]      [ -5   4   1]
        Matrix3x3d m(Vector3d(1.0, 2.0, 3.0), Vector3d(0.0, 1.0, 4.0), Vector3d(5.0, 6.0, 0.0));

        m.inverse();

        EXPECT_DOUBLE_EQ(m.getM11(), -24.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 18.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 5.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 20.0);
        EXPECT_DOUBLE_EQ(m.getM22(), -15.0);
        EXPECT_DOUBLE_EQ(m.getM23(), -4.0);

        EXPECT_DOUBLE_EQ(m.getM31(), -5.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
    }

    // singular matrix => inverse leaves matrix unchanged
    {
        Matrix3x3d m(Vector3d(1.0, 2.0, 3.0), Vector3d(2.0, 4.0, 6.0), Vector3d(3.0, 6.0, 9.0));

        m.inverse();

        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 3.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 6.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 6.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 9.0);
    }
}

TEST(TestMatrix3x3d, getInverse)
{
    // inverse of identity => identity
    {
        Matrix3x3d m = Matrix3x3d::identity().getInverse();

        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
    }

    // inverse of diagonal matrix
    {
        Matrix3x3d m =
            Matrix3x3d(Vector3d(2.0, 0.0, 0.0), Vector3d(0.0, 4.0, 0.0), Vector3d(0.0, 0.0, 5.0)).getInverse();

        EXPECT_DOUBLE_EQ(m.getM11(), 0.5);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 0.25);
        EXPECT_DOUBLE_EQ(m.getM23(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 0.2);
    }

    // inverse of non-trivial matrix
    {
        // determinant = 1
        //
        // [1 2 3]^-1   [-24  18   5]
        // [0 1 4]    = [ 20 -15  -4]
        // [5 6 0]      [ -5   4   1]
        Matrix3x3d m =
            Matrix3x3d(Vector3d(1.0, 2.0, 3.0), Vector3d(0.0, 1.0, 4.0), Vector3d(5.0, 6.0, 0.0)).getInverse();

        EXPECT_DOUBLE_EQ(m.getM11(), -24.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 18.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 5.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 20.0);
        EXPECT_DOUBLE_EQ(m.getM22(), -15.0);
        EXPECT_DOUBLE_EQ(m.getM23(), -4.0);

        EXPECT_DOUBLE_EQ(m.getM31(), -5.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
    }

    // singular matrix => inverse leaves matrix unchanged
    {
        Matrix3x3d m =
            Matrix3x3d(Vector3d(1.0, 2.0, 3.0), Vector3d(2.0, 4.0, 6.0), Vector3d(3.0, 6.0, 9.0)).getInverse();

        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 3.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 6.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 6.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 9.0);
    }
}

TEST(TestMatrix3x3d, addScalarOperator)
{
    {
        Matrix3x3d m(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

        m += 10.0;

        EXPECT_DOUBLE_EQ(m.getM11(), 11.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 12.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 13.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 14.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 15.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 16.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 18.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 19.0);
    }

    {
        const Matrix3x3d m = Matrix3x3d(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0) + 10.0;

        EXPECT_DOUBLE_EQ(m.getM11(), 11.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 12.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 13.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 14.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 15.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 16.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 18.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 19.0);
    }
}

TEST(TestMatrix3x3d, subScalarOperator)
{
    {
        Matrix3x3d m(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

        m -= 10.0;

        EXPECT_DOUBLE_EQ(m.getM11(), -9.0);
        EXPECT_DOUBLE_EQ(m.getM12(), -8.0);
        EXPECT_DOUBLE_EQ(m.getM13(), -7.0);

        EXPECT_DOUBLE_EQ(m.getM21(), -6.0);
        EXPECT_DOUBLE_EQ(m.getM22(), -5.0);
        EXPECT_DOUBLE_EQ(m.getM23(), -4.0);

        EXPECT_DOUBLE_EQ(m.getM31(), -3.0);
        EXPECT_DOUBLE_EQ(m.getM32(), -2.0);
        EXPECT_DOUBLE_EQ(m.getM33(), -1.0);
    }

    {
        const Matrix3x3d m = Matrix3x3d(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0) - 10.0;

        EXPECT_DOUBLE_EQ(m.getM11(), -9.0);
        EXPECT_DOUBLE_EQ(m.getM12(), -8.0);
        EXPECT_DOUBLE_EQ(m.getM13(), -7.0);

        EXPECT_DOUBLE_EQ(m.getM21(), -6.0);
        EXPECT_DOUBLE_EQ(m.getM22(), -5.0);
        EXPECT_DOUBLE_EQ(m.getM23(), -4.0);

        EXPECT_DOUBLE_EQ(m.getM31(), -3.0);
        EXPECT_DOUBLE_EQ(m.getM32(), -2.0);
        EXPECT_DOUBLE_EQ(m.getM33(), -1.0);
    }
}

TEST(TestMatrix3x3d, mulScalarOperator)
{
    {
        Matrix3x3d m(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

        m *= 10.0;

        EXPECT_DOUBLE_EQ(m.getM11(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 20.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 30.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 40.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 50.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 60.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 70.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 80.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 90.0);
    }

    {
        const Matrix3x3d m = Matrix3x3d(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0) * 10.0;

        EXPECT_DOUBLE_EQ(m.getM11(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 20.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 30.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 40.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 50.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 60.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 70.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 80.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 90.0);
    }
}

TEST(TestMatrix3x3d, divScalarOperator)
{
    {
        Matrix3x3d m(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

        m /= 10.0;

        EXPECT_DOUBLE_EQ(m.getM11(), 0.1);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.2);
        EXPECT_DOUBLE_EQ(m.getM13(), 0.3);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.4);
        EXPECT_DOUBLE_EQ(m.getM22(), 0.5);
        EXPECT_DOUBLE_EQ(m.getM23(), 0.6);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.7);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.8);
        EXPECT_DOUBLE_EQ(m.getM33(), 0.9);
    }

    {
        const Matrix3x3d m = Matrix3x3d(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0) / 10.0;

        EXPECT_DOUBLE_EQ(m.getM11(), 0.1);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.2);
        EXPECT_DOUBLE_EQ(m.getM13(), 0.3);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.4);
        EXPECT_DOUBLE_EQ(m.getM22(), 0.5);
        EXPECT_DOUBLE_EQ(m.getM23(), 0.6);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.7);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.8);
        EXPECT_DOUBLE_EQ(m.getM33(), 0.9);
    }
}

TEST(TestMatrix3x3d, addMatrixOperator)
{
    const Matrix3x3d m1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

    const Matrix3x3d m2(9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0);

    {
        Matrix3x3d m = m1;
        m += m2;

        EXPECT_DOUBLE_EQ(m.getM11(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 10.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 10.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 10.0);
    }

    {
        const Matrix3x3d m = m1 + m2;

        EXPECT_DOUBLE_EQ(m.getM11(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 10.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 10.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 10.0);
    }
}

TEST(TestMatrix3x3d, subMatrixOperator)
{
    const Matrix3x3d m1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

    const Matrix3x3d m2(9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0);

    {
        Matrix3x3d m = m1;
        m -= m2;

        EXPECT_DOUBLE_EQ(m.getM11(), -8.0);
        EXPECT_DOUBLE_EQ(m.getM12(), -6.0);
        EXPECT_DOUBLE_EQ(m.getM13(), -4.0);

        EXPECT_DOUBLE_EQ(m.getM21(), -2.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 2.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 6.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 8.0);
    }

    {
        const Matrix3x3d m = m1 - m2;

        EXPECT_DOUBLE_EQ(m.getM11(), -8.0);
        EXPECT_DOUBLE_EQ(m.getM12(), -6.0);
        EXPECT_DOUBLE_EQ(m.getM13(), -4.0);

        EXPECT_DOUBLE_EQ(m.getM21(), -2.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 2.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 6.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 8.0);
    }
}

TEST(TestMatrix3x3d, mulMatrixOperator)
{
    const Matrix3x3d m1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

    const Matrix3x3d m2(9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0);

    {
        Matrix3x3d m = m1;
        m *= m2;

        EXPECT_DOUBLE_EQ(m.getM11(), 30.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 24.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 18.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 84.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 69.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 54.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 138.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 114.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 90.0);
    }

    {
        const Matrix3x3d m = m1 * m2;

        EXPECT_DOUBLE_EQ(m.getM11(), 30.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 24.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 18.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 84.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 69.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 54.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 138.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 114.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 90.0);
    }
}

TEST(TestMatrix3x3d, cmpOperator)
{
    {
        const Matrix3x3d m1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

        const Matrix3x3d m2 = Matrix3x3d::identity();

        EXPECT_TRUE(m1 == m1);
        EXPECT_FALSE(m1 == m2);
        EXPECT_FALSE(m1 != m1);
        EXPECT_TRUE(m1 != m2);
    }

    constexpr double DoubleEpsilonHalf = 0.5 * DoubleEpsilon;
    constexpr double DoubleEpsilon2 = 2.0 * DoubleEpsilon;

    {
        const Matrix3x3d m1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

        const Matrix3x3d m2(1.0 - DoubleEpsilonHalf, 2.0 - DoubleEpsilonHalf, 3.0 - DoubleEpsilonHalf,
                            4.0 - DoubleEpsilonHalf, 5.0 - DoubleEpsilonHalf, 6.0 - DoubleEpsilonHalf,
                            7.0 - DoubleEpsilonHalf, 8.0 - DoubleEpsilonHalf, 9.0 - DoubleEpsilonHalf);

        EXPECT_TRUE(m1 == m2);
        EXPECT_FALSE(m1 != m2);
    }

    {
        const Matrix3x3d m1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

        const Matrix3x3d m2(1.0 - DoubleEpsilon2, 2.0 - DoubleEpsilon2, 3.0 - DoubleEpsilon2, 4.0 - DoubleEpsilon2,
                            5.0 - DoubleEpsilon2, 6.0 - DoubleEpsilon2, 7.0 - DoubleEpsilon2, 8.0 - DoubleEpsilon2,
                            9.0 - DoubleEpsilon2);

        EXPECT_TRUE(m1 != m2);
        EXPECT_FALSE(m1 == m2);
    }
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
