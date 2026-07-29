#include <gtest/gtest.h>

#include <Vector4d.hpp>

TEST(TestVec4, Constructor)
{
	MathLib::Vector4d v = MathLib::Vector4d(1., 2., 3., 4.);

	EXPECT_DOUBLE_EQ(v.getX(), 1.0);
    EXPECT_DOUBLE_EQ(v.getY(), 2.0);
    EXPECT_DOUBLE_EQ(v.getZ(), 3.0);
    EXPECT_DOUBLE_EQ(v.getW(), 4.0);
}
