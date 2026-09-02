#ifndef MATH_LIB_QUATERNION_H
#define MATH_LIB_QUATERNION_H

#include <array>
#include <cmath>
#include <type_traits>
#include <span>
#include <MathLibHeader.hpp>

namespace MathLib
{
    // X Y Z W
    // XYZ imaginary part
    // W real Part
    template<typename T>
    requires(std::is_floating_point_v<T>)
    class Quaternion
    {
    public:
#if defined(MATH_LIB_INTRINSIC)
        using _VectorInstrinsic =
            std::conditional_t<std::is_same_v<T, float>, Simd::VectorRegister4Float, Simd::VectorRegister4Double>;
#endif

        using _ValueType = T;

        explicit Quaternion() = default;
        ~Quaternion() = default;

        MATH_LIB_FORCE_INLINE explicit Quaternion(_ValueType x, _ValueType y, _ValueType z, _ValueType w)
            : m_data({x, y, z, w})
        {
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE explicit Quaternion(const std::span<T, 3>& spanXYZ, _ValueType w)
            : m_data({spanXYZ[1], spanXYZ[2], spanXYZ[3], w})
        {
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE explicit Quaternion(const std::span<T, 4>& spanXYZ)
            : m_data({spanXYZ[0], spanXYZ[1], spanXYZ[2], spanXYZ[3]})
        {
            ASSERT_IS_FINITE(*this);
        }

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
            return Quaternion(T(0), T(0), T(0), T(0));
            // clang-format on
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Quaternion identity() noexcept
        {
            // clang-format off
            return Quaternion(T(1), T(0), T(0), T(0));
            // clang-format on
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

        bool isFinite() const
        {
            return std::isfinite(m_data[0]) && std::isfinite(m_data[1]) && std::isfinite(m_data[2]) &&
                   std::isfinite(m_data[3]);
        }

        MATH_LIB_FORCE_INLINE Quaternion& operator+=(const Quaternion& rhs) noexcept
        {
            m_data[0] += rhs.m_data[0];
            m_data[1] += rhs.m_data[1];
            m_data[2] += rhs.m_data[2];
            m_data[3] += rhs.m_data[3];
        }

        MATH_LIB_FORCE_INLINE Quaternion& operator-=(const Quaternion& rhs) noexcept
        {
            m_data[0] -= rhs.m_data[0];
            m_data[1] -= rhs.m_data[1];
            m_data[2] -= rhs.m_data[2];
            m_data[3] -= rhs.m_data[3];
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
            m_data[0] *= scalar;
            m_data[1] *= scalar;
            m_data[2] *= scalar;
            m_data[3] *= scalar;
        }

        MATH_LIB_FORCE_INLINE Quaternion& operator/=(_ValueType scalar) noexcept
        {
            m_data[0] /= scalar;
            m_data[1] /= scalar;
            m_data[2] /= scalar;
            m_data[3] /= scalar;
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

        [[nodiscard]] MATH_LIB_FORCE_INLINE static _ValueType dot(const Quaternion& a, const Quaternion& b) noexcept
        {
            return a.m_data[0] * b.m_data[0] + a.m_data[1] * b.m_data[1] + a.m_data[2] * b.m_data[2] +
                   a.m_data[3] * b.m_data[3];
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
            const _ValueType lenght = length();
            if (fuzzyZero(lenght))
                return *this;

            const _ValueType invLength = T(1) / lenght;
            m_data[0] *= invLength;
            m_data[1] *= invLength;
            m_data[2] *= invLength;
            m_data[3] *= invLength;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Quaternion getNormalize() const
        {
            Quaternion q = *this;
            return q.normalize();
        }

        MATH_LIB_FORCE_INLINE Quaternion& conjugate()
        {
            m_data[0] = -m_data[0];
            m_data[1] = -m_data[1];
            m_data[2] = -m_data[2];
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

            m_data[0] *= -invLengthSq;
            m_data[1] *= -invLengthSq;
            m_data[2] *= -invLengthSq;
            m_data[3] *= invLengthSq;

            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Quaternion getInverse() const noexcept
        {
            Quaternion q = *this;
            return q.inverse();
        }

    private:
        std::array<T, 4> m_data;
    };

    using Quaternionf = Quaternion<float>;
    using Quaterniond = Quaternion<double>;

} // namespace MathLib

#endif // MATH_LIB_QUATERNION_H
