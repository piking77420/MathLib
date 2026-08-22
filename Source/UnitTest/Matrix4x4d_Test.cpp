#include <gtest/gtest.h>

#include <MathLibHeader.hpp>
#include <Matrix4x4d.hpp>

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
    Matrix4x4d m;
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
}

TEST(TestMatrix4x4d, determinant)
{
}

TEST(TestMatrix4x4d, inverse)
{
}

TEST(TestMatrix4x4d, getInverse)
{
}

TEST(TestMatrix4x4d, addScalarOperator)
{
}

TEST(TestMatrix4x4d, subScalarOperator)
{
}

TEST(TestMatrix4x4d, mulScalarOperator)
{
}

TEST(TestMatrix4x4d, divScalarOperator)
{
}

TEST(TestMatrix4x4d, addMatrixOperator)
{
}

TEST(TestMatrix4x4d, subMatrixOperator)
{
}

TEST(TestMatrix4x4d, mulMatrixOperator)
{
}

TEST(TestMatrix4x4d, cmpOperator)
{
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
