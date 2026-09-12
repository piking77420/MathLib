#include <gtest/gtest.h>

#include <span>
#include <numbers>

#include <MathLibHeader.hpp>
#include <MatrixTransformation.hpp>

// Thanks chat-gpt to generate test tbh
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

using namespace MathLib;

TEST(TestQuaterniond, constructor)
{
    {
        const Quaterniond v = Quaterniond(1., 2., 3., 4.);

        EXPECT_DOUBLE_EQ(v.getX(), 1.0);
        EXPECT_DOUBLE_EQ(v.getY(), 2.0);
        EXPECT_DOUBLE_EQ(v.getZ(), 3.0);
        EXPECT_DOUBLE_EQ(v.getW(), 4.0);
    }

    {
        const auto array = std::array<double, 3>{1., 2., 3.};
        const Quaterniond v = Quaterniond(std::span<const double, 3>(array), 4.);

        EXPECT_DOUBLE_EQ(v.getX(), 1.0);
        EXPECT_DOUBLE_EQ(v.getY(), 2.0);
        EXPECT_DOUBLE_EQ(v.getZ(), 3.0);
        EXPECT_DOUBLE_EQ(v.getW(), 4.0);
    }

    {
        const auto array = std::array<double, 4>{1., 2., 3., 4.};
        const Quaterniond v = Quaterniond(std::span<const double, 4>(array));

        EXPECT_DOUBLE_EQ(v.getX(), 1.0);
        EXPECT_DOUBLE_EQ(v.getY(), 2.0);
        EXPECT_DOUBLE_EQ(v.getZ(), 3.0);
        EXPECT_DOUBLE_EQ(v.getW(), 4.0);
    }

    {
        const Quaterniond v = Quaterniond(Vector3d{1., 2., 3.}, 4.);

        EXPECT_DOUBLE_EQ(v.getX(), 1.0);
        EXPECT_DOUBLE_EQ(v.getY(), 2.0);
        EXPECT_DOUBLE_EQ(v.getZ(), 3.0);
        EXPECT_DOUBLE_EQ(v.getW(), 4.0);
    }
}

TEST(TestQuaterniond, zero)
{
    const Quaterniond v = Quaterniond::zero();

    EXPECT_DOUBLE_EQ(v.getX(), 0.0);
    EXPECT_DOUBLE_EQ(v.getY(), 0.0);
    EXPECT_DOUBLE_EQ(v.getZ(), 0.0);
    EXPECT_DOUBLE_EQ(v.getW(), 0.0);
}

TEST(TestQuaterniond, identity)
{
    const Quaterniond v = Quaterniond::identity();

    EXPECT_DOUBLE_EQ(v.getX(), 0.0);
    EXPECT_DOUBLE_EQ(v.getY(), 0.0);
    EXPECT_DOUBLE_EQ(v.getZ(), 0.0);
    EXPECT_DOUBLE_EQ(v.getW(), 1.0);
}

TEST(TestQuaterniond, Setter)
{
    Quaterniond v{};
    v.setX(1.);
    v.setY(2.);
    v.setZ(3.);
    v.setW(4.);

    EXPECT_DOUBLE_EQ(v.getX(), 1.0);
    EXPECT_DOUBLE_EQ(v.getY(), 2.0);
    EXPECT_DOUBLE_EQ(v.getZ(), 3.0);
    EXPECT_DOUBLE_EQ(v.getW(), 4.0);
}

TEST(TestQuaterniond, Data)
{
    Quaterniond v{};

    EXPECT_EQ(reinterpret_cast<double*>(&v), v.data());
}

TEST(TestQuaterniond, Dot)
{
    const Quaterniond a{1., 2., 3., 4.};
    const Quaterniond b{5., 6., 7., 8.};

    const float result = Quaterniond::dot(a, b);

    EXPECT_DOUBLE_EQ(result, 70.);
}

TEST(TestQuaterniond, DotIdentity)
{
    const Quaterniond identity = Quaterniond::identity();
    const Quaterniond q{1., 2., 3., 4.};

    EXPECT_DOUBLE_EQ(Quaterniond::dot(identity, q), 4.);
}

TEST(TestQuaterniond, DotOrthogonal)
{
    const Quaterniond x{1., 0., 0., 0.};
    const Quaterniond y{0., 1., 0., 0.};

    EXPECT_DOUBLE_EQ(Quaterniond::dot(x, y), 0.);
}

TEST(TestQuaterniond, DotSelf)
{
    const Quaterniond q{1., 2., 3., 4.};

    EXPECT_DOUBLE_EQ(Quaterniond::dot(q, q), q.lengthSquare());
    EXPECT_DOUBLE_EQ(Quaterniond::dot(q, q), 30.);
}

TEST(TestQuaterniond, LengthSquareZero)
{
    const Quaterniond q(0., 0., 0., 0.);

    EXPECT_DOUBLE_EQ(q.lengthSquare(), 0.);
}

TEST(TestQuaterniond, LengthZero)
{
    const Quaterniond q(0., 0., 0., 0.);

    EXPECT_DOUBLE_EQ(q.length(), 0.);
}

TEST(TestQuaterniond, LengthSquareIdentity)
{
    const Quaterniond q = Quaterniond::identity();

    EXPECT_DOUBLE_EQ(q.lengthSquare(), 1.);
}

TEST(TestQuaterniond, LengthIdentity)
{
    const Quaterniond q = Quaterniond::identity();

    EXPECT_DOUBLE_EQ(q.length(), 1.);
}

TEST(TestQuaterniond, LengthSquare)
{
    const Quaterniond q(1., 2., 3., 4.);

    // 1² + 2² + 3² + 4² = 30
    EXPECT_DOUBLE_EQ(q.lengthSquare(), 30.);
}

TEST(TestQuaterniond, Length)
{
    const Quaterniond q(1., 2., 3., 4.);

    EXPECT_NEAR(q.length(), std::sqrt(30.), DoubleEpsilon);
}

TEST(TestQuaterniond, LengthNormalizedQuaternion)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, std::numbers::pi_v<double> * 0.37);

    EXPECT_NEAR(q.length(), 1., DoubleEpsilon);
    EXPECT_NEAR(q.lengthSquare(), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, FromNormalizeAxisAngle)
{
    {
        const Quaterniond q = Quaterniond::fromNormalizeAxisAngle(Vector3d{1., 0., 0.}, 0.);

        EXPECT_NEAR(q.getX(), 0., Epsilon<double>::Value);
        EXPECT_NEAR(q.getY(), 0., Epsilon<double>::Value);
        EXPECT_NEAR(q.getZ(), 0., Epsilon<double>::Value);
        EXPECT_NEAR(q.getW(), 1., Epsilon<double>::Value);
    }

    {
        const Quaterniond q = Quaterniond::fromNormalizeAxisAngle(Vector3d{1., 0., 0.}, std::numbers::pi_v<double>);

        EXPECT_NEAR(q.getX(), 1., Epsilon<double>::Value);
        EXPECT_NEAR(q.getY(), 0., Epsilon<double>::Value);
        EXPECT_NEAR(q.getZ(), 0., Epsilon<double>::Value);
        EXPECT_NEAR(q.getW(), 0., Epsilon<double>::Value);
    }

    {
        const Quaterniond q =
            Quaterniond::fromNormalizeAxisAngle(Vector3d{0., 1., 0.}, std::numbers::pi_v<double> * 0.5f);

        constexpr float sqrtHalf = std::numbers::sqrt2_v<double> * 0.5f;

        EXPECT_NEAR(q.getX(), 0., Epsilon<double>::Value);
        EXPECT_NEAR(q.getY(), sqrtHalf, Epsilon<double>::Value);
        EXPECT_NEAR(q.getZ(), 0., Epsilon<double>::Value);
        EXPECT_NEAR(q.getW(), sqrtHalf, Epsilon<double>::Value);
    }
}

TEST(TestQuaterniond, Normalize)
{
    Quaterniond q(1., 2., 3., 4.);

    q.normalize();

    const float invLength = 1. / std::sqrt(30.);

    EXPECT_NEAR(q.getX(), 1. * invLength, DoubleEpsilon);
    EXPECT_NEAR(q.getY(), 2. * invLength, DoubleEpsilon);
    EXPECT_NEAR(q.getZ(), 3. * invLength, DoubleEpsilon);
    EXPECT_NEAR(q.getW(), 4. * invLength, DoubleEpsilon);

    EXPECT_NEAR(q.length(), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, NormalizeZero)
{
    Quaterniond q(0., 0., 0., 0.);

    q.normalize();

    EXPECT_DOUBLE_EQ(q.getX(), 0.);
    EXPECT_DOUBLE_EQ(q.getY(), 0.);
    EXPECT_DOUBLE_EQ(q.getZ(), 0.);
    EXPECT_DOUBLE_EQ(q.getW(), 0.);
}

TEST(TestQuaterniond, GetNormalize)
{
    const Quaterniond q(1., 2., 3., 4.);

    const Quaterniond normalized = q.getNormalize();

    EXPECT_DOUBLE_EQ(q.getX(), 1.);
    EXPECT_DOUBLE_EQ(q.getY(), 2.);
    EXPECT_DOUBLE_EQ(q.getZ(), 3.);
    EXPECT_DOUBLE_EQ(q.getW(), 4.);

    EXPECT_NEAR(normalized.length(), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, Conjugate)
{
    Quaterniond q(1., 2., 3., 4.);

    q.conjugate();

    EXPECT_DOUBLE_EQ(q.getX(), -1.);
    EXPECT_DOUBLE_EQ(q.getY(), -2.);
    EXPECT_DOUBLE_EQ(q.getZ(), -3.);
    EXPECT_DOUBLE_EQ(q.getW(), 4.);
}

TEST(TestQuaterniond, GetConjugate)
{
    const Quaterniond q(1., 2., 3., 4.);

    const Quaterniond conjugate = q.getConjugate();

    EXPECT_DOUBLE_EQ(conjugate.getX(), -1.);
    EXPECT_DOUBLE_EQ(conjugate.getY(), -2.);
    EXPECT_DOUBLE_EQ(conjugate.getZ(), -3.);
    EXPECT_DOUBLE_EQ(conjugate.getW(), 4.);

    // Original unchanged
    EXPECT_DOUBLE_EQ(q.getX(), 1.);
    EXPECT_DOUBLE_EQ(q.getY(), 2.);
    EXPECT_DOUBLE_EQ(q.getZ(), 3.);
    EXPECT_DOUBLE_EQ(q.getW(), 4.);
}

TEST(TestQuaterniond, Inverse)
{
    Quaterniond q(1., 2., 3., 4.);

    q.inverse();

    constexpr float invLengthSquare = 1. / 30.;

    EXPECT_NEAR(q.getX(), -1. * invLengthSquare, DoubleEpsilon);
    EXPECT_NEAR(q.getY(), -2. * invLengthSquare, DoubleEpsilon);
    EXPECT_NEAR(q.getZ(), -3. * invLengthSquare, DoubleEpsilon);
    EXPECT_NEAR(q.getW(), 4. * invLengthSquare, DoubleEpsilon);
}

TEST(TestQuaterniond, GetInverse)
{
    const Quaterniond q(1., 2., 3., 4.);

    const Quaterniond inverse = q.getInverse();

    constexpr float invLengthSquare = 1. / 30.;

    EXPECT_NEAR(inverse.getX(), -1. * invLengthSquare, DoubleEpsilon);
    EXPECT_NEAR(inverse.getY(), -2. * invLengthSquare, DoubleEpsilon);
    EXPECT_NEAR(inverse.getZ(), -3. * invLengthSquare, DoubleEpsilon);
    EXPECT_NEAR(inverse.getW(), 4. * invLengthSquare, DoubleEpsilon);

    EXPECT_DOUBLE_EQ(q.getX(), 1.);
    EXPECT_DOUBLE_EQ(q.getY(), 2.);
    EXPECT_DOUBLE_EQ(q.getZ(), 3.);
    EXPECT_DOUBLE_EQ(q.getW(), 4.);
}

TEST(TestQuaterniond, InverseNormalizedEqualsConjugate)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, 0.7f);

    const Quaterniond inverse = q.getInverse();
    const Quaterniond conjugate = q.getConjugate();

    EXPECT_NEAR(inverse.getX(), conjugate.getX(), DoubleEpsilon);
    EXPECT_NEAR(inverse.getY(), conjugate.getY(), DoubleEpsilon);
    EXPECT_NEAR(inverse.getZ(), conjugate.getZ(), DoubleEpsilon);
    EXPECT_NEAR(inverse.getW(), conjugate.getW(), DoubleEpsilon);
}

TEST(TestQuaterniond, InverseZero)
{
    Quaterniond q(0., 0., 0., 0.);

    q.inverse();

    EXPECT_DOUBLE_EQ(q.getX(), 0.);
    EXPECT_DOUBLE_EQ(q.getY(), 0.);
    EXPECT_DOUBLE_EQ(q.getZ(), 0.);
    EXPECT_DOUBLE_EQ(q.getW(), 0.);
}

TEST(TestQuaterniond, DoubleConjugate)
{
    const Quaterniond q(1., 2., 3., 4.);

    const Quaterniond result = q.getConjugate().getConjugate();

    EXPECT_DOUBLE_EQ(result.getX(), q.getX());
    EXPECT_DOUBLE_EQ(result.getY(), q.getY());
    EXPECT_DOUBLE_EQ(result.getZ(), q.getZ());
    EXPECT_DOUBLE_EQ(result.getW(), q.getW());
}

TEST(TestQuaterniond, MemberRotate)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{0., 0., 1.}, std::numbers::pi_v<double> * 0.5f);

    const Vector3d result = q.rotate(Vector3d{1., 0., 0.});

    EXPECT_NEAR(result.getX(), 0., DoubleEpsilon);
    EXPECT_NEAR(result.getY(), 1., DoubleEpsilon);
    EXPECT_NEAR(result.getZ(), 0., DoubleEpsilon);
}

TEST(TestQuaterniond, MemberInverseRotate)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{0., 0., 1.}, std::numbers::pi_v<double> * 0.5f);

    const Vector3d result = q.inverseRotate(Vector3d{0., 1., 0.});

    EXPECT_NEAR(result.getX(), 1., DoubleEpsilon);
    EXPECT_NEAR(result.getY(), 0., DoubleEpsilon);
    EXPECT_NEAR(result.getZ(), 0., DoubleEpsilon);
}

TEST(TestQuaterniond, RotateInverseRotateRoundTrip)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, 0.73f);

    const Vector3d v{2., -3., 5.};

    const Vector3d rotated = q.rotate(v);
    const Vector3d restored = q.inverseRotate(rotated);

    EXPECT_NEAR(restored.getX(), v.getX(), DoubleEpsilon);
    EXPECT_NEAR(restored.getY(), v.getY(), DoubleEpsilon);
    EXPECT_NEAR(restored.getZ(), v.getZ(), DoubleEpsilon);
}

TEST(TestQuaterniond, ToMatrix3x3Identity)
{
    const Matrix3x3d m = Quaterniond::toMatrix3x3(Quaterniond::identity());

    EXPECT_NEAR(m.getM11(), 1., DoubleEpsilon);
    EXPECT_NEAR(m.getM12(), 0., DoubleEpsilon);
    EXPECT_NEAR(m.getM13(), 0., DoubleEpsilon);

    EXPECT_NEAR(m.getM21(), 0., DoubleEpsilon);
    EXPECT_NEAR(m.getM22(), 1., DoubleEpsilon);
    EXPECT_NEAR(m.getM23(), 0., DoubleEpsilon);

    EXPECT_NEAR(m.getM31(), 0., DoubleEpsilon);
    EXPECT_NEAR(m.getM32(), 0., DoubleEpsilon);
    EXPECT_NEAR(m.getM33(), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, ToMatrix3x3RotationZ90)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{0., 0., 1.}, std::numbers::pi_v<double> * 0.5f);

    const Matrix3x3d m = Quaterniond::toMatrix3x3(q);

    // [ 0 -1  0 ]
    // [ 1  0  0 ]
    // [ 0  0  1 ]

    EXPECT_NEAR(m.getM11(), 0., DoubleEpsilon);
    EXPECT_NEAR(m.getM12(), -1., DoubleEpsilon);
    EXPECT_NEAR(m.getM13(), 0., DoubleEpsilon);

    EXPECT_NEAR(m.getM21(), 1., DoubleEpsilon);
    EXPECT_NEAR(m.getM22(), 0., DoubleEpsilon);
    EXPECT_NEAR(m.getM23(), 0., DoubleEpsilon);

    EXPECT_NEAR(m.getM31(), 0., DoubleEpsilon);
    EXPECT_NEAR(m.getM32(), 0., DoubleEpsilon);
    EXPECT_NEAR(m.getM33(), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, ToMatrix4x4Identity)
{
    const Matrix4x4d m = Quaterniond::toMatrix4x4(Quaterniond::identity());

    EXPECT_NEAR(m.getM11(), 1., DoubleEpsilon);
    EXPECT_NEAR(m.getM22(), 1., DoubleEpsilon);
    EXPECT_NEAR(m.getM33(), 1., DoubleEpsilon);
    EXPECT_NEAR(m.getM44(), 1., DoubleEpsilon);

    EXPECT_NEAR(m.getM12(), 0., DoubleEpsilon);
    EXPECT_NEAR(m.getM13(), 0., DoubleEpsilon);
    EXPECT_NEAR(m.getM14(), 0., DoubleEpsilon);

    EXPECT_NEAR(m.getM21(), 0., DoubleEpsilon);
    EXPECT_NEAR(m.getM23(), 0., DoubleEpsilon);
    EXPECT_NEAR(m.getM24(), 0., DoubleEpsilon);

    EXPECT_NEAR(m.getM31(), 0., DoubleEpsilon);
    EXPECT_NEAR(m.getM32(), 0., DoubleEpsilon);
    EXPECT_NEAR(m.getM34(), 0., DoubleEpsilon);

    EXPECT_NEAR(m.getM41(), 0., DoubleEpsilon);
    EXPECT_NEAR(m.getM42(), 0., DoubleEpsilon);
    EXPECT_NEAR(m.getM43(), 0., DoubleEpsilon);
}

TEST(TestQuaterniond, FromRotationMatrixRoundTrip)
{
    const Quaterniond original = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, 0.8f);

    const Matrix3x3d m = Quaterniond::toMatrix3x3(original);

    const Quaterniond reconstructed = Quaterniond::fromRotationMatrix(m);

    EXPECT_TRUE(reconstructed.isNormalized());

    EXPECT_NEAR(std::abs(Quaterniond::dot(original, reconstructed)), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, FromRotationMatrix180X)
{
    const Quaterniond expected = Quaterniond::fromAxisAngle(Vector3d{1., 0., 0.}, std::numbers::pi_v<double>);

    const Matrix3x3d m = Quaterniond::toMatrix3x3(expected);

    const Quaterniond q = Quaterniond::fromRotationMatrix(m);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q, expected)), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, FromRotationMatrix180Y)
{
    const Quaterniond expected = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, std::numbers::pi_v<double>);

    const Matrix3x3d m = Quaterniond::toMatrix3x3(expected);

    const Quaterniond q = Quaterniond::fromRotationMatrix(m);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q, expected)), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, FromRotationMatrix180Z)
{
    const Quaterniond expected = Quaterniond::fromAxisAngle(Vector3d{0., 0., 1.}, std::numbers::pi_v<double>);

    const Matrix3x3d m = Quaterniond::toMatrix3x3(expected);

    const Quaterniond q = Quaterniond::fromRotationMatrix(m);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q, expected)), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, FromRotationMatrixPositiveTrace)
{
    const Quaterniond expected = Quaterniond::fromAxisAngle(Vector3d{1., 0., 0.}, 0.4f);

    const Matrix3x3d m = Quaterniond::toMatrix3x3(expected);

    const Quaterniond q = Quaterniond::fromRotationMatrix(m);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q, expected)), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, Nlerp)
{
    const Quaterniond a = Quaterniond::identity();
    const Quaterniond b = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, std::numbers::pi_v<double>);

    {
        const Quaterniond q = Quaterniond::nlerp(a, b, 0.);

        EXPECT_NEAR(std::abs(Quaterniond::dot(q, a)), 1., DoubleEpsilon);
        EXPECT_TRUE(q.isNormalized());
    }

    {
        const Quaterniond q = Quaterniond::nlerp(a, b, 1.);

        EXPECT_NEAR(std::abs(Quaterniond::dot(q, b)), 1., DoubleEpsilon);
        EXPECT_TRUE(q.isNormalized());
    }

    {
        const Quaterniond a = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, 0.);

        const Quaterniond b = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, std::numbers::pi_v<double> * 0.5f);

        const Quaterniond q = Quaterniond::nlerp(a, b, 0.5f);

        const Quaterniond expected =
            Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, std::numbers::pi_v<double> * 0.25f);

        EXPECT_NEAR(std::abs(Quaterniond::dot(q, expected)), 1., DoubleEpsilon);
    }
}

TEST(TestQuaterniond, NlerpClamp)
{
    const Quaterniond a = Quaterniond::fromAxisAngle(Vector3d{1., 0., 0.}, 0.5f);

    const Quaterniond b = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, 1.);

    const Quaterniond q0 = Quaterniond::nlerp(a, b, -10.);
    const Quaterniond q1 = Quaterniond::nlerp(a, b, 10.);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q0, a)), 1., DoubleEpsilon);
    EXPECT_NEAR(std::abs(Quaterniond::dot(q1, b)), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, NlerpAssumeNormalize)
{
    const Quaterniond a = Quaterniond::identity();

    const Quaterniond b = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, std::numbers::pi_v<double> * 0.5f);

    ASSERT_TRUE(a.isNormalized());
    ASSERT_TRUE(b.isNormalized());

    const Quaterniond q = Quaterniond::nlerpAssumeNormalize(a, b, 0.5f);

    const Quaterniond expected = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, std::numbers::pi_v<double> * 0.25f);

    EXPECT_TRUE(q.isNormalized());
    EXPECT_NEAR(std::abs(Quaterniond::dot(q, expected)), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, NlerpUnclampedNormalizesInputs)
{
    const Quaterniond a{0., 0., 0., 2.};
    const Quaterniond b{0., 4., 0., 0.};

    const Quaterniond q = Quaterniond::nlerpUnclamped(a, b, 0.5f);

    constexpr float sqrtHalf = std::numbers::sqrt2_v<double> * 0.5f;

    EXPECT_NEAR(q.getX(), 0., DoubleEpsilon);
    EXPECT_NEAR(q.getY(), sqrtHalf, DoubleEpsilon);
    EXPECT_NEAR(q.getZ(), 0., DoubleEpsilon);
    EXPECT_NEAR(q.getW(), sqrtHalf, DoubleEpsilon);

    EXPECT_TRUE(q.isNormalized());
}

TEST(TestQuaterniond, NlerpUnclampedAssumeNormalize)
{
    const Quaterniond a = Quaterniond::identity();
    const Quaterniond b{0., 1., 0., 0.};

    ASSERT_TRUE(a.isNormalized());
    ASSERT_TRUE(b.isNormalized());

    const Quaterniond q = Quaterniond::nlerpUnclampedAssumeNormalize(a, b, 0.5f);

    constexpr float sqrtHalf = std::numbers::sqrt2_v<double> * 0.5f;

    EXPECT_NEAR(q.getX(), 0., DoubleEpsilon);
    EXPECT_NEAR(q.getY(), sqrtHalf, DoubleEpsilon);
    EXPECT_NEAR(q.getZ(), 0., DoubleEpsilon);
    EXPECT_NEAR(q.getW(), sqrtHalf, DoubleEpsilon);

    EXPECT_TRUE(q.isNormalized());
}

TEST(TestQuaterniond, NlerpShortestPath)
{
    const Quaterniond a = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, 1.);

    const Quaterniond b = -a;

    ASSERT_LT(Quaterniond::dot(a, b), 0.);

    const Quaterniond q = Quaterniond::nlerpUnclampedAssumeNormalize(a, b, 0.5f);

    EXPECT_TRUE(q.isNormalized());

    // q and -q represent the same rotation.
    EXPECT_NEAR(std::abs(Quaterniond::dot(q, a)), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, Slerp)
{
    const Quaterniond a = Quaterniond::identity();

    const Quaterniond b = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, std::numbers::pi_v<double> * 0.5f);

    const Quaterniond q = Quaterniond::slerp(a, b, 0.5f);

    const Quaterniond expected = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, std::numbers::pi_v<double> * 0.25f);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q, expected)), 1., DoubleEpsilon);

    EXPECT_TRUE(q.isNormalized());
}

TEST(TestQuaterniond, SlerpClamp)
{
    const Quaterniond a = Quaterniond::fromAxisAngle(Vector3d{1., 0., 0.}, 0.25f);

    const Quaterniond b = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, 1.25f);

    const Quaterniond q0 = Quaterniond::slerp(a, b, -1.);

    const Quaterniond q1 = Quaterniond::slerp(a, b, 2.);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q0, a)), 1., DoubleEpsilon);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q1, b)), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, SlerpNUnclampedNormalizesInputs)
{
    const Quaterniond normalizedA = Quaterniond::identity();

    const Quaterniond normalizedB = Quaterniond::fromAxisAngle(Vector3d{0., 0., 1.}, std::numbers::pi_v<double> * 0.5f);

    const Quaterniond a = normalizedA * 2.;
    const Quaterniond b = normalizedB * 4.;

    ASSERT_FALSE(a.isNormalized());
    ASSERT_FALSE(b.isNormalized());

    const Quaterniond q = Quaterniond::slerpNUnclamped(a, b, 0.5f);

    const Quaterniond expected = Quaterniond::fromAxisAngle(Vector3d{0., 0., 1.}, std::numbers::pi_v<double> * 0.25f);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q, expected)), 1., DoubleEpsilon);

    EXPECT_TRUE(q.isNormalized());
}

TEST(TestQuaterniond, SlerpUnclampedAssumeNormalize)
{
    const Quaterniond a = Quaterniond::identity();

    const Quaterniond b = Quaterniond::fromAxisAngle(Vector3d{1., 0., 0.}, std::numbers::pi_v<double> * 0.5f);

    ASSERT_TRUE(a.isNormalized());
    ASSERT_TRUE(b.isNormalized());

    const Quaterniond q = Quaterniond::slerpUnclampedAssumeNormalize(a, b, 0.5f);

    const Quaterniond expected = Quaterniond::fromAxisAngle(Vector3d{1., 0., 0.}, std::numbers::pi_v<double> * 0.25f);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q, expected)), 1., DoubleEpsilon);

    EXPECT_NEAR(q.length(), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, SlerpAssumeNormalize)
{
    const Quaterniond a = Quaterniond::identity();

    const Quaterniond b = Quaterniond::fromAxisAngle(Vector3d{0., 0., 1.}, std::numbers::pi_v<double> * 0.5f);

    const Quaterniond q = Quaterniond::slerpAssumeNormalize(a, b, 0.5f);

    const Quaterniond expected = Quaterniond::fromAxisAngle(Vector3d{0., 0., 1.}, std::numbers::pi_v<double> * 0.25f);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q, expected)), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, SlerpShortestPath)
{
    const Quaterniond a = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, 0.8f);

    const Quaterniond b = -a;

    ASSERT_LT(Quaterniond::dot(a, b), 0.);

    const Quaterniond q = Quaterniond::slerpUnclampedAssumeNormalize(a, b, 0.5f);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q, a)), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, SlerpCloseQuaternions)
{
    const Quaterniond a = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, 0.1f);

    const Quaterniond b = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, 0.1001f);

    ASSERT_GT(Quaterniond::dot(a, b), 0.9995f);

    const Quaterniond q = Quaterniond::slerpUnclampedAssumeNormalize(a, b, 0.5f);

    const Quaterniond expected = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, 0.10005f);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q, expected)), 1., DoubleEpsilon);

    EXPECT_TRUE(q.isFinite());
}

TEST(TestQuaterniond, FromEulerAnglesIdentity)
{
    const Quaterniond q = Quaterniond::fromEulerAngles(0., 0., 0.);

    const Quaterniond expected = Quaterniond::identity();

    EXPECT_NEAR(std::abs(Quaterniond::dot(q, expected)), 1., DoubleEpsilon);
    EXPECT_TRUE(q.isNormalized());
}

TEST(TestQuaterniond, FromEulerAnglesRotationX)
{
    const Quaterniond q = Quaterniond::fromEulerAngles(std::numbers::pi_v<double> * 0.5f, 0., 0.);

    const Quaterniond expected = Quaterniond::fromAxisAngle(Vector3d{1., 0., 0.}, std::numbers::pi_v<double> * 0.5f);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q, expected)), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, FromEulerAnglesRotationY)
{
    const Quaterniond q = Quaterniond::fromEulerAngles(0., std::numbers::pi_v<double> * 0.5f, 0.);

    const Quaterniond expected = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, std::numbers::pi_v<double> * 0.5f);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q, expected)), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, FromEulerAnglesRotationZ)
{
    const Quaterniond q = Quaterniond::fromEulerAngles(0., 0., std::numbers::pi_v<double> * 0.5f);

    const Quaterniond expected = Quaterniond::fromAxisAngle(Vector3d{0., 0., 1.}, std::numbers::pi_v<double> * 0.5f);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q, expected)), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, ToEulerAnglesRoundTrip)
{
    constexpr float x = 0.3f;
    constexpr float y = 0.5f;
    constexpr float z = -0.7f;

    const Quaterniond original = Quaterniond::fromEulerAngles(x, y, z);

    const std::array<double, 3> euler = Quaterniond::toEulerAngles(original);

    const Quaterniond reconstructed = Quaterniond::fromEulerAngles(euler[0], euler[1], euler[2]);

    EXPECT_NEAR(std::abs(Quaterniond::dot(original, reconstructed)), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, ToEulerAnglesRotationX)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{1., 0., 0.}, std::numbers::pi_v<double> * 0.5f);

    const auto euler = Quaterniond::toEulerAngles(q);

    EXPECT_NEAR(euler[0], std::numbers::pi_v<double> * 0.5f, DoubleEpsilon);
    EXPECT_NEAR(euler[1], 0., DoubleEpsilon);
    EXPECT_NEAR(euler[2], 0., DoubleEpsilon);
}

TEST(TestQuaterniond, ToEulerAnglesRotationY)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, std::numbers::pi_v<double> * 0.25f);

    const auto euler = Quaterniond::toEulerAngles(q);

    EXPECT_NEAR(euler[0], 0., DoubleEpsilon);
    EXPECT_NEAR(euler[1], std::numbers::pi_v<double> * 0.25f, DoubleEpsilon);
    EXPECT_NEAR(euler[2], 0., DoubleEpsilon);
}

TEST(TestQuaterniond, ToEulerAnglesRotationZ)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{0., 0., 1.}, std::numbers::pi_v<double> * 0.5f);

    const auto euler = Quaterniond::toEulerAngles(q);

    EXPECT_NEAR(euler[0], 0., DoubleEpsilon);
    EXPECT_NEAR(euler[1], 0., DoubleEpsilon);
    EXPECT_NEAR(euler[2], std::numbers::pi_v<double> * 0.5f, DoubleEpsilon);
}

TEST(TestQuaterniond, RotateIdentity)
{
    const Quaterniond q = Quaterniond::identity();
    const Vector3d v{1., 2., 3.};

    const Vector3d rotated = Quaterniond::rotate(q, v);

    EXPECT_NEAR(rotated.getX(), 1., DoubleEpsilon);
    EXPECT_NEAR(rotated.getY(), 2., DoubleEpsilon);
    EXPECT_NEAR(rotated.getZ(), 3., DoubleEpsilon);
}

TEST(TestQuaterniond, Rotate90DegreesAroundZ)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{0., 0., 1.}, std::numbers::pi_v<double> * 0.5f);

    const Vector3d rotated = Quaterniond::rotate(q, Vector3d{1., 0., 0.});

    EXPECT_NEAR(rotated.getX(), 0., DoubleEpsilon);
    EXPECT_NEAR(rotated.getY(), 1., DoubleEpsilon);
    EXPECT_NEAR(rotated.getZ(), 0., DoubleEpsilon);
}

TEST(TestQuaterniond, Rotate90DegreesAroundY)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, std::numbers::pi_v<double> * 0.5f);

    const Vector3d rotated = Quaterniond::rotate(q, Vector3d{1., 0., 0.});

    EXPECT_NEAR(rotated.getX(), 0., DoubleEpsilon);
    EXPECT_NEAR(rotated.getY(), 0., DoubleEpsilon);
    EXPECT_NEAR(rotated.getZ(), -1., DoubleEpsilon);
}

TEST(TestQuaterniond, InverseRotate)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, 0.7f);

    const Vector3d v{2., -1., 4.};

    const Vector3d rotated = Quaterniond::rotate(q, v);

    const Vector3d restored = Quaterniond::inverseRotate(q, rotated);

    EXPECT_NEAR(restored.getX(), v.getX(), DoubleEpsilon);
    EXPECT_NEAR(restored.getY(), v.getY(), DoubleEpsilon);
    EXPECT_NEAR(restored.getZ(), v.getZ(), DoubleEpsilon);
}

TEST(TestQuaterniond, InverseRotate90DegreesAroundZ)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{0., 0., 1.}, std::numbers::pi_v<double> * 0.5f);

    const Vector3d rotated = Quaterniond::inverseRotate(q, Vector3d{0., 1., 0.});

    EXPECT_NEAR(rotated.getX(), 1., DoubleEpsilon);
    EXPECT_NEAR(rotated.getY(), 0., DoubleEpsilon);
    EXPECT_NEAR(rotated.getZ(), 0., DoubleEpsilon);
}

TEST(TestQuaterniond, AngleSameQuaternion)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, 0.7f);

    EXPECT_NEAR(Quaterniond::angle(q, q), 0., DoubleEpsilon);
}

TEST(TestQuaterniond, AngleSameRotationOppositeQuaternionSign)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, 0.7f);

    EXPECT_NEAR(Quaterniond::angle(q, -q), 0., DoubleEpsilon);
}

TEST(TestQuaterniond, Angle90Degrees)
{
    const Quaterniond a = Quaterniond::identity();

    const Quaterniond b = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, std::numbers::pi_v<double> * 0.5f);

    EXPECT_NEAR(Quaterniond::angle(a, b), std::numbers::pi_v<double> * 0.5f, DoubleEpsilon);
}

TEST(TestQuaterniond, AngleBetweenRotations)
{
    const Quaterniond a = Quaterniond::fromAxisAngle(Vector3d{0., 0., 1.}, std::numbers::pi_v<double> * 0.25f);

    const Quaterniond b = Quaterniond::fromAxisAngle(Vector3d{0., 0., 1.}, std::numbers::pi_v<double> * 0.75f);

    EXPECT_NEAR(Quaterniond::angle(a, b), std::numbers::pi_v<double> * 0.5f, DoubleEpsilon);
}

TEST(TestQuaterniond, QuaternionAdd)
{
    {
        const Quaterniond a{1., 2., 3., 4.};
        const Quaterniond b{5., 6., 7., 8.};

        const Quaterniond q = a + b;

        EXPECT_DOUBLE_EQ(q.getX(), 6.);
        EXPECT_DOUBLE_EQ(q.getY(), 8.);
        EXPECT_DOUBLE_EQ(q.getZ(), 10.);
        EXPECT_DOUBLE_EQ(q.getW(), 12.);
    }

    {
        Quaterniond q{1., 2., 3., 4.};
        const Quaterniond b{5., 6., 7., 8.};

        q += b;

        EXPECT_DOUBLE_EQ(q.getX(), 6.);
        EXPECT_DOUBLE_EQ(q.getY(), 8.);
        EXPECT_DOUBLE_EQ(q.getZ(), 10.);
        EXPECT_DOUBLE_EQ(q.getW(), 12.);
    }
}

TEST(TestQuaterniond, QuaternionSub)
{
    {
        const Quaterniond a{5., 6., 7., 8.};
        const Quaterniond b{1., 2., 3., 4.};

        const Quaterniond q = a - b;

        EXPECT_DOUBLE_EQ(q.getX(), 4.);
        EXPECT_DOUBLE_EQ(q.getY(), 4.);
        EXPECT_DOUBLE_EQ(q.getZ(), 4.);
        EXPECT_DOUBLE_EQ(q.getW(), 4.);
    }

    {
        Quaterniond q{5., 6., 7., 8.};
        const Quaterniond b{1., 2., 3., 4.};

        q -= b;

        EXPECT_DOUBLE_EQ(q.getX(), 4.);
        EXPECT_DOUBLE_EQ(q.getY(), 4.);
        EXPECT_DOUBLE_EQ(q.getZ(), 4.);
        EXPECT_DOUBLE_EQ(q.getW(), 4.);
    }
}

TEST(TestQuaterniond, QuaternionScalarMultiply)
{
    {
        const Quaterniond q{1., 2., 3., 4.};

        const Quaterniond result = q * 2.;

        EXPECT_DOUBLE_EQ(result.getX(), 2.);
        EXPECT_DOUBLE_EQ(result.getY(), 4.);
        EXPECT_DOUBLE_EQ(result.getZ(), 6.);
        EXPECT_DOUBLE_EQ(result.getW(), 8.);
    }

    {
        const Quaterniond q{1., 2., 3., 4.};

        const Quaterniond result = 2. * q;

        EXPECT_DOUBLE_EQ(result.getX(), 2.);
        EXPECT_DOUBLE_EQ(result.getY(), 4.);
        EXPECT_DOUBLE_EQ(result.getZ(), 6.);
        EXPECT_DOUBLE_EQ(result.getW(), 8.);
    }

    {
        Quaterniond q{1., 2., 3., 4.};

        q *= 2.;

        EXPECT_DOUBLE_EQ(q.getX(), 2.);
        EXPECT_DOUBLE_EQ(q.getY(), 4.);
        EXPECT_DOUBLE_EQ(q.getZ(), 6.);
        EXPECT_DOUBLE_EQ(q.getW(), 8.);
    }
}

TEST(TestQuaterniond, QuaternionScalarDivide)
{
    {
        const Quaterniond q{2., 4., 6., 8.};

        const Quaterniond result = q / 2.;

        EXPECT_DOUBLE_EQ(result.getX(), 1.);
        EXPECT_DOUBLE_EQ(result.getY(), 2.);
        EXPECT_DOUBLE_EQ(result.getZ(), 3.);
        EXPECT_DOUBLE_EQ(result.getW(), 4.);
    }

    {
        Quaterniond q{2., 4., 6., 8.};

        q /= 2.;

        EXPECT_DOUBLE_EQ(q.getX(), 1.);
        EXPECT_DOUBLE_EQ(q.getY(), 2.);
        EXPECT_DOUBLE_EQ(q.getZ(), 3.);
        EXPECT_DOUBLE_EQ(q.getW(), 4.);
    }
}

TEST(TestQuaterniond, MatrixRoundTripArbitraryAxis)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{1., 2., 3.}, 0.8);

    const Matrix3x3d m = Quaterniond::toMatrix3x3(q);
    const Quaterniond reconstructed = Quaterniond::fromRotationMatrix(m);

    EXPECT_NEAR(std::abs(Quaterniond::dot(q, reconstructed)), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, EqualSameValues)
{
    const Quaterniond a(1., 2., 3., 4.);
    const Quaterniond b(1., 2., 3., 4.);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(TestQuaterniond, NotEqualDifferentX)
{
    const Quaterniond a(1., 2., 3., 4.);
    const Quaterniond b(2., 2., 3., 4.);

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(TestQuaterniond, NotEqualDifferentY)
{
    const Quaterniond a(1., 2., 3., 4.);
    const Quaterniond b(1., 3., 3., 4.);

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(TestQuaterniond, NotEqualDifferentZ)
{
    const Quaterniond a(1., 2., 3., 4.);
    const Quaterniond b(1., 2., 4., 4.);

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(TestQuaterniond, NotEqualDifferentW)
{
    const Quaterniond a(1., 2., 3., 4.);
    const Quaterniond b(1., 2., 3., 5.);

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(TestQuaterniond, EqualWithinEpsilon)
{
    const Quaterniond a(1., 2., 3., 4.);

    const Quaterniond b(1. + DoubleEpsilon * 0.5f, 2. - DoubleEpsilon * 0.5f, 3. + DoubleEpsilon * 0.5f,
                        4. - DoubleEpsilon * 0.5f);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(TestQuaterniond, NotEqualOutsideEpsilon)
{
    const Quaterniond a(1., 2., 3., 4.);

    const Quaterniond b(1. + DoubleEpsilon * 2., 2., 3., 4.);

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(TestQuaterniond, OppositeSignNotComponentEqual)
{
    const Quaterniond q = Quaterniond::fromAxisAngle(Vector3d{0., 1., 0.}, 0.7);

    EXPECT_FALSE(q == -q);
    EXPECT_TRUE(q != -q);
}

TEST(TestQuaterniond, FromToRotation)
{
    const Vector3d from{1., 0., 0.};
    const Vector3d to{0., 1., 0.};

    const Quaterniond q = Quaterniond::fromToRotation(from, to);

    const Vector3d result = q.rotate(from);

    EXPECT_NEAR(result.getX(), to.getX(), DoubleEpsilon);
    EXPECT_NEAR(result.getY(), to.getY(), DoubleEpsilon);
    EXPECT_NEAR(result.getZ(), to.getZ(), DoubleEpsilon);

    EXPECT_TRUE(q.isNormalized());
}

TEST(TestQuaterniond, FromToRotationSameDirection)
{
    const Vector3d from{0., 1., 0.};

    const Quaterniond q = Quaterniond::fromToRotation(from, from);

    EXPECT_NEAR(q.getX(), 0., DoubleEpsilon);
    EXPECT_NEAR(q.getY(), 0., DoubleEpsilon);
    EXPECT_NEAR(q.getZ(), 0., DoubleEpsilon);
    EXPECT_NEAR(q.getW(), 1., DoubleEpsilon);
}

TEST(TestQuaterniond, FromToRotationOppositeDirection)
{
    const Vector3d from{1., 0., 0.};
    const Vector3d to{-1., 0., 0.};

    const Quaterniond q = Quaterniond::fromToRotation(from, to);

    const Vector3d result = q.rotate(from);

    EXPECT_NEAR(result.getX(), -1., DoubleEpsilon);
    EXPECT_NEAR(result.getY(), 0., DoubleEpsilon);
    EXPECT_NEAR(result.getZ(), 0., DoubleEpsilon);

    EXPECT_TRUE(q.isNormalized());
}

TEST(TestQuaterniond, FromToRotationArbitrary)
{
    const Vector3d from{1., 2., 3.};
    const Vector3d to{-2., 4., 1.};

    const Quaterniond q = Quaterniond::fromToRotation(from, to);

    const Vector3d result = q.rotate(from.getNormalize());

    const Vector3d expected = to.getNormalize();

    EXPECT_NEAR(result.getX(), expected.getX(), DoubleEpsilon);
    EXPECT_NEAR(result.getY(), expected.getY(), DoubleEpsilon);
    EXPECT_NEAR(result.getZ(), expected.getZ(), DoubleEpsilon);
}

TEST(TestQuaterniond, FromToRotationAssumeNormalize)
{
    const Vector3d from{1., 2., 3.};
    const Vector3d to{-2., 4., 1.};

    const Quaterniond q = Quaterniond::fromToRotation(from, to);
    const Quaterniond q2 = Quaterniond::fromToRotationAssumeNormalize(from.getNormalize(), to.getNormalize());

    EXPECT_DOUBLE_EQ(q.getX(), q2.getX());
    EXPECT_DOUBLE_EQ(q.getY(), q2.getY());
    EXPECT_DOUBLE_EQ(q.getZ(), q2.getZ());
    EXPECT_DOUBLE_EQ(q.getW(), q2.getW());
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
