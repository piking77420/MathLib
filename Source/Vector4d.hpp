#ifndef MATH_LIB_VECTOR4D_H
#define MATH_LIB_VECTOR4D_H

#include <cmath>
#include <MathLibHeader.hpp>

namespace MathLib
{
    template<typename T>
    class Vector4;

    template<>
    class Vector4<double>
    {
    public:
        Vector4() = default;

        ~Vector4() = default;

        MATH_LIB_FORCE_INLINE Vector4(double _x, double _y, double _z, double _w)
            : m_x(_x)
            , m_y(_y)
            , m_z(_z)
            , m_w(_w)
        {
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getX() const noexcept
        {
            return m_x;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getY() const noexcept
        {
            return m_y;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getZ() const noexcept
        {
            return m_z;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getW() const noexcept
        {
            return m_w;
        }

        MATH_LIB_FORCE_INLINE void setX(double _x) noexcept
        {
            m_x = _x;
        }

        MATH_LIB_FORCE_INLINE void setY(double _y) noexcept
        {
            m_y = _y;
        }

        MATH_LIB_FORCE_INLINE void setZ(double _z) noexcept
        {
            m_z = _z;
        }

        MATH_LIB_FORCE_INLINE void setW(double _w) noexcept
        {
            m_w = _w;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 operator+(const Vector4& _other) const
        {
            return {m_x + _other.m_x, m_y + _other.m_y, m_z + _other.m_z, m_w + _other.m_w};
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 operator-(const Vector4& _other) const
        {
            return {m_x - _other.m_x, m_y - _other.m_y, m_z - _other.m_z, m_w - _other.m_w};
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4& operator+=(const Vector4& _other) noexcept
        {
            m_x += _other.m_x;
            m_y += _other.m_y;
            m_z += _other.m_z;
            m_w += _other.m_w;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4& operator-=(const Vector4& _other) noexcept
        {
            m_x -= _other.m_x;
            m_y -= _other.m_y;
            m_z -= _other.m_z;
            m_w -= _other.m_w;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 operator+(const double _scalar) const
        {
            return {m_x + _scalar, m_y + _scalar, m_z + _scalar, m_w + _scalar};
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 operator-(const double _scalar) const
        {
            return {m_x - _scalar, m_y - _scalar, m_z - _scalar, m_w - _scalar};
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 operator*(const double _scalar) const
        {
            return {m_x * _scalar, m_y * _scalar, m_z * _scalar, m_w * _scalar};
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 operator/(const double _scalar) const
        {
            return {m_x / _scalar, m_y / _scalar, m_z / _scalar, m_w / _scalar};
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4& operator*=(double _scalar) noexcept
        {
            m_x *= _scalar;
            m_y *= _scalar;
            m_z *= _scalar;
            m_w *= _scalar;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4& operator/=(double _scalar) noexcept
        {
            m_x /= _scalar;
            m_y /= _scalar;
            m_z /= _scalar;
            m_w /= _scalar;
            return *this;
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double dot(const Vector4& _a, const Vector4& _b)
        {
            return (_a.m_x * _b.m_x) + (_a.m_y * _b.m_y) + (_a.m_z * _b.m_z) + (_a.m_w * _b.m_w);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double lengthSquare() const
        {
            return dot(*this, *this);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double length() const
        {
            return std::sqrt(lengthSquare());
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double distanceSquare(const Vector4& _a, const Vector4& _b)
        {
            return (_b - _a).lengthSquare();
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double distance(const Vector4& _a, const Vector4& _b)
        {
            return std::sqrt(distanceSquare(_a, _b));
        }

        [[nodiscard]] bool operator==(const Vector4& _other) const
        {
            return FuzzyZero(m_x - _other.m_x) && FuzzyZero(m_y - _other.m_y) && FuzzyZero(m_z - _other.m_z) &&
                   FuzzyZero(m_w - _other.m_w);
        }

        [[nodiscard]] bool operator!=(const Vector4& _other) const
        {
            return !this->operator==(_other);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 getNormalize() const
        {
            const double currentlength = length();

            if (FuzzyZero(currentlength))
            {
                return *this;
            }

            return *this / currentlength;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 getNormalizeFast() const
        {
            const double currentlength = length();

            if (FuzzyZero(currentlength))
            {
                return *this;
            }
            const double invCurrentlength = 1.0 / currentlength;

            return *this * invCurrentlength;
        }

        [[nodiscard]] Vector4& normalize()
        {
            const double currentlength = length();

            if (!FuzzyZero(currentlength))
            {
                *this = *this / currentlength;
            }

            return *this;
        }

        [[nodiscard]] Vector4& normalizeFast()
        {
            const double currentlength = length();

            if (!FuzzyZero(currentlength))
            {
                const double invCurrentlength = 1.0 / currentlength;
                *this = *this * invCurrentlength;
            }

            return *this;
        }

        [[nodiscard]] bool isHomogeneous() const
        {
            return FuzzyEqual(m_w, 1.0);
        }

        static Vector4 unitX()
        {
            return {1.0, 0.0, 0.0, 0.0};
        }

        static Vector4 unitY()
        {
            return {0.0, 1.0, 0.0, 0.0};
        }

        static Vector4 unitZ()
        {
            return {0.0, 0.0, 1.0, 0.0};
        }

        static Vector4 unitW()
        {
            return {0.0, 0.0, 0.0, 1.0};
        }

        static Vector4 zero()
        {
            return {0.0, 0.0, 0.0, 1.0};
        }

    private:
        double m_x;
        double m_y;
        double m_z;
        double m_w;
    };

    using Vector4d = Vector4<double>;

} // MathLib

#endif // MATH_LIB_VECTOR4D_H