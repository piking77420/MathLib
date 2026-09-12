#include <gtest/gtest.h>

#include <span>
#include <numbers>

#include <MathLibHeader.hpp>
#include <MatrixTransformation.hpp>

// Thanks chat-gpt to generate test tbh
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

using namespace MathLib;

TEST(TestQuaternionf, constructor)
{
    {
        const Quaternionf v = Quaternionf(1., 2., 3., 4.);

        EXPECT_FLOAT_EQ(v.getX(), 1.0);
        EXPECT_FLOAT_EQ(v.getY(), 2.0);
        EXPECT_FLOAT_EQ(v.getZ(), 3.0);
        EXPECT_FLOAT_EQ(v.getW(), 4.0);
    }

    {
        const auto array = std::array<float, 3>{1., 2., 3.};
        const Quaternionf v = Quaternionf(std::span<const float, 3>(array), 4.);

        EXPECT_FLOAT_EQ(v.getX(), 1.0);
        EXPECT_FLOAT_EQ(v.getY(), 2.0);
        EXPECT_FLOAT_EQ(v.getZ(), 3.0);
        EXPECT_FLOAT_EQ(v.getW(), 4.0);
    }

    {
        const auto array = std::array<float, 4>{1., 2., 3., 4.};
        const Quaternionf v = Quaternionf(std::span<const float, 4>(array));

        EXPECT_FLOAT_EQ(v.getX(), 1.0);
        EXPECT_FLOAT_EQ(v.getY(), 2.0);
        EXPECT_FLOAT_EQ(v.getZ(), 3.0);
        EXPECT_FLOAT_EQ(v.getW(), 4.0);
    }

    {
        const Quaternionf v = Quaternionf(Vector3f{1., 2., 3.}, 4.);

        EXPECT_FLOAT_EQ(v.getX(), 1.0);
        EXPECT_FLOAT_EQ(v.getY(), 2.0);
        EXPECT_FLOAT_EQ(v.getZ(), 3.0);
        EXPECT_FLOAT_EQ(v.getW(), 4.0);
    }
}

TEST(TestQuaternionf, zero)
{
    const Quaternionf v = Quaternionf::zero();

    EXPECT_FLOAT_EQ(v.getX(), 0.0);
    EXPECT_FLOAT_EQ(v.getY(), 0.0);
    EXPECT_FLOAT_EQ(v.getZ(), 0.0);
    EXPECT_FLOAT_EQ(v.getW(), 0.0);
}

TEST(TestQuaternionf, identity)
{
    const Quaternionf v = Quaternionf::identity();

    EXPECT_FLOAT_EQ(v.getX(), 0.0);
    EXPECT_FLOAT_EQ(v.getY(), 0.0);
    EXPECT_FLOAT_EQ(v.getZ(), 0.0);
    EXPECT_FLOAT_EQ(v.getW(), 1.0);
}

TEST(TestQuaternionf, Setter)
{
    Quaternionf v{};
    v.setX(1.);
    v.setY(2.);
    v.setZ(3.);
    v.setW(4.);

    EXPECT_FLOAT_EQ(v.getX(), 1.0);
    EXPECT_FLOAT_EQ(v.getY(), 2.0);
    EXPECT_FLOAT_EQ(v.getZ(), 3.0);
    EXPECT_FLOAT_EQ(v.getW(), 4.0);
}

TEST(TestQuaternionf, Data)
{
    Quaternionf v{};

    EXPECT_EQ(reinterpret_cast<float*>(&v), v.data());
}

TEST(TestQuaternionf, Dot)
{
    const Quaternionf a{1.f, 2.f, 3.f, 4.f};
    const Quaternionf b{5.f, 6.f, 7.f, 8.f};

    const float result = Quaternionf::dot(a, b);

    EXPECT_FLOAT_EQ(result, 70.f);
}

TEST(TestQuaternionf, DotIdentity)
{
    const Quaternionf identity = Quaternionf::identity();
    const Quaternionf q{1.f, 2.f, 3.f, 4.f};

    EXPECT_FLOAT_EQ(Quaternionf::dot(identity, q), 4.f);
}

TEST(TestQuaternionf, DotOrthogonal)
{
    const Quaternionf x{1.f, 0.f, 0.f, 0.f};
    const Quaternionf y{0.f, 1.f, 0.f, 0.f};

    EXPECT_FLOAT_EQ(Quaternionf::dot(x, y), 0.f);
}

TEST(TestQuaternionf, DotSelf)
{
    const Quaternionf q{1.f, 2.f, 3.f, 4.f};

    EXPECT_FLOAT_EQ(Quaternionf::dot(q, q), q.lengthSquare());
    EXPECT_FLOAT_EQ(Quaternionf::dot(q, q), 30.f);
}

TEST(TestQuaternionf, LengthSquareZero)
{
    const Quaternionf q(0.f, 0.f, 0.f, 0.f);

    EXPECT_FLOAT_EQ(q.lengthSquare(), 0.f);
}

TEST(TestQuaternionf, LengthZero)
{
    const Quaternionf q(0.f, 0.f, 0.f, 0.f);

    EXPECT_FLOAT_EQ(q.length(), 0.f);
}

TEST(TestQuaternionf, LengthSquareIdentity)
{
    const Quaternionf q = Quaternionf::identity();

    EXPECT_FLOAT_EQ(q.lengthSquare(), 1.f);
}

TEST(TestQuaternionf, LengthIdentity)
{
    const Quaternionf q = Quaternionf::identity();

    EXPECT_FLOAT_EQ(q.length(), 1.f);
}

TEST(TestQuaternionf, LengthSquare)
{
    const Quaternionf q(1.f, 2.f, 3.f, 4.f);

    // 1² + 2² + 3² + 4² = 30
    EXPECT_FLOAT_EQ(q.lengthSquare(), 30.f);
}

TEST(TestQuaternionf, Length)
{
    const Quaternionf q(1.f, 2.f, 3.f, 4.f);

    EXPECT_NEAR(q.length(), std::sqrt(30.f), FloatEpsilon);
}

TEST(TestQuaternionf, LengthNormalizedQuaternion)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, std::numbers::pi_v<float> * 0.37f);

    EXPECT_NEAR(q.length(), 1.f, FloatEpsilon);
    EXPECT_NEAR(q.lengthSquare(), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, FromNormalizeAxisAngle)
{
    {
        const Quaternionf q = Quaternionf::fromNormalizeAxisAngle(Vector3f{1.f, 0.f, 0.f}, 0.f);

        EXPECT_NEAR(q.getX(), 0.f, Epsilon<float>::Value);
        EXPECT_NEAR(q.getY(), 0.f, Epsilon<float>::Value);
        EXPECT_NEAR(q.getZ(), 0.f, Epsilon<float>::Value);
        EXPECT_NEAR(q.getW(), 1.f, Epsilon<float>::Value);
    }

    {
        const Quaternionf q = Quaternionf::fromNormalizeAxisAngle(Vector3f{1.f, 0.f, 0.f}, std::numbers::pi_v<float>);

        EXPECT_NEAR(q.getX(), 1.f, Epsilon<float>::Value);
        EXPECT_NEAR(q.getY(), 0.f, Epsilon<float>::Value);
        EXPECT_NEAR(q.getZ(), 0.f, Epsilon<float>::Value);
        EXPECT_NEAR(q.getW(), 0.f, Epsilon<float>::Value);
    }

    {
        const Quaternionf q =
            Quaternionf::fromNormalizeAxisAngle(Vector3f{0.f, 1.f, 0.f}, std::numbers::pi_v<float> * 0.5f);

        constexpr float sqrtHalf = std::numbers::sqrt2_v<float> * 0.5f;

        EXPECT_NEAR(q.getX(), 0.f, Epsilon<float>::Value);
        EXPECT_NEAR(q.getY(), sqrtHalf, Epsilon<float>::Value);
        EXPECT_NEAR(q.getZ(), 0.f, Epsilon<float>::Value);
        EXPECT_NEAR(q.getW(), sqrtHalf, Epsilon<float>::Value);
    }
}

TEST(TestQuaternionf, Normalize)
{
    Quaternionf q(1.f, 2.f, 3.f, 4.f);

    q.normalize();

    const float invLength = 1.f / std::sqrt(30.f);

    EXPECT_NEAR(q.getX(), 1.f * invLength, FloatEpsilon);
    EXPECT_NEAR(q.getY(), 2.f * invLength, FloatEpsilon);
    EXPECT_NEAR(q.getZ(), 3.f * invLength, FloatEpsilon);
    EXPECT_NEAR(q.getW(), 4.f * invLength, FloatEpsilon);

    EXPECT_NEAR(q.length(), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, NormalizeZero)
{
    Quaternionf q(0.f, 0.f, 0.f, 0.f);

    q.normalize();

    EXPECT_FLOAT_EQ(q.getX(), 0.f);
    EXPECT_FLOAT_EQ(q.getY(), 0.f);
    EXPECT_FLOAT_EQ(q.getZ(), 0.f);
    EXPECT_FLOAT_EQ(q.getW(), 0.f);
}

TEST(TestQuaternionf, GetNormalize)
{
    const Quaternionf q(1.f, 2.f, 3.f, 4.f);

    const Quaternionf normalized = q.getNormalize();

    EXPECT_FLOAT_EQ(q.getX(), 1.f);
    EXPECT_FLOAT_EQ(q.getY(), 2.f);
    EXPECT_FLOAT_EQ(q.getZ(), 3.f);
    EXPECT_FLOAT_EQ(q.getW(), 4.f);

    EXPECT_NEAR(normalized.length(), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, Conjugate)
{
    Quaternionf q(1.f, 2.f, 3.f, 4.f);

    q.conjugate();

    EXPECT_FLOAT_EQ(q.getX(), -1.f);
    EXPECT_FLOAT_EQ(q.getY(), -2.f);
    EXPECT_FLOAT_EQ(q.getZ(), -3.f);
    EXPECT_FLOAT_EQ(q.getW(), 4.f);
}

TEST(TestQuaternionf, GetConjugate)
{
    const Quaternionf q(1.f, 2.f, 3.f, 4.f);

    const Quaternionf conjugate = q.getConjugate();

    EXPECT_FLOAT_EQ(conjugate.getX(), -1.f);
    EXPECT_FLOAT_EQ(conjugate.getY(), -2.f);
    EXPECT_FLOAT_EQ(conjugate.getZ(), -3.f);
    EXPECT_FLOAT_EQ(conjugate.getW(), 4.f);

    // Original unchanged
    EXPECT_FLOAT_EQ(q.getX(), 1.f);
    EXPECT_FLOAT_EQ(q.getY(), 2.f);
    EXPECT_FLOAT_EQ(q.getZ(), 3.f);
    EXPECT_FLOAT_EQ(q.getW(), 4.f);
}

TEST(TestQuaternionf, Inverse)
{
    Quaternionf q(1.f, 2.f, 3.f, 4.f);

    q.inverse();

    constexpr float invLengthSquare = 1.f / 30.f;

    EXPECT_NEAR(q.getX(), -1.f * invLengthSquare, FloatEpsilon);
    EXPECT_NEAR(q.getY(), -2.f * invLengthSquare, FloatEpsilon);
    EXPECT_NEAR(q.getZ(), -3.f * invLengthSquare, FloatEpsilon);
    EXPECT_NEAR(q.getW(), 4.f * invLengthSquare, FloatEpsilon);
}

TEST(TestQuaternionf, GetInverse)
{
    const Quaternionf q(1.f, 2.f, 3.f, 4.f);

    const Quaternionf inverse = q.getInverse();

    constexpr float invLengthSquare = 1.f / 30.f;

    EXPECT_NEAR(inverse.getX(), -1.f * invLengthSquare, FloatEpsilon);
    EXPECT_NEAR(inverse.getY(), -2.f * invLengthSquare, FloatEpsilon);
    EXPECT_NEAR(inverse.getZ(), -3.f * invLengthSquare, FloatEpsilon);
    EXPECT_NEAR(inverse.getW(), 4.f * invLengthSquare, FloatEpsilon);

    EXPECT_FLOAT_EQ(q.getX(), 1.f);
    EXPECT_FLOAT_EQ(q.getY(), 2.f);
    EXPECT_FLOAT_EQ(q.getZ(), 3.f);
    EXPECT_FLOAT_EQ(q.getW(), 4.f);
}

TEST(TestQuaternionf, InverseNormalizedEqualsConjugate)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, 0.7f);

    const Quaternionf inverse = q.getInverse();
    const Quaternionf conjugate = q.getConjugate();

    EXPECT_NEAR(inverse.getX(), conjugate.getX(), FloatEpsilon);
    EXPECT_NEAR(inverse.getY(), conjugate.getY(), FloatEpsilon);
    EXPECT_NEAR(inverse.getZ(), conjugate.getZ(), FloatEpsilon);
    EXPECT_NEAR(inverse.getW(), conjugate.getW(), FloatEpsilon);
}

TEST(TestQuaternionf, InverseZero)
{
    Quaternionf q(0.f, 0.f, 0.f, 0.f);

    q.inverse();

    EXPECT_FLOAT_EQ(q.getX(), 0.f);
    EXPECT_FLOAT_EQ(q.getY(), 0.f);
    EXPECT_FLOAT_EQ(q.getZ(), 0.f);
    EXPECT_FLOAT_EQ(q.getW(), 0.f);
}

TEST(TestQuaternionf, DoubleConjugate)
{
    const Quaternionf q(1.f, 2.f, 3.f, 4.f);

    const Quaternionf result = q.getConjugate().getConjugate();

    EXPECT_FLOAT_EQ(result.getX(), q.getX());
    EXPECT_FLOAT_EQ(result.getY(), q.getY());
    EXPECT_FLOAT_EQ(result.getZ(), q.getZ());
    EXPECT_FLOAT_EQ(result.getW(), q.getW());
}

TEST(TestQuaternionf, MemberRotate)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{0.f, 0.f, 1.f}, std::numbers::pi_v<float> * 0.5f);

    const Vector3f result = q.rotate(Vector3f{1.f, 0.f, 0.f});

    EXPECT_NEAR(result.getX(), 0.f, FloatEpsilon);
    EXPECT_NEAR(result.getY(), 1.f, FloatEpsilon);
    EXPECT_NEAR(result.getZ(), 0.f, FloatEpsilon);
}

TEST(TestQuaternionf, MemberInverseRotate)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{0.f, 0.f, 1.f}, std::numbers::pi_v<float> * 0.5f);

    const Vector3f result = q.inverseRotate(Vector3f{0.f, 1.f, 0.f});

    EXPECT_NEAR(result.getX(), 1.f, FloatEpsilon);
    EXPECT_NEAR(result.getY(), 0.f, FloatEpsilon);
    EXPECT_NEAR(result.getZ(), 0.f, FloatEpsilon);
}

TEST(TestQuaternionf, RotateInverseRotateRoundTrip)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, 0.73f);

    const Vector3f v{2.f, -3.f, 5.f};

    const Vector3f rotated = q.rotate(v);
    const Vector3f restored = q.inverseRotate(rotated);

    EXPECT_NEAR(restored.getX(), v.getX(), FloatEpsilon);
    EXPECT_NEAR(restored.getY(), v.getY(), FloatEpsilon);
    EXPECT_NEAR(restored.getZ(), v.getZ(), FloatEpsilon);
}

TEST(TestQuaternionf, ToMatrix3x3Identity)
{
    const Matrix3x3f m = Quaternionf::toMatrix3x3(Quaternionf::identity());

    EXPECT_NEAR(m.getM11(), 1.f, FloatEpsilon);
    EXPECT_NEAR(m.getM12(), 0.f, FloatEpsilon);
    EXPECT_NEAR(m.getM13(), 0.f, FloatEpsilon);

    EXPECT_NEAR(m.getM21(), 0.f, FloatEpsilon);
    EXPECT_NEAR(m.getM22(), 1.f, FloatEpsilon);
    EXPECT_NEAR(m.getM23(), 0.f, FloatEpsilon);

    EXPECT_NEAR(m.getM31(), 0.f, FloatEpsilon);
    EXPECT_NEAR(m.getM32(), 0.f, FloatEpsilon);
    EXPECT_NEAR(m.getM33(), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, ToMatrix3x3RotationZ90)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{0.f, 0.f, 1.f}, std::numbers::pi_v<float> * 0.5f);

    const Matrix3x3f m = Quaternionf::toMatrix3x3(q);

    // [ 0 -1  0 ]
    // [ 1  0  0 ]
    // [ 0  0  1 ]

    EXPECT_NEAR(m.getM11(), 0.f, FloatEpsilon);
    EXPECT_NEAR(m.getM12(), -1.f, FloatEpsilon);
    EXPECT_NEAR(m.getM13(), 0.f, FloatEpsilon);

    EXPECT_NEAR(m.getM21(), 1.f, FloatEpsilon);
    EXPECT_NEAR(m.getM22(), 0.f, FloatEpsilon);
    EXPECT_NEAR(m.getM23(), 0.f, FloatEpsilon);

    EXPECT_NEAR(m.getM31(), 0.f, FloatEpsilon);
    EXPECT_NEAR(m.getM32(), 0.f, FloatEpsilon);
    EXPECT_NEAR(m.getM33(), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, ToMatrix4x4Identity)
{
    const Matrix4x4f m = Quaternionf::toMatrix4x4(Quaternionf::identity());

    EXPECT_NEAR(m.getM11(), 1.f, FloatEpsilon);
    EXPECT_NEAR(m.getM22(), 1.f, FloatEpsilon);
    EXPECT_NEAR(m.getM33(), 1.f, FloatEpsilon);
    EXPECT_NEAR(m.getM44(), 1.f, FloatEpsilon);

    EXPECT_NEAR(m.getM12(), 0.f, FloatEpsilon);
    EXPECT_NEAR(m.getM13(), 0.f, FloatEpsilon);
    EXPECT_NEAR(m.getM14(), 0.f, FloatEpsilon);

    EXPECT_NEAR(m.getM21(), 0.f, FloatEpsilon);
    EXPECT_NEAR(m.getM23(), 0.f, FloatEpsilon);
    EXPECT_NEAR(m.getM24(), 0.f, FloatEpsilon);

    EXPECT_NEAR(m.getM31(), 0.f, FloatEpsilon);
    EXPECT_NEAR(m.getM32(), 0.f, FloatEpsilon);
    EXPECT_NEAR(m.getM34(), 0.f, FloatEpsilon);

    EXPECT_NEAR(m.getM41(), 0.f, FloatEpsilon);
    EXPECT_NEAR(m.getM42(), 0.f, FloatEpsilon);
    EXPECT_NEAR(m.getM43(), 0.f, FloatEpsilon);
}

TEST(TestQuaternionf, FromRotationMatrixRoundTrip)
{
    const Quaternionf original = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, 0.8f);

    const Matrix3x3f m = Quaternionf::toMatrix3x3(original);

    const Quaternionf reconstructed = Quaternionf::fromRotationMatrix(m);

    EXPECT_TRUE(reconstructed.isNormalized());

    EXPECT_NEAR(std::abs(Quaternionf::dot(original, reconstructed)), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, FromRotationMatrix180X)
{
    const Quaternionf expected = Quaternionf::fromAxisAngle(Vector3f{1.f, 0.f, 0.f}, std::numbers::pi_v<float>);

    const Matrix3x3f m = Quaternionf::toMatrix3x3(expected);

    const Quaternionf q = Quaternionf::fromRotationMatrix(m);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q, expected)), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, FromRotationMatrix180Y)
{
    const Quaternionf expected = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, std::numbers::pi_v<float>);

    const Matrix3x3f m = Quaternionf::toMatrix3x3(expected);

    const Quaternionf q = Quaternionf::fromRotationMatrix(m);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q, expected)), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, FromRotationMatrix180Z)
{
    const Quaternionf expected = Quaternionf::fromAxisAngle(Vector3f{0.f, 0.f, 1.f}, std::numbers::pi_v<float>);

    const Matrix3x3f m = Quaternionf::toMatrix3x3(expected);

    const Quaternionf q = Quaternionf::fromRotationMatrix(m);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q, expected)), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, FromRotationMatrixPositiveTrace)
{
    const Quaternionf expected = Quaternionf::fromAxisAngle(Vector3f{1.f, 0.f, 0.f}, 0.4f);

    const Matrix3x3f m = Quaternionf::toMatrix3x3(expected);

    const Quaternionf q = Quaternionf::fromRotationMatrix(m);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q, expected)), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, Nlerp)
{
    const Quaternionf a = Quaternionf::identity();
    const Quaternionf b = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, std::numbers::pi_v<float>);

    {
        const Quaternionf q = Quaternionf::nlerp(a, b, 0.f);

        EXPECT_NEAR(std::abs(Quaternionf::dot(q, a)), 1.f, FloatEpsilon);
        EXPECT_TRUE(q.isNormalized());
    }

    {
        const Quaternionf q = Quaternionf::nlerp(a, b, 1.f);

        EXPECT_NEAR(std::abs(Quaternionf::dot(q, b)), 1.f, FloatEpsilon);
        EXPECT_TRUE(q.isNormalized());
    }

    {
        const Quaternionf a = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, 0.f);

        const Quaternionf b = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, std::numbers::pi_v<float> * 0.5f);

        const Quaternionf q = Quaternionf::nlerp(a, b, 0.5f);

        const Quaternionf expected =
            Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, std::numbers::pi_v<float> * 0.25f);

        EXPECT_NEAR(std::abs(Quaternionf::dot(q, expected)), 1.f, FloatEpsilon);
    }
}

TEST(TestQuaternionf, NlerpClamp)
{
    const Quaternionf a = Quaternionf::fromAxisAngle(Vector3f{1.f, 0.f, 0.f}, 0.5f);

    const Quaternionf b = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, 1.f);

    const Quaternionf q0 = Quaternionf::nlerp(a, b, -10.f);
    const Quaternionf q1 = Quaternionf::nlerp(a, b, 10.f);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q0, a)), 1.f, FloatEpsilon);
    EXPECT_NEAR(std::abs(Quaternionf::dot(q1, b)), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, NlerpAssumeNormalize)
{
    const Quaternionf a = Quaternionf::identity();

    const Quaternionf b = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, std::numbers::pi_v<float> * 0.5f);

    ASSERT_TRUE(a.isNormalized());
    ASSERT_TRUE(b.isNormalized());

    const Quaternionf q = Quaternionf::nlerpAssumeNormalize(a, b, 0.5f);

    const Quaternionf expected = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, std::numbers::pi_v<float> * 0.25f);

    EXPECT_TRUE(q.isNormalized());
    EXPECT_NEAR(std::abs(Quaternionf::dot(q, expected)), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, NlerpUnclampedNormalizesInputs)
{
    const Quaternionf a{0.f, 0.f, 0.f, 2.f};
    const Quaternionf b{0.f, 4.f, 0.f, 0.f};

    const Quaternionf q = Quaternionf::nlerpUnclamped(a, b, 0.5f);

    constexpr float sqrtHalf = std::numbers::sqrt2_v<float> * 0.5f;

    EXPECT_NEAR(q.getX(), 0.f, FloatEpsilon);
    EXPECT_NEAR(q.getY(), sqrtHalf, FloatEpsilon);
    EXPECT_NEAR(q.getZ(), 0.f, FloatEpsilon);
    EXPECT_NEAR(q.getW(), sqrtHalf, FloatEpsilon);

    EXPECT_TRUE(q.isNormalized());
}

TEST(TestQuaternionf, NlerpUnclampedAssumeNormalize)
{
    const Quaternionf a = Quaternionf::identity();
    const Quaternionf b{0.f, 1.f, 0.f, 0.f};

    ASSERT_TRUE(a.isNormalized());
    ASSERT_TRUE(b.isNormalized());

    const Quaternionf q = Quaternionf::nlerpUnclampedAssumeNormalize(a, b, 0.5f);

    constexpr float sqrtHalf = std::numbers::sqrt2_v<float> * 0.5f;

    EXPECT_NEAR(q.getX(), 0.f, FloatEpsilon);
    EXPECT_NEAR(q.getY(), sqrtHalf, FloatEpsilon);
    EXPECT_NEAR(q.getZ(), 0.f, FloatEpsilon);
    EXPECT_NEAR(q.getW(), sqrtHalf, FloatEpsilon);

    EXPECT_TRUE(q.isNormalized());
}

TEST(TestQuaternionf, NlerpShortestPath)
{
    const Quaternionf a = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, 1.f);

    const Quaternionf b = -a;

    ASSERT_LT(Quaternionf::dot(a, b), 0.f);

    const Quaternionf q = Quaternionf::nlerpUnclampedAssumeNormalize(a, b, 0.5f);

    EXPECT_TRUE(q.isNormalized());

    // q and -q represent the same rotation.
    EXPECT_NEAR(std::abs(Quaternionf::dot(q, a)), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, Slerp)
{
    const Quaternionf a = Quaternionf::identity();

    const Quaternionf b = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, std::numbers::pi_v<float> * 0.5f);

    const Quaternionf q = Quaternionf::slerp(a, b, 0.5f);

    const Quaternionf expected = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, std::numbers::pi_v<float> * 0.25f);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q, expected)), 1.f, FloatEpsilon);

    EXPECT_TRUE(q.isNormalized());
}

TEST(TestQuaternionf, SlerpClamp)
{
    const Quaternionf a = Quaternionf::fromAxisAngle(Vector3f{1.f, 0.f, 0.f}, 0.25f);

    const Quaternionf b = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, 1.25f);

    const Quaternionf q0 = Quaternionf::slerp(a, b, -1.f);

    const Quaternionf q1 = Quaternionf::slerp(a, b, 2.f);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q0, a)), 1.f, FloatEpsilon);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q1, b)), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, SlerpNUnclampedNormalizesInputs)
{
    const Quaternionf normalizedA = Quaternionf::identity();

    const Quaternionf normalizedB =
        Quaternionf::fromAxisAngle(Vector3f{0.f, 0.f, 1.f}, std::numbers::pi_v<float> * 0.5f);

    const Quaternionf a = normalizedA * 2.f;
    const Quaternionf b = normalizedB * 4.f;

    ASSERT_FALSE(a.isNormalized());
    ASSERT_FALSE(b.isNormalized());

    const Quaternionf q = Quaternionf::slerpNUnclamped(a, b, 0.5f);

    const Quaternionf expected = Quaternionf::fromAxisAngle(Vector3f{0.f, 0.f, 1.f}, std::numbers::pi_v<float> * 0.25f);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q, expected)), 1.f, FloatEpsilon);

    EXPECT_TRUE(q.isNormalized());
}

TEST(TestQuaternionf, SlerpUnclampedAssumeNormalize)
{
    const Quaternionf a = Quaternionf::identity();

    const Quaternionf b = Quaternionf::fromAxisAngle(Vector3f{1.f, 0.f, 0.f}, std::numbers::pi_v<float> * 0.5f);

    ASSERT_TRUE(a.isNormalized());
    ASSERT_TRUE(b.isNormalized());

    const Quaternionf q = Quaternionf::slerpUnclampedAssumeNormalize(a, b, 0.5f);

    const Quaternionf expected = Quaternionf::fromAxisAngle(Vector3f{1.f, 0.f, 0.f}, std::numbers::pi_v<float> * 0.25f);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q, expected)), 1.f, FloatEpsilon);

    EXPECT_NEAR(q.length(), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, SlerpAssumeNormalize)
{
    const Quaternionf a = Quaternionf::identity();

    const Quaternionf b = Quaternionf::fromAxisAngle(Vector3f{0.f, 0.f, 1.f}, std::numbers::pi_v<float> * 0.5f);

    const Quaternionf q = Quaternionf::slerpAssumeNormalize(a, b, 0.5f);

    const Quaternionf expected = Quaternionf::fromAxisAngle(Vector3f{0.f, 0.f, 1.f}, std::numbers::pi_v<float> * 0.25f);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q, expected)), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, SlerpShortestPath)
{
    const Quaternionf a = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, 0.8f);

    const Quaternionf b = -a;

    ASSERT_LT(Quaternionf::dot(a, b), 0.f);

    const Quaternionf q = Quaternionf::slerpUnclampedAssumeNormalize(a, b, 0.5f);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q, a)), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, SlerpCloseQuaternions)
{
    const Quaternionf a = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, 0.1f);

    const Quaternionf b = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, 0.1001f);

    ASSERT_GT(Quaternionf::dot(a, b), 0.9995f);

    const Quaternionf q = Quaternionf::slerpUnclampedAssumeNormalize(a, b, 0.5f);

    const Quaternionf expected = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, 0.10005f);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q, expected)), 1.f, FloatEpsilon);

    EXPECT_TRUE(q.isFinite());
}

TEST(TestQuaternionf, FromEulerAnglesIdentity)
{
    const Quaternionf q = Quaternionf::fromEulerAngles(0.f, 0.f, 0.f);

    const Quaternionf expected = Quaternionf::identity();

    EXPECT_NEAR(std::abs(Quaternionf::dot(q, expected)), 1.f, FloatEpsilon);
    EXPECT_TRUE(q.isNormalized());
}

TEST(TestQuaternionf, FromEulerAnglesRotationX)
{
    const Quaternionf q = Quaternionf::fromEulerAngles(std::numbers::pi_v<float> * 0.5f, 0.f, 0.f);

    const Quaternionf expected = Quaternionf::fromAxisAngle(Vector3f{1.f, 0.f, 0.f}, std::numbers::pi_v<float> * 0.5f);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q, expected)), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, FromEulerAnglesRotationY)
{
    const Quaternionf q = Quaternionf::fromEulerAngles(0.f, std::numbers::pi_v<float> * 0.5f, 0.f);

    const Quaternionf expected = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, std::numbers::pi_v<float> * 0.5f);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q, expected)), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, FromEulerAnglesRotationZ)
{
    const Quaternionf q = Quaternionf::fromEulerAngles(0.f, 0.f, std::numbers::pi_v<float> * 0.5f);

    const Quaternionf expected = Quaternionf::fromAxisAngle(Vector3f{0.f, 0.f, 1.f}, std::numbers::pi_v<float> * 0.5f);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q, expected)), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, ToEulerAnglesRoundTrip)
{
    constexpr float x = 0.3f;
    constexpr float y = 0.5f;
    constexpr float z = -0.7f;

    const Quaternionf original = Quaternionf::fromEulerAngles(x, y, z);

    const std::array<float, 3> euler = Quaternionf::toEulerAngles(original);

    const Quaternionf reconstructed = Quaternionf::fromEulerAngles(euler[0], euler[1], euler[2]);

    EXPECT_NEAR(std::abs(Quaternionf::dot(original, reconstructed)), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, ToEulerAnglesRotationX)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{1.f, 0.f, 0.f}, std::numbers::pi_v<float> * 0.5f);

    const auto euler = Quaternionf::toEulerAngles(q);

    EXPECT_NEAR(euler[0], std::numbers::pi_v<float> * 0.5f, FloatEpsilon);
    EXPECT_NEAR(euler[1], 0.f, FloatEpsilon);
    EXPECT_NEAR(euler[2], 0.f, FloatEpsilon);
}

TEST(TestQuaternionf, ToEulerAnglesRotationY)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, std::numbers::pi_v<float> * 0.25f);

    const auto euler = Quaternionf::toEulerAngles(q);

    EXPECT_NEAR(euler[0], 0.f, FloatEpsilon);
    EXPECT_NEAR(euler[1], std::numbers::pi_v<float> * 0.25f, FloatEpsilon);
    EXPECT_NEAR(euler[2], 0.f, FloatEpsilon);
}

TEST(TestQuaternionf, ToEulerAnglesRotationZ)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{0.f, 0.f, 1.f}, std::numbers::pi_v<float> * 0.5f);

    const auto euler = Quaternionf::toEulerAngles(q);

    EXPECT_NEAR(euler[0], 0.f, FloatEpsilon);
    EXPECT_NEAR(euler[1], 0.f, FloatEpsilon);
    EXPECT_NEAR(euler[2], std::numbers::pi_v<float> * 0.5f, FloatEpsilon);
}

TEST(TestQuaternionf, RotateIdentity)
{
    const Quaternionf q = Quaternionf::identity();
    const Vector3f v{1.f, 2.f, 3.f};

    const Vector3f rotated = Quaternionf::rotate(q, v);

    EXPECT_NEAR(rotated.getX(), 1.f, FloatEpsilon);
    EXPECT_NEAR(rotated.getY(), 2.f, FloatEpsilon);
    EXPECT_NEAR(rotated.getZ(), 3.f, FloatEpsilon);
}

TEST(TestQuaternionf, Rotate90DegreesAroundZ)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{0.f, 0.f, 1.f}, std::numbers::pi_v<float> * 0.5f);

    const Vector3f rotated = Quaternionf::rotate(q, Vector3f{1.f, 0.f, 0.f});

    EXPECT_NEAR(rotated.getX(), 0.f, FloatEpsilon);
    EXPECT_NEAR(rotated.getY(), 1.f, FloatEpsilon);
    EXPECT_NEAR(rotated.getZ(), 0.f, FloatEpsilon);
}

TEST(TestQuaternionf, Rotate90DegreesAroundY)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, std::numbers::pi_v<float> * 0.5f);

    const Vector3f rotated = Quaternionf::rotate(q, Vector3f{1.f, 0.f, 0.f});

    EXPECT_NEAR(rotated.getX(), 0.f, FloatEpsilon);
    EXPECT_NEAR(rotated.getY(), 0.f, FloatEpsilon);
    EXPECT_NEAR(rotated.getZ(), -1.f, FloatEpsilon);
}

TEST(TestQuaternionf, InverseRotate)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, 0.7f);

    const Vector3f v{2.f, -1.f, 4.f};

    const Vector3f rotated = Quaternionf::rotate(q, v);

    const Vector3f restored = Quaternionf::inverseRotate(q, rotated);

    EXPECT_NEAR(restored.getX(), v.getX(), FloatEpsilon);
    EXPECT_NEAR(restored.getY(), v.getY(), FloatEpsilon);
    EXPECT_NEAR(restored.getZ(), v.getZ(), FloatEpsilon);
}

TEST(TestQuaternionf, InverseRotate90DegreesAroundZ)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{0.f, 0.f, 1.f}, std::numbers::pi_v<float> * 0.5f);

    const Vector3f rotated = Quaternionf::inverseRotate(q, Vector3f{0.f, 1.f, 0.f});

    EXPECT_NEAR(rotated.getX(), 1.f, FloatEpsilon);
    EXPECT_NEAR(rotated.getY(), 0.f, FloatEpsilon);
    EXPECT_NEAR(rotated.getZ(), 0.f, FloatEpsilon);
}

TEST(TestQuaternionf, AngleSameQuaternion)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, 0.7f);

    EXPECT_NEAR(Quaternionf::angle(q, q), 0.f, FloatEpsilon);
}

TEST(TestQuaternionf, AngleSameRotationOppositeQuaternionSign)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, 0.7f);

    EXPECT_NEAR(Quaternionf::angle(q, -q), 0.f, FloatEpsilon);
}

TEST(TestQuaternionf, Angle90Degrees)
{
    const Quaternionf a = Quaternionf::identity();

    const Quaternionf b = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, std::numbers::pi_v<float> * 0.5f);

    EXPECT_NEAR(Quaternionf::angle(a, b), std::numbers::pi_v<float> * 0.5f, FloatEpsilon);
}

TEST(TestQuaternionf, AngleBetweenRotations)
{
    const Quaternionf a = Quaternionf::fromAxisAngle(Vector3f{0.f, 0.f, 1.f}, std::numbers::pi_v<float> * 0.25f);

    const Quaternionf b = Quaternionf::fromAxisAngle(Vector3f{0.f, 0.f, 1.f}, std::numbers::pi_v<float> * 0.75f);

    EXPECT_NEAR(Quaternionf::angle(a, b), std::numbers::pi_v<float> * 0.5f, FloatEpsilon);
}

TEST(TestQuaternionf, QuaternionAdd)
{
    {
        const Quaternionf a{1.f, 2.f, 3.f, 4.f};
        const Quaternionf b{5.f, 6.f, 7.f, 8.f};

        const Quaternionf q = a + b;

        EXPECT_FLOAT_EQ(q.getX(), 6.f);
        EXPECT_FLOAT_EQ(q.getY(), 8.f);
        EXPECT_FLOAT_EQ(q.getZ(), 10.f);
        EXPECT_FLOAT_EQ(q.getW(), 12.f);
    }

    {
        Quaternionf q{1.f, 2.f, 3.f, 4.f};
        const Quaternionf b{5.f, 6.f, 7.f, 8.f};

        q += b;

        EXPECT_FLOAT_EQ(q.getX(), 6.f);
        EXPECT_FLOAT_EQ(q.getY(), 8.f);
        EXPECT_FLOAT_EQ(q.getZ(), 10.f);
        EXPECT_FLOAT_EQ(q.getW(), 12.f);
    }
}

TEST(TestQuaternionf, QuaternionSub)
{
    {
        const Quaternionf a{5.f, 6.f, 7.f, 8.f};
        const Quaternionf b{1.f, 2.f, 3.f, 4.f};

        const Quaternionf q = a - b;

        EXPECT_FLOAT_EQ(q.getX(), 4.f);
        EXPECT_FLOAT_EQ(q.getY(), 4.f);
        EXPECT_FLOAT_EQ(q.getZ(), 4.f);
        EXPECT_FLOAT_EQ(q.getW(), 4.f);
    }

    {
        Quaternionf q{5.f, 6.f, 7.f, 8.f};
        const Quaternionf b{1.f, 2.f, 3.f, 4.f};

        q -= b;

        EXPECT_FLOAT_EQ(q.getX(), 4.f);
        EXPECT_FLOAT_EQ(q.getY(), 4.f);
        EXPECT_FLOAT_EQ(q.getZ(), 4.f);
        EXPECT_FLOAT_EQ(q.getW(), 4.f);
    }
}

TEST(TestQuaternionf, QuaternionScalarMultiply)
{
    {
        const Quaternionf q{1.f, 2.f, 3.f, 4.f};

        const Quaternionf result = q * 2.f;

        EXPECT_FLOAT_EQ(result.getX(), 2.f);
        EXPECT_FLOAT_EQ(result.getY(), 4.f);
        EXPECT_FLOAT_EQ(result.getZ(), 6.f);
        EXPECT_FLOAT_EQ(result.getW(), 8.f);
    }

    {
        const Quaternionf q{1.f, 2.f, 3.f, 4.f};

        const Quaternionf result = 2.f * q;

        EXPECT_FLOAT_EQ(result.getX(), 2.f);
        EXPECT_FLOAT_EQ(result.getY(), 4.f);
        EXPECT_FLOAT_EQ(result.getZ(), 6.f);
        EXPECT_FLOAT_EQ(result.getW(), 8.f);
    }

    {
        Quaternionf q{1.f, 2.f, 3.f, 4.f};

        q *= 2.f;

        EXPECT_FLOAT_EQ(q.getX(), 2.f);
        EXPECT_FLOAT_EQ(q.getY(), 4.f);
        EXPECT_FLOAT_EQ(q.getZ(), 6.f);
        EXPECT_FLOAT_EQ(q.getW(), 8.f);
    }
}

TEST(TestQuaternionf, QuaternionScalarDivide)
{
    {
        const Quaternionf q{2.f, 4.f, 6.f, 8.f};

        const Quaternionf result = q / 2.f;

        EXPECT_FLOAT_EQ(result.getX(), 1.f);
        EXPECT_FLOAT_EQ(result.getY(), 2.f);
        EXPECT_FLOAT_EQ(result.getZ(), 3.f);
        EXPECT_FLOAT_EQ(result.getW(), 4.f);
    }

    {
        Quaternionf q{2.f, 4.f, 6.f, 8.f};

        q /= 2.f;

        EXPECT_FLOAT_EQ(q.getX(), 1.f);
        EXPECT_FLOAT_EQ(q.getY(), 2.f);
        EXPECT_FLOAT_EQ(q.getZ(), 3.f);
        EXPECT_FLOAT_EQ(q.getW(), 4.f);
    }
}

TEST(TestQuaternionf, MatrixRoundTripArbitraryAxis)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{1.f, 2.f, 3.f}, 0.8f);

    const Matrix3x3f m = Quaternionf::toMatrix3x3(q);
    const Quaternionf reconstructed = Quaternionf::fromRotationMatrix(m);

    EXPECT_NEAR(std::abs(Quaternionf::dot(q, reconstructed)), 1.f, FloatEpsilon);
}

TEST(TestQuaternionf, EqualSameValues)
{
    const Quaternionf a(1.f, 2.f, 3.f, 4.f);
    const Quaternionf b(1.f, 2.f, 3.f, 4.f);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(TestQuaternionf, NotEqualDifferentX)
{
    const Quaternionf a(1.f, 2.f, 3.f, 4.f);
    const Quaternionf b(2.f, 2.f, 3.f, 4.f);

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(TestQuaternionf, NotEqualDifferentY)
{
    const Quaternionf a(1.f, 2.f, 3.f, 4.f);
    const Quaternionf b(1.f, 3.f, 3.f, 4.f);

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(TestQuaternionf, NotEqualDifferentZ)
{
    const Quaternionf a(1.f, 2.f, 3.f, 4.f);
    const Quaternionf b(1.f, 2.f, 4.f, 4.f);

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(TestQuaternionf, NotEqualDifferentW)
{
    const Quaternionf a(1.f, 2.f, 3.f, 4.f);
    const Quaternionf b(1.f, 2.f, 3.f, 5.f);

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(TestQuaternionf, EqualWithinEpsilon)
{
    const Quaternionf a(1.f, 2.f, 3.f, 4.f);

    const Quaternionf b(1.f + FloatEpsilon * 0.5f, 2.f - FloatEpsilon * 0.5f, 3.f + FloatEpsilon * 0.5f,
                        4.f - FloatEpsilon * 0.5f);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(TestQuaternionf, NotEqualOutsideEpsilon)
{
    const Quaternionf a(1.f, 2.f, 3.f, 4.f);

    const Quaternionf b(1.f + FloatEpsilon * 2.f, 2.f, 3.f, 4.f);

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(TestQuaternionf, OppositeSignNotComponentEqual)
{
    const Quaternionf q = Quaternionf::fromAxisAngle(Vector3f{0.f, 1.f, 0.f}, 0.7f);

    EXPECT_FALSE(q == -q);
    EXPECT_TRUE(q != -q);
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
