#ifndef MATH_LIB_QUATERNION_H
#define MATH_LIB_QUATERNION_H

#include <array>
#include <cmath>
#include <type_traits>
#include <numbers>
#include <span>
#include <MathLibHeader.hpp>
#include <Vector3.hpp>
#include <Matrix3x3.hpp>
#include <Matrix4x4.hpp>

#define QUAT4F_ALIGNEMENT 16
#define QUAT4D_ALIGNEMENT 32
#include <AVX.hpp>
#include <NEON.hpp>
#include <SSE.hpp>

namespace MathLib
{
    // X Y Z W
    // XYZ imaginary part
    // W real Part
    template<typename T>
    requires(std::is_floating_point_v<T>)
    class alignas(std::is_same_v<T, float> ? QUAT4F_ALIGNEMENT : QUAT4D_ALIGNEMENT) Quaternion
    {
    public:
#if defined(MATH_LIB_INTRINSIC)
        using _VectorInstrinsic =
            std::conditional_t<std::is_same_v<T, float>, Simd::VectorRegister4Float, Simd::VectorRegister4Double>;
#endif

        using _ValueType = T;
        using _Vector3 = Vector3<_ValueType>;
        using _Mat3x3 = Matrix3x3<_ValueType>;
        using _Mat4x4 = Matrix4x4<_ValueType>;
        static constexpr _ValueType Zero = static_cast<_ValueType>(0);
        static constexpr _ValueType One = static_cast<_ValueType>(1);
        static constexpr _ValueType Two = static_cast<_ValueType>(2);

        explicit Quaternion() = default;
        ~Quaternion() = default;

        MATH_LIB_FORCE_INLINE explicit Quaternion(_ValueType x, _ValueType y, _ValueType z, _ValueType w)
            : m_data({x, y, z, w})
        {
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE explicit Quaternion(const std::span<const T, 3>& spanXYZ, _ValueType w)
            : m_data({spanXYZ[0], spanXYZ[1], spanXYZ[2], w})
        {
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE explicit Quaternion(const std::span<const T, 4>& spanXYZ)
            : m_data({spanXYZ[0], spanXYZ[1], spanXYZ[2], spanXYZ[3]})
        {
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE explicit Quaternion(const _Vector3& imaginary, _ValueType real)
            : m_data({imaginary[0], imaginary[1], imaginary[2], real})
        {
            ASSERT_IS_FINITE(*this);
        }

#if defined(MATH_LIB_INTRINSIC)
        MATH_LIB_FORCE_INLINE Quaternion(const _VectorInstrinsic& reg) noexcept
        {
            Simd::storeUnaligned(reg, m_data.data());
        }
#endif // defined(MATH_LIB_INTRINSIC)

        [[nodiscard]] MATH_LIB_FORCE_INLINE const _ValueType* data() const noexcept
        {
            return m_data.data();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE _ValueType* data() noexcept
        {
            return m_data.data();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion zero() noexcept
        {
            // clang-format off
            return Quaternion(Zero, Zero, Zero, Zero);
            // clang-format on
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion identity() noexcept
        {
            // clang-format off
            return Quaternion(Zero, Zero, Zero, One);
            // clang-format on
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static bool sameRotation(const Quaternion& rhs,
                                                                     const Quaternion& lhs) noexcept
        {
            return std::abs(dot(lhs, rhs)) >= One - Epsilon<_ValueType>::Value;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static _ValueType dot(const Quaternion& a, const Quaternion& b) noexcept
        {

#if defined(MATH_LIB_INTRINSIC)
            return Simd::dot(a, b);
#else
            return a.m_data[0] * b.m_data[0] + a.m_data[1] * b.m_data[1] + a.m_data[2] * b.m_data[2] +
                   a.m_data[3] * b.m_data[3];
#endif // defined(MATH_LIB_INTRINSIC)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion fromNormalizeAxisAngle(const _Vector3& axis,
                                                                                     _ValueType angle) noexcept
        {
            const _ValueType halfAngle = angle * _ValueType(0.5);

            const _ValueType sinHalfAngle = std::sin(halfAngle);
            const _ValueType cosHalfAngle = std::cos(halfAngle);
#if defined(MATH_LIB_INTRINSIC)
            return Quaternion(Simd::mul(Simd::makeVector4(axis.getX(), axis.getY(), axis.getZ(), T(1.0)),
                                        Simd::makeVector4(sinHalfAngle, sinHalfAngle, sinHalfAngle, cosHalfAngle)));
#else
            return Quaternion(axis.getX() * sinHalfAngle, axis.getY() * sinHalfAngle, axis.getZ() * sinHalfAngle,
                              cosHalfAngle);
#endif // defined(MATH_LIB_INTRINSIC)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion fromAxisAngle(const _Vector3& axis,
                                                                            _ValueType angle) noexcept
        {
            return fromNormalizeAxisAngle(axis.getNormalize(), angle);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion nlerp(const Quaternion& q0, const Quaternion& q1,
                                                                    _ValueType t)
        {
            if (t <= Zero)
                return q0.getNormalize();

            if (t >= One)
                return q1.getNormalize();

            return nlerpUnclamped(q0, q1, t);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion nlerpAssumeNormalize(const Quaternion& q0,
                                                                                   const Quaternion& q1, _ValueType t)
        {
            if (t <= Zero)
                return q0;

            if (t >= One)
                return q1;

            return nlerpUnclampedAssumeNormalize(q0, q1, t);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion nlerpUnclamped(const Quaternion& q0, const Quaternion& q1,
                                                                             _ValueType t)
        {
            const Quaternion a = q0.getNormalize();
            const Quaternion bNormalized = q1.getNormalize();

            const Quaternion b = dot(a, bNormalized) >= Zero ? bNormalized : -bNormalized;

            return (a * (One - t) + b * t).getNormalize();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion
        nlerpUnclampedAssumeNormalize(const Quaternion& q0, const Quaternion& q1, _ValueType t)
        {
            const Quaternion b = dot(q0, q1) >= Zero ? q1 : -q1;

            return (q0 * (One - t) + b * t).getNormalize();
        }

        template<_ValueType ShortCutHigh = _ValueType(0.9995)>
        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion slerpNUnclamped(const Quaternion& a, const Quaternion& b,
                                                                              _ValueType t)
        {
            return slerpUnclampedAssumeNormalize<ShortCutHigh>(a.getNormalize(), b.getNormalize(), t);
        }

        template<_ValueType ShortCutHigh = _ValueType(0.9995)>
        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion
        slerpUnclampedAssumeNormalize(const Quaternion& a, const Quaternion& b, _ValueType t)
        {
            static_assert(ShortCutHigh > Zero && ShortCutHigh < One);

            _ValueType cosTheta = Quaternion::dot(a, b);
            Quaternion bCopy = b;

            if (cosTheta < Zero)
            {
                cosTheta = -cosTheta;
                bCopy = -bCopy;
            }

            cosTheta = std::clamp(cosTheta, Zero, One);

            if (cosTheta > ShortCutHigh)
                return nlerpUnclampedAssumeNormalize(a, bCopy, t);

            const _ValueType theta = std::acos(cosTheta);
            const _ValueType sinTheta = std::sin(theta);

            const _ValueType w0 = std::sin((One - t) * theta) / sinTheta;

            const _ValueType w1 = std::sin(t * theta) / sinTheta;

            return a * w0 + bCopy * w1;
        }

        template<_ValueType ShortCutHigh = _ValueType(0.9995)>
        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion slerp(const Quaternion& a, const Quaternion& b,
                                                                    _ValueType t)
        {
            if (t <= Zero)
                return a.getNormalize();

            if (t >= One)
                return b.getNormalize();

            return slerpNUnclamped<ShortCutHigh>(a, b, t);
        }

        template<_ValueType ShortCutHigh = _ValueType(0.9995)>
        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion slerpAssumeNormalize(const Quaternion& a,
                                                                                   const Quaternion& b, _ValueType t)
        {
            if (t <= Zero)
                return a;

            if (t >= One)
                return b;

            return slerpUnclampedAssumeNormalize<ShortCutHigh>(a, b, t);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static std::array<_ValueType, 3> toEulerAngles(const Quaternion& q)
        {
            const _ValueType qX = q.getX();
            const _ValueType qY = q.getY();
            const _ValueType qZ = q.getZ();
            const _ValueType qW = q.getW();

            const _ValueType x =
                std::atan2(_ValueType(2) * (qW * qX + qY * qZ), _ValueType(1) - _ValueType(2) * (qX * qX + qY * qY));

            const _ValueType sinY = std::clamp(_ValueType(2) * (qW * qY - qZ * qX), _ValueType(-1), _ValueType(1));

            const _ValueType y = std::atan2(sinY, std::sqrt(std::max(_ValueType(0), _ValueType(1) - sinY * sinY)));

            const _ValueType z =
                std::atan2(_ValueType(2) * (qW * qZ + qX * qY), _ValueType(1) - _ValueType(2) * (qY * qY + qZ * qZ));

            return {x, y, z};
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion
        fromEulerAngles(_ValueType x, _ValueType y, _ValueType z,
                        RotationOrder rotationOrder = RotationOrder::XYZ) noexcept
        {
            MATHLIB_ASSERT(rotationOrder == RotationOrder::XYZ && "Only handles XYZ rotation order");

            const _ValueType xHalf = x * _ValueType(0.5);
            const _ValueType yHalf = y * _ValueType(0.5);
            const _ValueType zHalf = z * _ValueType(0.5);

            const _ValueType cosHalfX = std::cos(xHalf);
            const _ValueType sinHalfX = std::sin(xHalf);

            const _ValueType cosHalfY = std::cos(yHalf);
            const _ValueType sinHalfY = std::sin(yHalf);

            const _ValueType cosHalfZ = std::cos(zHalf);
            const _ValueType sinHalfZ = std::sin(zHalf);

            const _ValueType qX = sinHalfX * cosHalfY * cosHalfZ - cosHalfX * sinHalfY * sinHalfZ;

            const _ValueType qY = cosHalfX * sinHalfY * cosHalfZ + sinHalfX * cosHalfY * sinHalfZ;

            const _ValueType qZ = cosHalfX * cosHalfY * sinHalfZ - sinHalfX * sinHalfY * cosHalfZ;

            const _ValueType qW = cosHalfX * cosHalfY * cosHalfZ + sinHalfX * sinHalfY * sinHalfZ;

            return Quaternion(qX, qY, qZ, qW);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static _Vector3 rotate(const Quaternion& q, const _Vector3& v) noexcept
        {
            const _Vector3 qv(q.getX(), q.getY(), q.getZ());

            const _Vector3 t = _Vector3::cross(qv, v) * _ValueType(2);

            return v + t * q.getW() + _Vector3::cross(qv, t);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static _Vector3 inverseRotate(const Quaternion& q,
                                                                          const _Vector3& v) noexcept
        {
            return rotate(q.getConjugate(), v);
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE _ValueType angle(const Quaternion& a, const Quaternion& b) noexcept
        {
            _ValueType d = std::abs(dot(a.getNormalize(), b.getNormalize()));
            d = std::clamp(d, Zero, One);

            return Two * std::acos(d);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion fromToRotation(const _Vector3& from,
                                                                             const _Vector3& to) noexcept
        {
            const _Vector3 fromN = from.getNormalize();
            const _Vector3 toN = to.getNormalize();

            const _ValueType d = _Vector3::dot(fromN, toN);

            // Same direction.
            if (d >= One - Epsilon<_ValueType>::Double)
                return identity();

            // Opposite direction: cross(from, to) is ~zero,
            // so choose any axis perpendicular to from.
            if (d <= -One + Epsilon<_ValueType>::Double)
            {
                _Vector3 axis = _Vector3::cross(_Vector3(One, Zero, Zero), fromN);

                // from is almost parallel to X, use Y instead.
                if (fuzzyZero(axis.lengthSquare()))
                {
                    axis = _Vector3::cross(_Vector3(Zero, One, Zero), fromN);
                }

                axis.normalize();

                return fromNormalizeAxisAngle(axis, std::numbers::pi_v<_ValueType>);
            }

            const _Vector3 axis = _Vector3::cross(fromN, toN);

            Quaternion q(axis.getX(), axis.getY(), axis.getZ(), One + d);

            return q.getNormalize();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion
        fromToRotationAssumeNormalize(const _Vector3& fromN, const _Vector3& toN) noexcept
        {
            const _ValueType d = _Vector3::dot(fromN, toN);

            // Same direction.
            if (d >= One - Epsilon<_ValueType>::Double)
                return identity();

            // Opposite direction: cross(from, to) is ~zero,
            // so choose any axis perpendicular to from.
            if (d <= -One + Epsilon<_ValueType>::Double)
            {
                _Vector3 axis = _Vector3::cross(_Vector3(One, Zero, Zero), fromN);

                // from is almost parallel to X, use Y instead.
                if (fuzzyZero(axis.lengthSquare()))
                {
                    axis = _Vector3::cross(_Vector3(Zero, One, Zero), fromN);
                }

                axis.normalize();

                return fromNormalizeAxisAngle(axis, std::numbers::pi_v<_ValueType>);
            }

            const _Vector3 axis = _Vector3::cross(fromN, toN);
            return Quaternion(axis.getX(), axis.getY(), axis.getZ(), One + d).getNormalize();
        }

        MATH_LIB_FORCE_INLINE _ValueType getX() const
        {
            return m_data[0];
        }

        MATH_LIB_FORCE_INLINE _ValueType getY() const
        {
            return m_data[1];
        }

        MATH_LIB_FORCE_INLINE _ValueType getZ() const
        {
            return m_data[2];
        }

        MATH_LIB_FORCE_INLINE _ValueType getW() const
        {
            return m_data[3];
        }

        MATH_LIB_FORCE_INLINE void setX(_ValueType newA)
        {
            m_data[0] = newA;
        }

        MATH_LIB_FORCE_INLINE void setY(_ValueType newB)
        {
            m_data[1] = newB;
        }

        MATH_LIB_FORCE_INLINE void setZ(_ValueType newC)
        {
            m_data[2] = newC;
        }

        MATH_LIB_FORCE_INLINE void setW(_ValueType newW)
        {
            m_data[3] = newW;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE bool isFinite() const
        {
            return std::isfinite(m_data[0]) && std::isfinite(m_data[1]) && std::isfinite(m_data[2]) &&
                   std::isfinite(m_data[3]);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE bool isNormalized() const noexcept
        {
            return fuzzyZero(lengthSquare() - One, Epsilon<_ValueType>::Double);
        }

        MATH_LIB_FORCE_INLINE Quaternion& operator+=(const Quaternion& rhs) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Quaternion(Simd::add(*this, rhs));
#else
            m_data[0] += rhs.m_data[0];
            m_data[1] += rhs.m_data[1];
            m_data[2] += rhs.m_data[2];
            m_data[3] += rhs.m_data[3];
#endif // defined(MATH_LIB_INTRINSIC)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Quaternion& operator-=(const Quaternion& rhs) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Quaternion(Simd::sub(*this, rhs));
#else
            m_data[0] -= rhs.m_data[0];
            m_data[1] -= rhs.m_data[1];
            m_data[2] -= rhs.m_data[2];
            m_data[3] -= rhs.m_data[3];
#endif // defined(MATH_LIB_INTRINSIC)
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE friend Quaternion operator+(Quaternion lhs, const Quaternion& rhs) noexcept
        {
            lhs += rhs;
            return lhs;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE friend Quaternion operator-(Quaternion lhs, const Quaternion& rhs) noexcept
        {
            lhs -= rhs;
            return lhs;
        }

        MATH_LIB_FORCE_INLINE Quaternion& operator*=(_ValueType scalar) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Quaternion(Simd::mul(*this, Simd::makeVector4(scalar)));
#else
            m_data[0] *= scalar;
            m_data[1] *= scalar;
            m_data[2] *= scalar;
            m_data[3] *= scalar;
#endif // defined(MATH_LIB_INTRINSIC)
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Quaternion operator*(_ValueType scalar, Quaternion rhs) noexcept
        {
            rhs *= scalar;
            return rhs;
        }

        MATH_LIB_FORCE_INLINE Quaternion& operator/=(_ValueType scalar) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Quaternion(Simd::div(*this, Simd::makeVector4(scalar)));
#else
            m_data[0] /= scalar;
            m_data[1] /= scalar;
            m_data[2] /= scalar;
            m_data[3] /= scalar;
#endif // defined(MATH_LIB_INTRINSIC)
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE friend Quaternion operator*(Quaternion lhs, _ValueType scalar) noexcept
        {
            lhs *= scalar;
            return lhs;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE friend Quaternion operator/(Quaternion lhs, _ValueType scalar) noexcept
        {
            lhs /= scalar;
            return lhs;
        }

        MATH_LIB_FORCE_INLINE Quaternion& operator*=(const Quaternion& rhs) noexcept
        {
            const _ValueType x1 = m_data[0];
            const _ValueType y1 = m_data[1];
            const _ValueType z1 = m_data[2];
            const _ValueType w1 = m_data[3];

            const _ValueType x2 = rhs.m_data[0];
            const _ValueType y2 = rhs.m_data[1];
            const _ValueType z2 = rhs.m_data[2];
            const _ValueType w2 = rhs.m_data[3];

            m_data[0] = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2;
            m_data[1] = w1 * y2 - x1 * z2 + y1 * w2 + z1 * x2;
            m_data[2] = w1 * z2 + x1 * y2 - y1 * x2 + z1 * w2;
            m_data[3] = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2;

            return *this;
        }

        MATH_LIB_FORCE_INLINE friend Quaternion operator*(Quaternion lhs, const Quaternion& rhs) noexcept
        {
            lhs *= rhs;
            return lhs;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Quaternion operator-() const noexcept
        {
            return Quaternion(-m_data[0], -m_data[1], -m_data[2], -m_data[3]);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE bool operator==(const Quaternion& other) const
        {
            return fuzzyZero(m_data[0] - other.m_data[0]) && fuzzyZero(m_data[1] - other.m_data[1]) &&
                   fuzzyZero(m_data[2] - other.m_data[2]) && fuzzyZero(m_data[3] - other.m_data[3]);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE bool operator!=(const Quaternion& other) const
        {
            return !(*this == other);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE _ValueType dot(const Quaternion& rhs) const noexcept
        {
            return dot(*this, rhs);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE _ValueType lengthSquare() const
        {
            return dot(*this, *this);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE _ValueType length() const
        {
            return std::sqrt(lengthSquare());
        }

        MATH_LIB_FORCE_INLINE Quaternion& normalize()
        {
            const _ValueType lenghtSquare = lengthSquare();
            if (fuzzyZero(lenghtSquare, Epsilon<_ValueType>::Double))
                return *this;

            const _ValueType invLength = One / std::sqrt(lenghtSquare);

#if defined(MATH_LIB_INTRINSIC)
            *this = Quaternion(Simd::mul(*this, Simd::makeVector4(invLength)));
#else
            m_data[0] *= invLength;
            m_data[1] *= invLength;
            m_data[2] *= invLength;
            m_data[3] *= invLength;
#endif // defined(MATH_LIB_INTRINSIC)
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Quaternion getNormalize() const
        {
            Quaternion q = *this;
            return q.normalize();
        }

        MATH_LIB_FORCE_INLINE Quaternion& conjugate()
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Quaternion(Simd::negate(Simd::makeVector4(m_data[0], m_data[1], m_data[2], -m_data[3])));
#else
            m_data[0] = -m_data[0];
            m_data[1] = -m_data[1];
            m_data[2] = -m_data[2];
#endif // defined(MATH_LIB_INTRINSIC)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Quaternion getConjugate() const
        {
            Quaternion q = *this;
            return q.conjugate();
        }

        MATH_LIB_FORCE_INLINE Quaternion& inverse() noexcept
        {
            const _ValueType lengthSq = lengthSquare();

            if (fuzzyZero(lengthSq))
                return *this;

            const _ValueType invLengthSq = _ValueType(1) / lengthSq;

#if defined(MATH_LIB_INTRINSIC)
            _VectorInstrinsic vec =
                Simd::negate(Simd::makeVector4(invLengthSq, invLengthSq, invLengthSq, -invLengthSq));
            *this = Quaternion(Simd::mul(*this, vec));
#else
            m_data[0] *= -invLengthSq;
            m_data[1] *= -invLengthSq;
            m_data[2] *= -invLengthSq;
            m_data[3] *= invLengthSq;
#endif // defined(MATH_LIB_INTRINSIC)
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Quaternion getInverse() const noexcept
        {
            Quaternion q = *this;
            return q.inverse();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE _Vector3 rotate(const _Vector3& v) const noexcept
        {
            return rotate(*this, v);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE _Vector3 inverseRotate(const _Vector3& v) const noexcept
        {
            return inverseRotate(*this, v);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static _Mat3x3 toMatrix3x3(const Quaternion& q) noexcept
        {
            const _ValueType x = q.getX();
            const _ValueType y = q.getY();
            const _ValueType z = q.getZ();
            const _ValueType w = q.getW();

            const _ValueType sqX = x * x;
            const _ValueType sqY = y * y;
            const _ValueType sqZ = z * z;
            const _ValueType sqW = w * w;

            const _ValueType xy = x * y;
            const _ValueType yw = y * w;
            const _ValueType zw = z * w;
            const _ValueType yz = y * z;
            const _ValueType xw = x * w;
            const _ValueType xz = x * z;

            // clang-format off
            const _ValueType m11 = One - Two * (sqY + sqZ); const _ValueType m12 = Two * (xy - zw); const _ValueType m13 = Two * (xz + yw);
            const _ValueType m21 = Two * (xy + zw); const _ValueType m22 = One - Two * (sqX + sqZ); const _ValueType m23 = Two * (yz - xw);
            const _ValueType m31 = Two * (xz - yw); const _ValueType m32 = Two * (yz + xw); const _ValueType m33 = One - Two * (sqX + sqY);

            return _Mat3x3(m11, m12, m13,
                           m21, m22, m23,
                           m31, m32, m33);
            // clang-format on
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static _Mat4x4 toMatrix4x4(const Quaternion& q) noexcept
        {
            const _ValueType x = q.getX();
            const _ValueType y = q.getY();
            const _ValueType z = q.getZ();
            const _ValueType w = q.getW();

            const _ValueType sqX = x * x;
            const _ValueType sqY = y * y;
            const _ValueType sqZ = z * z;
            const _ValueType sqW = w * w;

            const _ValueType xy = x * y;
            const _ValueType yw = y * w;
            const _ValueType zw = z * w;
            const _ValueType yz = y * z;
            const _ValueType xw = x * w;
            const _ValueType xz = x * z;

            // clang-format off
            const _ValueType m11 = One - Two * (sqY + sqZ); const _ValueType m12 = Two * (xy - zw); const _ValueType m13 = Two * (xz + yw);
            const _ValueType m21 = Two * (xy + zw); const _ValueType m22 = One - Two * (sqX + sqZ); const _ValueType m23 = Two * (yz - xw);
            const _ValueType m31 = Two * (xz - yw); const _ValueType m32 = Two * (yz + xw); const _ValueType m33 = One - Two * (sqX + sqY);

            return _Mat4x4(m11, m12, m13, 0.0,
                           m21, m22, m23, 0.0,
                           m31, m32, m33, 0.0,
                           0.0, 0.0, 0.0, 1.0);
            // clang-format on
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion fromRotationMatrix(const _Mat3x3& m) noexcept
        {
            const _ValueType m00 = m[0][0];
            const _ValueType m01 = m[0][1];
            const _ValueType m02 = m[0][2];

            const _ValueType m10 = m[1][0];
            const _ValueType m11 = m[1][1];
            const _ValueType m12 = m[1][2];

            const _ValueType m20 = m[2][0];
            const _ValueType m21 = m[2][1];
            const _ValueType m22 = m[2][2];

            const _ValueType trace = m.getM11() + m.getM22() + m.getM33();
            _ValueType x;
            _ValueType y;
            _ValueType z;
            _ValueType w;

            if (trace > Zero)
            {
                const _ValueType s = std::sqrt(trace + One) * Two;

                w = _ValueType(0.25) * s;
                x = (m21 - m12) / s;
                y = (m02 - m20) / s;
                z = (m10 - m01) / s;
            }
            else if (m00 > m11 && m00 > m22)
            {
                const _ValueType s = std::sqrt(One + m00 - m11 - m22) * Two;

                w = (m21 - m12) / s;
                x = _ValueType(0.25) * s;
                y = (m01 + m10) / s;
                z = (m02 + m20) / s;
            }
            else if (m11 > m22)
            {
                const _ValueType s = std::sqrt(One + m11 - m00 - m22) * Two;

                w = (m02 - m20) / s;
                x = (m01 + m10) / s;
                y = _ValueType(0.25) * s;
                z = (m12 + m21) / s;
            }
            else
            {
                const _ValueType s = std::sqrt(One + m22 - m00 - m11) * Two;

                w = (m10 - m01) / s;
                x = (m02 + m20) / s;
                y = (m12 + m21) / s;
                z = _ValueType(0.25) * s;
            }

            return Quaternion(x, y, z, w);
        }

#if defined(MATH_LIB_INTRINSIC)
        operator _VectorInstrinsic() const noexcept
        {
            return Simd::makeVector4Unaligned(m_data.data());
        }
#endif // defined(MATH_LIB_INTRINSIC)

    private:
        std::array<T, 4> m_data;
    };

    using Quaternionf = Quaternion<float>;
    using Quaterniond = Quaternion<double>;

} // namespace MathLib

#endif // MATH_LIB_QUATERNION_H
