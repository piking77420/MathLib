#include <gtest/gtest.h>

#include <numbers>

#include <MathLibHeader.hpp>
#include <MatrixTransformation.hpp>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

using namespace MathLib;

TEST(TestMatrix4x4d, constructor)
{
    {
        // clang-format off
        const Matrix4x4d m(1.0, 2.0, 3.0, 4.0, 
                           5.0, 6.0, 7.0, 8.0,
                           9.0, 10.0, 11.0, 12.0,
                           13.0, 14.0, 15.0, 16.0);
        // clang-format on
        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 4.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 5.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 6.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 7.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 8.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 9.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 11.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 12.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 13.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 14.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 15.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 16.0);
    }

    {
        // clang-format off
        const Matrix4x4d m(Vector4d(1.0, 2.0, 3.0, 4.0), 
                           Vector4d(5.0, 6.0, 7.0, 8.0),
                           Vector4d(9.0, 10.0, 11.0, 12.0),
                           Vector4d(13.0, 14.0, 15.0, 16.0));
        // clang-format on
        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 4.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 5.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 6.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 7.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 8.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 9.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 11.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 12.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 13.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 14.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 15.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 16.0);
    }
}

TEST(TestMatrix4x4d, identity)
{
    const Matrix4x4d m = Matrix4x4d::identity();

    EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
    EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
    EXPECT_DOUBLE_EQ(m.getM13(), 0.0);
    EXPECT_DOUBLE_EQ(m.getM14(), 0.0);

    EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
    EXPECT_DOUBLE_EQ(m.getM22(), 1.0);
    EXPECT_DOUBLE_EQ(m.getM23(), 0.0);
    EXPECT_DOUBLE_EQ(m.getM24(), 0.0);

    EXPECT_DOUBLE_EQ(m.getM31(), 0.0);
    EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
    EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
    EXPECT_DOUBLE_EQ(m.getM34(), 0.0);

    EXPECT_DOUBLE_EQ(m.getM41(), 0.0);
    EXPECT_DOUBLE_EQ(m.getM42(), 0.0);
    EXPECT_DOUBLE_EQ(m.getM43(), 0.0);
    EXPECT_DOUBLE_EQ(m.getM44(), 1.0);
}

TEST(TestMatrix4x4d, setter)
{
    Matrix4x4d m = Matrix4x4d::zero();
    m.setM11(1.0) //
        .setM12(2.0)
        .setM13(3.0)
        .setM14(4.0)
        .setM21(5.0) //
        .setM22(6.0)
        .setM23(7.0)
        .setM24(8.0)
        .setM31(9.0) //
        .setM32(10.0)
        .setM33(11.0)
        .setM34(12.0)
        .setM41(13.0) //
        .setM42(14.0)
        .setM43(15.0)
        .setM44(16.0);

    EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
    EXPECT_DOUBLE_EQ(m.getM12(), 2.0);
    EXPECT_DOUBLE_EQ(m.getM13(), 3.0);
    EXPECT_DOUBLE_EQ(m.getM14(), 4.0);

    EXPECT_DOUBLE_EQ(m.getM21(), 5.0);
    EXPECT_DOUBLE_EQ(m.getM22(), 6.0);
    EXPECT_DOUBLE_EQ(m.getM23(), 7.0);
    EXPECT_DOUBLE_EQ(m.getM24(), 8.0);

    EXPECT_DOUBLE_EQ(m.getM31(), 9.0);
    EXPECT_DOUBLE_EQ(m.getM32(), 10.0);
    EXPECT_DOUBLE_EQ(m.getM33(), 11.0);
    EXPECT_DOUBLE_EQ(m.getM34(), 12.0);

    EXPECT_DOUBLE_EQ(m.getM41(), 13.0);
    EXPECT_DOUBLE_EQ(m.getM42(), 14.0);
    EXPECT_DOUBLE_EQ(m.getM43(), 15.0);
    EXPECT_DOUBLE_EQ(m.getM44(), 16.0);
}

TEST(TestMatrix4x4d, transpose)
{
    // Transposing identity does not change anything.
    {
        const Matrix4x4d m = Matrix4x4d::identity().transpose();

        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 1.0);
    }

    // Transpose swaps rows and columns.
    {
        // clang-format off

        const Matrix4x4d m = Matrix4x4d(1.0, 2.0, 3.0, 4.0, 
                                        5.0, 6.0, 7.0, 8.0, 
                                        9.0, 10.0, 11.0, 12.0,
                                        13.0, 14.0, 15.0, 16.0).transpose();
        // clang-format on

        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 5.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 9.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 13.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 6.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 14.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 7.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 11.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 15.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 8.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 12.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 16.0);
    }
}

TEST(TestMatrix4x4d, getTranspose)
{
    // Transposing identity does not change anything.
    {
        const Matrix4x4d m = Matrix4x4d::identity().getTranspose();

        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 1.0);
    }

    // Transpose swaps rows and columns.
    {
        // clang-format off

        const Matrix4x4d m = Matrix4x4d(1.0, 2.0, 3.0, 4.0, 
                                        5.0, 6.0, 7.0, 8.0, 
                                        9.0, 10.0, 11.0, 12.0,
                                        13.0, 14.0, 15.0, 16.0).getTranspose();
        // clang-format on

        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 5.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 9.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 13.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 6.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 14.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 7.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 11.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 15.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 8.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 12.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 16.0);
    }
}

TEST(TestMatrix4x4d, determinant)
{
    // determinant of identity => 1.0
    {
        const double value = Matrix4x4d::identity().determinant();
        EXPECT_DOUBLE_EQ(value, 1.0);
    }

    // determinant of zero matrix => 0.0
    {
        const Matrix4x4d m(Vector4d::zero(), Vector4d::zero(), Vector4d::zero(), Vector4d::zero());

        EXPECT_DOUBLE_EQ(m.determinant(), 0.0);
    }

    // determinant of diagonal matrix => product of diagonal = 120.0
    {
        // clang-format off
        const Matrix4x4d m(Vector4d(2.0, 0.0, 0.0, 0.0), 
                           Vector4d(0.0, 3.0, 0.0, 0.0), 
                           Vector4d(0.0, 0.0, 4.0, 0.0),
                           Vector4d(0.0, 0.0, 0.0, 5.0));
        // clang-format on

        EXPECT_DOUBLE_EQ(m.determinant(), 120.0);
    }

    // determinant of non-trivial matrix => 72.0
    {
        // clang-format off
        const Matrix4x4d m(Vector4d(1.0, 2.0, 3.0, 4.0), 
                           Vector4d(5.0, 6.0, 7.0, 8.0),
                           Vector4d(2.0, 6.0, 4.0, 8.0),
                           Vector4d(3.0, 1.0, 1.0, 2.0));
        // clang-format on
        EXPECT_DOUBLE_EQ(m.determinant(), 72.0);
    }

    // upper triangular matrix => product of diagonal = -24.0
    {
        // clang-format off
        const Matrix4x4d m(Vector4d(1.0, 2.0, 3.0, 4.0), 
                           Vector4d(0.0, -2.0, 5.0, 6.0), 
                           Vector4d(0.0, 0.0, 3.0, 7.0),
                           Vector4d(0.0, 0.0, 0.0, 4.0));
        // clang-format on

        EXPECT_DOUBLE_EQ(m.determinant(), -24.0);
    }

    // linearly dependent rows => determinant 0.0
    {
        // clang-format off
        const Matrix4x4d m(Vector4d(1.0, 2.0, 3.0, 4.0), 
                           Vector4d(2.0, 4.0, 6.0, 8.0), 
                           Vector4d(5.0, 6.0, 7.0, 8.0),
                           Vector4d(9.0, 10.0, 11.0, 12.0));
        // clang-format on
        EXPECT_DOUBLE_EQ(m.determinant(), 0.0);
    }
}

TEST(TestMatrix4x4d, inverse)
{
    // inverse of identity => identity
    {
        Matrix4x4d m = Matrix4x4d::identity();
        m.inverse();

        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 1.0);
    }

    // inverse of diagonal matrix
    {
        // clang-format off
        Matrix4x4d m(Vector4d(2.0, 0.0, 0.0, 0.0), 
                     Vector4d(0.0, 4.0, 0.0, 0.0), 
                     Vector4d(0.0, 0.0, 5.0, 0.0),
                     Vector4d(0.0, 0.0, 0.0, 10.0));
        // clang-format on
        m.inverse();

        EXPECT_DOUBLE_EQ(m.getM11(), 0.5);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 0.25);
        EXPECT_DOUBLE_EQ(m.getM23(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 0.2);
        EXPECT_DOUBLE_EQ(m.getM34(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 0.1);
    }

    // inverse of non-trivial matrix
    {
        // determinant = 1
        //
        // [1 2 3 4]^-1   [-24  18   5 -29]
        // [0 1 4 5]    = [ 20 -15  -4  23]
        // [5 6 0 7]      [ -5   4   1  -7]
        // [0 0 0 1]      [  0   0   0   1]
        // clang-format off
        Matrix4x4d m(Vector4d(1.0, 2.0, 3.0, 4.0), 
                     Vector4d(0.0, 1.0, 4.0, 5.0), 
                     Vector4d(5.0, 6.0, 0.0, 7.0),
                     Vector4d(0.0, 0.0, 0.0, 1.0));
        // clang-format on
        m.inverse();

        EXPECT_DOUBLE_EQ(m.getM11(), -24.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 18.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 5.0);
        EXPECT_DOUBLE_EQ(m.getM14(), -29.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 20.0);
        EXPECT_DOUBLE_EQ(m.getM22(), -15.0);
        EXPECT_DOUBLE_EQ(m.getM23(), -4.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 23.0);

        EXPECT_DOUBLE_EQ(m.getM31(), -5.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM34(), -7.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 1.0);
    }

    // singular matrix => inverse leaves matrix unchanged
    {
        // clang-format off
        Matrix4x4d m(Vector4d(1.0, 2.0, 3.0, 4.0), 
                     Vector4d(2.0, 4.0, 6.0, 8.0), 
                     Vector4d(3.0, 6.0, 9.0, 12.0),
                     Vector4d(4.0, 8.0, 12.0, 16.0));
        // clang-format on
        m.inverse();

        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 4.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 6.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 8.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 6.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 9.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 12.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 8.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 12.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 16.0);
    }
}

TEST(TestMatrix4x4d, getInverse)
{
    // inverse of identity => identity
    {
        const Matrix4x4d m = Matrix4x4d::identity().getInverse();

        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 1.0);
    }

    // inverse of diagonal matrix
    {
        // clang-format off
        const Matrix4x4d m = Matrix4x4d(Vector4d(2.0, 0.0, 0.0, 0.0), 
                                        Vector4d(0.0, 4.0, 0.0, 0.0),
                                        Vector4d(0.0, 0.0, 5.0, 0.0),
                                        Vector4d(0.0, 0.0, 0.0, 10.0))
                                 .getInverse();
        // clang-format on
        EXPECT_DOUBLE_EQ(m.getM11(), 0.5);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 0.25);
        EXPECT_DOUBLE_EQ(m.getM23(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 0.2);
        EXPECT_DOUBLE_EQ(m.getM34(), 0.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 0.1);
    }

    // inverse of non-trivial matrix
    {
        // determinant = 1
        //
        // [1 2 3 4]^-1   [-24  18   5 -29]
        // [0 1 4 5]    = [ 20 -15  -4  23]
        // [5 6 0 7]      [ -5   4   1  -7]
        // [0 0 0 1]      [  0   0   0   1]
        // clang-format off
        const Matrix4x4d m = Matrix4x4d(Vector4d(1.0, 2.0, 3.0, 4.0), 
                                        Vector4d(0.0, 1.0, 4.0, 5.0),
                                        Vector4d(5.0, 6.0, 0.0, 7.0), 
                                        Vector4d(0.0, 0.0, 0.0, 1.0))
                                 .getInverse();
        // clang-format on
        EXPECT_DOUBLE_EQ(m.getM11(), -24.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 18.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 5.0);
        EXPECT_DOUBLE_EQ(m.getM14(), -29.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 20.0);
        EXPECT_DOUBLE_EQ(m.getM22(), -15.0);
        EXPECT_DOUBLE_EQ(m.getM23(), -4.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 23.0);

        EXPECT_DOUBLE_EQ(m.getM31(), -5.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM34(), -7.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 1.0);
    }

    // singular matrix => inverse leaves matrix unchanged
    {
        // clang-format off
        Matrix4x4d m = Matrix4x4d(Vector4d(1.0, 2.0, 3.0, 4.0), 
                                  Vector4d(2.0, 4.0, 6.0, 8.0),
                                  Vector4d(3.0, 6.0, 9.0, 12.0),
                                  Vector4d(4.0, 8.0, 12.0, 16.0))
                           .getInverse();
        // clang-format on

        EXPECT_DOUBLE_EQ(m.getM11(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 4.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 2.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 6.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 8.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 6.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 9.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 12.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 8.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 12.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 16.0);
    }
}

TEST(TestMatrix4x4d, addScalarOperator)
{
    {
        // clang-format off
        Matrix4x4d m(1.0, 2.0, 3.0, 4.0, 
                    5.0, 6.0, 7.0, 8.0, 
                    9.0, 10.0, 11.0, 12.0, 
                    13.0, 14.0, 15.0, 16.0);
        // clang-format on
        m += 10.0;

        EXPECT_DOUBLE_EQ(m.getM11(), 11.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 12.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 13.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 14.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 15.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 16.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 18.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 19.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 20.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 21.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 22.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 23.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 24.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 25.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 26.0);
    }

    {
        // clang-format off
        const Matrix4x4d m =
            Matrix4x4d(1.0, 2.0, 3.0, 4.0, 
                       5.0, 6.0, 7.0, 8.0,
                       9.0, 10.0, 11.0, 12.0,
                       13.0, 14.0, 15.0, 16.0) + 10.0;
        // clang-format on

        EXPECT_DOUBLE_EQ(m.getM11(), 11.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 12.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 13.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 14.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 15.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 16.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 18.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 19.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 20.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 21.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 22.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 23.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 24.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 25.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 26.0);
    }
}

TEST(TestMatrix4x4d, subScalarOperator)
{
    {
        // clang-format off
        Matrix4x4d m(1.0, 2.0, 3.0, 4.0, 
                     5.0, 6.0, 7.0, 8.0, 
                     9.0, 10.0, 11.0, 12.0, 
                     13.0, 14.0, 15.0, 16.0);
        // clang-format on
        m -= 10.0;

        EXPECT_DOUBLE_EQ(m.getM11(), -9.0);
        EXPECT_DOUBLE_EQ(m.getM12(), -8.0);
        EXPECT_DOUBLE_EQ(m.getM13(), -7.0);
        EXPECT_DOUBLE_EQ(m.getM14(), -6.0);

        EXPECT_DOUBLE_EQ(m.getM21(), -5.0);
        EXPECT_DOUBLE_EQ(m.getM22(), -4.0);
        EXPECT_DOUBLE_EQ(m.getM23(), -3.0);
        EXPECT_DOUBLE_EQ(m.getM24(), -2.0);

        EXPECT_DOUBLE_EQ(m.getM31(), -1.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 2.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 5.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 6.0);
    }

    {
        // clang-format off
        const Matrix4x4d m =
            Matrix4x4d(1.0, 2.0, 3.0, 4.0, 
                       5.0, 6.0, 7.0, 8.0, 
                       9.0, 10.0, 11.0, 12.0, 
                       13.0, 14.0, 15.0, 16.0) - 10.0;
        // clang-format on

        EXPECT_DOUBLE_EQ(m.getM11(), -9.0);
        EXPECT_DOUBLE_EQ(m.getM12(), -8.0);
        EXPECT_DOUBLE_EQ(m.getM13(), -7.0);
        EXPECT_DOUBLE_EQ(m.getM14(), -6.0);

        EXPECT_DOUBLE_EQ(m.getM21(), -5.0);
        EXPECT_DOUBLE_EQ(m.getM22(), -4.0);
        EXPECT_DOUBLE_EQ(m.getM23(), -3.0);
        EXPECT_DOUBLE_EQ(m.getM24(), -2.0);

        EXPECT_DOUBLE_EQ(m.getM31(), -1.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 0.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 2.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 4.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 5.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 6.0);
    }
}

TEST(TestMatrix4x4d, mulScalarOperator)
{
    {
        // clang-format off
        Matrix4x4d m(1.0, 2.0, 3.0, 4.0, 
                     5.0, 6.0, 7.0, 8.0,
                     9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);
        // clang-format on
        m *= 10.0;

        EXPECT_DOUBLE_EQ(m.getM11(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 20.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 30.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 40.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 50.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 60.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 70.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 80.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 90.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 100.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 110.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 120.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 130.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 140.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 150.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 160.0);
    }

    {
        // clang-format off
        const Matrix4x4d m =
            Matrix4x4d(1.0, 2.0, 3.0, 4.0, 
                       5.0, 6.0, 7.0, 8.0,
                       9.0, 10.0, 11.0, 12.0, 
                      13.0, 14.0, 15.0, 16.0) * 10.0;
        // clang-format on

        EXPECT_DOUBLE_EQ(m.getM11(), 10.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 20.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 30.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 40.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 50.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 60.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 70.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 80.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 90.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 100.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 110.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 120.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 130.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 140.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 150.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 160.0);
    }
}

TEST(TestMatrix4x4d, divScalarOperator)
{
    {
        // clang-format off
        Matrix4x4d m(1.0, 2.0, 3.0, 4.0, 
                     5.0, 6.0, 7.0, 8.0, 
                     9.0, 10.0, 11.0, 12.0, 
                     13.0, 14.0, 15.0, 16.0);
        // clang-format on
        m /= 10.0;

        EXPECT_DOUBLE_EQ(m.getM11(), 0.1);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.2);
        EXPECT_DOUBLE_EQ(m.getM13(), 0.3);
        EXPECT_DOUBLE_EQ(m.getM14(), 0.4);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.5);
        EXPECT_DOUBLE_EQ(m.getM22(), 0.6);
        EXPECT_DOUBLE_EQ(m.getM23(), 0.7);
        EXPECT_DOUBLE_EQ(m.getM24(), 0.8);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.9);
        EXPECT_DOUBLE_EQ(m.getM32(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.1);
        EXPECT_DOUBLE_EQ(m.getM34(), 1.2);

        EXPECT_DOUBLE_EQ(m.getM41(), 1.3);
        EXPECT_DOUBLE_EQ(m.getM42(), 1.4);
        EXPECT_DOUBLE_EQ(m.getM43(), 1.5);
        EXPECT_DOUBLE_EQ(m.getM44(), 1.6);
    }

    {
        // clang-format off
        const Matrix4x4d m = Matrix4x4d(1.0, 2.0, 3.0, 4.0, 
                                        5.0, 6.0, 7.0, 8.0, 
                                        9.0, 10.0, 11.0, 12.0, 
                                        13.0, 14.0, 15.0, 16.0) / 10.0;
        // clang-format on
        EXPECT_DOUBLE_EQ(m.getM11(), 0.1);
        EXPECT_DOUBLE_EQ(m.getM12(), 0.2);
        EXPECT_DOUBLE_EQ(m.getM13(), 0.3);
        EXPECT_DOUBLE_EQ(m.getM14(), 0.4);

        EXPECT_DOUBLE_EQ(m.getM21(), 0.5);
        EXPECT_DOUBLE_EQ(m.getM22(), 0.6);
        EXPECT_DOUBLE_EQ(m.getM23(), 0.7);
        EXPECT_DOUBLE_EQ(m.getM24(), 0.8);

        EXPECT_DOUBLE_EQ(m.getM31(), 0.9);
        EXPECT_DOUBLE_EQ(m.getM32(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 1.1);
        EXPECT_DOUBLE_EQ(m.getM34(), 1.2);

        EXPECT_DOUBLE_EQ(m.getM41(), 1.3);
        EXPECT_DOUBLE_EQ(m.getM42(), 1.4);
        EXPECT_DOUBLE_EQ(m.getM43(), 1.5);
        EXPECT_DOUBLE_EQ(m.getM44(), 1.6);
    }
}

TEST(TestMatrix4x4d, addMatrixOperator)
{
    // clang-format off
    const Matrix4x4d m1(1.0, 2.0, 3.0, 4.0, 
                        5.0, 6.0, 7.0, 8.0, 
                        9.0, 10.0, 11.0, 12.0, 
                        13.0, 14.0, 15.0, 16.0);

    const Matrix4x4d m2(16.0, 15.0, 14.0, 13.0, 
                        12.0, 11.0, 10.0, 9.0, 
                        8.0, 7.0, 6.0, 5.0, 
                        4.0, 3.0, 2.0, 1.0);
    // clang-format on

    {
        Matrix4x4d m = m1;
        m += m2;

        EXPECT_DOUBLE_EQ(m.getM11(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 17.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 17.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 17.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 17.0);
    }

    {
        const Matrix4x4d m = m1 + m2;

        EXPECT_DOUBLE_EQ(m.getM11(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 17.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 17.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 17.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 17.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 17.0);
    }
}

TEST(TestMatrix4x4d, subMatrixOperator)
{
    // clang-format off

    const Matrix4x4d m1(1.0, 2.0, 3.0, 4.0, 
                        5.0, 6.0, 7.0, 8.0,
                        9.0, 10.0, 11.0, 12.0,
                        13.0, 14.0, 15.0, 16.0);

    const Matrix4x4d m2(16.0, 15.0, 14.0, 13.0, 
                        12.0, 11.0, 10.0, 9.0, 
                        8.0, 7.0, 6.0, 5.0, 
                        4.0, 3.0, 2.0, 1.0);
    // clang-format on

    {
        Matrix4x4d m = m1;
        m -= m2;

        EXPECT_DOUBLE_EQ(m.getM11(), -15.0);
        EXPECT_DOUBLE_EQ(m.getM12(), -13.0);
        EXPECT_DOUBLE_EQ(m.getM13(), -11.0);
        EXPECT_DOUBLE_EQ(m.getM14(), -9.0);

        EXPECT_DOUBLE_EQ(m.getM21(), -7.0);
        EXPECT_DOUBLE_EQ(m.getM22(), -5.0);
        EXPECT_DOUBLE_EQ(m.getM23(), -3.0);
        EXPECT_DOUBLE_EQ(m.getM24(), -1.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 5.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 7.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 9.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 11.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 13.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 15.0);
    }

    {
        const Matrix4x4d m = m1 - m2;

        EXPECT_DOUBLE_EQ(m.getM11(), -15.0);
        EXPECT_DOUBLE_EQ(m.getM12(), -13.0);
        EXPECT_DOUBLE_EQ(m.getM13(), -11.0);
        EXPECT_DOUBLE_EQ(m.getM14(), -9.0);

        EXPECT_DOUBLE_EQ(m.getM21(), -7.0);
        EXPECT_DOUBLE_EQ(m.getM22(), -5.0);
        EXPECT_DOUBLE_EQ(m.getM23(), -3.0);
        EXPECT_DOUBLE_EQ(m.getM24(), -1.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 1.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 3.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 5.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 7.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 9.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 11.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 13.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 15.0);
    }
}

TEST(TestMatrix4x4d, mulMatrixOperator)
{
    // clang-format off
    const Matrix4x4d m1(1.0, 2.0, 3.0, 4.0,
                        5.0, 6.0, 7.0, 8.0, 
                        9.0, 10.0, 11.0, 12.0, 
                        13.0, 14.0, 15.0, 16.0);

    const Matrix4x4d m2(16.0, 15.0, 14.0, 13.0, 
                        12.0, 11.0, 10.0, 9.0,
                        8.0, 7.0, 6.0, 5.0, 
                        4.0, 3.0, 2.0, 1.0);
    // clang-format on
    {
        Matrix4x4d m = m1;
        m *= m2;

        EXPECT_DOUBLE_EQ(m.getM11(), 80.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 70.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 60.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 50.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 240.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 214.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 188.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 162.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 400.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 358.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 316.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 274.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 560.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 502.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 444.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 386.0);
    }

    {
        const Matrix4x4d m = m1 * m2;

        EXPECT_DOUBLE_EQ(m.getM11(), 80.0);
        EXPECT_DOUBLE_EQ(m.getM12(), 70.0);
        EXPECT_DOUBLE_EQ(m.getM13(), 60.0);
        EXPECT_DOUBLE_EQ(m.getM14(), 50.0);

        EXPECT_DOUBLE_EQ(m.getM21(), 240.0);
        EXPECT_DOUBLE_EQ(m.getM22(), 214.0);
        EXPECT_DOUBLE_EQ(m.getM23(), 188.0);
        EXPECT_DOUBLE_EQ(m.getM24(), 162.0);

        EXPECT_DOUBLE_EQ(m.getM31(), 400.0);
        EXPECT_DOUBLE_EQ(m.getM32(), 358.0);
        EXPECT_DOUBLE_EQ(m.getM33(), 316.0);
        EXPECT_DOUBLE_EQ(m.getM34(), 274.0);

        EXPECT_DOUBLE_EQ(m.getM41(), 560.0);
        EXPECT_DOUBLE_EQ(m.getM42(), 502.0);
        EXPECT_DOUBLE_EQ(m.getM43(), 444.0);
        EXPECT_DOUBLE_EQ(m.getM44(), 386.0);
    }
}

TEST(TestMatrix4x4d, mulVector4Operator)
{
    // clang-format off
    const Matrix4x4d m(1.0,  2.0,  3.0,  4.0,
                       5.0,  6.0,  7.0,  8.0,
                       9.0, 10.0, 11.0, 12.0,
                      13.0, 14.0, 15.0, 16.0);

    const Vector4d v(1.0, 2.0, 3.0, 4.0);
    // clang-format on

    const Vector4d result = m * v;

    EXPECT_DOUBLE_EQ(result.getX(), 30.0);
    EXPECT_DOUBLE_EQ(result.getY(), 70.0);
    EXPECT_DOUBLE_EQ(result.getZ(), 110.0);
    EXPECT_DOUBLE_EQ(result.getW(), 150.0);
}

TEST(TestMatrix4x4d, mulVector3Operator)
{
    // clang-format off
    const Matrix4x4d m(1.0,  2.0,  3.0,  4.0,
                       5.0,  6.0,  7.0,  8.0,
                       9.0, 10.0, 11.0, 12.0,
                      13.0, 14.0, 15.0, 16.0);

    const Vector3d v(1.0, 2.0, 3.0);
    // clang-format on

    const Vector4d result = m * v;

    EXPECT_DOUBLE_EQ(result.getX(), 18.0);
    EXPECT_DOUBLE_EQ(result.getY(), 46.0);
    EXPECT_DOUBLE_EQ(result.getZ(), 74.0);
    EXPECT_DOUBLE_EQ(result.getW(), 102.0);
}

TEST(TestMatrix4x4d, cmpOperator)
{
    {
        // clang-format off
        const Matrix4x4d m1(1.0, 2.0, 3.0, 4.0, 
                            5.0, 6.0, 7.0, 8.0, 
                            9.0, 10.0, 11.0, 12.0,
                            13.0, 14.0, 15.0, 16.0);
        // clang-format on
        const Matrix4x4d m2 = Matrix4x4d::identity();

        EXPECT_TRUE(m1 == m1);
        EXPECT_FALSE(m1 == m2);
        EXPECT_FALSE(m1 != m1);
        EXPECT_TRUE(m1 != m2);
    }

    constexpr double DoubleEpsilonHalf = 0.5 * DoubleEpsilon;
    constexpr double DoubleEpsilon2 = 2.0 * DoubleEpsilon;

    {
        // clang-format off
        const Matrix4x4d m1(1.0, 2.0, 3.0, 4.0, 
                            5.0, 6.0, 7.0, 8.0, 
                            9.0, 10.0, 11.0, 12.0, 
                            13.0, 14.0, 15.0, 16.0);
        // clang-format on
        const Matrix4x4d m2(
            1.0 - DoubleEpsilonHalf, 2.0 - DoubleEpsilonHalf, 3.0 - DoubleEpsilonHalf, 4.0 - DoubleEpsilonHalf,

            5.0 - DoubleEpsilonHalf, 6.0 - DoubleEpsilonHalf, 7.0 - DoubleEpsilonHalf, 8.0 - DoubleEpsilonHalf,

            9.0 - DoubleEpsilonHalf, 10.0 - DoubleEpsilonHalf, 11.0 - DoubleEpsilonHalf, 12.0 - DoubleEpsilonHalf,

            13.0 - DoubleEpsilonHalf, 14.0 - DoubleEpsilonHalf, 15.0 - DoubleEpsilonHalf, 16.0 - DoubleEpsilonHalf);

        EXPECT_TRUE(m1 == m2);
        EXPECT_FALSE(m1 != m2);
    }

    {
        // clang-format off
        const Matrix4x4d m1(1.0, 2.0, 3.0, 4.0, 
                            5.0, 6.0, 7.0, 8.0, 
                            9.0, 10.0, 11.0, 12.0, 
                            13.0, 14.0, 15.0, 16.0);
        // clang-format on
        const Matrix4x4d m2(1.0 - DoubleEpsilon2, 2.0 - DoubleEpsilon2, 3.0 - DoubleEpsilon2, 4.0 - DoubleEpsilon2,

                            5.0 - DoubleEpsilon2, 6.0 - DoubleEpsilon2, 7.0 - DoubleEpsilon2, 8.0 - DoubleEpsilon2,

                            9.0 - DoubleEpsilon2, 10.0 - DoubleEpsilon2, 11.0 - DoubleEpsilon2, 12.0 - DoubleEpsilon2,

                            13.0 - DoubleEpsilon2, 14.0 - DoubleEpsilon2, 15.0 - DoubleEpsilon2, 16.0 - DoubleEpsilon2);

        EXPECT_TRUE(m1 != m2);
        EXPECT_FALSE(m1 == m2);
    }
}

TEST(TestMatrix4x4d, trsEulerAngles)
{
    const Vector3d translation(1.0, 2.0, 3.0);
    const Vector3d rotation(0.0, std::numbers::pi * 0.5, -std::numbers::pi * 0.5);
    const Vector3d scale(3.0, 2.0, 1.0);

    const Matrix4x4d m = MathLib::trs<Matrix4x4d>(translation, rotation, scale);

    EXPECT_NEAR(m.getM11(), 0.0, DoubleEpsilon);
    EXPECT_NEAR(m.getM12(), 2.0, DoubleEpsilon);
    EXPECT_NEAR(m.getM13(), 0.0, DoubleEpsilon);
    EXPECT_NEAR(m.getM14(), 1.0, DoubleEpsilon);

    EXPECT_NEAR(m.getM21(), 0.0, DoubleEpsilon);
    EXPECT_NEAR(m.getM22(), 0.0, DoubleEpsilon);
    EXPECT_NEAR(m.getM23(), -1.0, DoubleEpsilon);
    EXPECT_NEAR(m.getM24(), 2.0, DoubleEpsilon);

    EXPECT_NEAR(m.getM31(), -3.0, DoubleEpsilon);
    EXPECT_NEAR(m.getM32(), 0.0, DoubleEpsilon);
    EXPECT_NEAR(m.getM33(), 0.0, DoubleEpsilon);
    EXPECT_NEAR(m.getM34(), 3.0, DoubleEpsilon);

    EXPECT_NEAR(m.getM41(), 0.0, DoubleEpsilon);
    EXPECT_NEAR(m.getM42(), 0.0, DoubleEpsilon);
    EXPECT_NEAR(m.getM43(), 0.0, DoubleEpsilon);
    EXPECT_NEAR(m.getM44(), 1.0, DoubleEpsilon);
}
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
