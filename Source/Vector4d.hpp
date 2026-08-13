#ifndef MATH_LIB_VECTOR4D_H
#define MATH_LIB_VECTOR4D_H

#include <array>
#include <cassert>
#include <cmath>
#include <format>
#include <ostream>
#include <span>
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

        MATH_LIB_FORCE_INLINE Vector4& operator+=(const Vector4& _other) noexcept
        {
            m_x += _other.m_x;
            m_y += _other.m_y;
            m_z += _other.m_z;
            m_w += _other.m_w;
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator-=(const Vector4& _other) noexcept
        {
            m_x -= _other.m_x;
            m_y -= _other.m_y;
            m_z -= _other.m_z;
            m_w -= _other.m_w;
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator+(Vector4 _lhs, const Vector4& _rhs) noexcept
        {
            _lhs += _rhs;
            return _lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator-(Vector4 _lhs, const Vector4& _rhs) noexcept
        {
            _lhs -= _rhs;
            return _lhs;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator+=(const double _scalar) noexcept
        {
            m_x += _scalar;
            m_y += _scalar;
            m_z += _scalar;
            m_w += _scalar;
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator-=(const double _scalar) noexcept
        {
            m_x -= _scalar;
            m_y -= _scalar;
            m_z -= _scalar;
            m_w -= _scalar;
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator*=(double _scalar) noexcept
        {
            m_x *= _scalar;
            m_y *= _scalar;
            m_z *= _scalar;
            m_w *= _scalar;
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator/=(double _scalar) noexcept
        {
            m_x /= _scalar;
            m_y /= _scalar;
            m_z /= _scalar;
            m_w /= _scalar;
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator+(Vector4 _lhs, const double _scalar) noexcept
        {
            _lhs += _scalar;
            return _lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator-(Vector4 _lhs, const double _scalar) noexcept
        {
            _lhs -= _scalar;
            return _lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator*(Vector4 _lhs, const double _scalar) noexcept
        {
            _lhs *= _scalar;
            return _lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator/(Vector4 _lhs, const double _scalar) noexcept
        {
            _lhs /= _scalar;
            return _lhs;
        }

        [[nodiscard]] bool operator==(const Vector4& _other) const
        {
            return FuzzyZero(m_x - _other.m_x) && FuzzyZero(m_y - _other.m_y) && FuzzyZero(m_z - _other.m_z) &&
                   FuzzyZero(m_w - _other.m_w);
        }

        [[nodiscard]] bool operator!=(const Vector4& _other) const
        {
            return !(*this == _other);
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

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 getNormalize() const
        {
            const double currentLength = length();

            if (FuzzyZero(currentLength))
            {
                return *this;
            }

            return *this / currentLength;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 getNormalizeFast() const
        {
            const double currentLength = length();

            if (FuzzyZero(currentLength))
            {
                return *this;
            }

            const double invLength = 1.0 / currentLength;
            return *this * invLength;
        }

        Vector4& normalize()
        {
            const double currentLength = length();

            if (FuzzyZero(currentLength))
            {
                return *this;
            }

            *this /= currentLength;
            return *this;
        }

        Vector4& normalizeFast()
        {
            const double currentLength = length();

            if (FuzzyZero(currentLength))
            {
                return *this;
            }

            const double invLength = 1.0 / currentLength;
            *this *= invLength;
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

        MATH_LIB_FORCE_INLINE void streamToUnalignedDouble(const std::span<double, 4>& _span) const
        {
            _span[0] = m_x;
            _span[1] = m_y;
            _span[2] = m_z;
            _span[3] = m_w;
        }

        MATH_LIB_FORCE_INLINE void streamToUnalignedDouble(double* const _ptr) const
        {
            streamToUnalignedDouble(std::span<double, 4>(_ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void streamToUnAlignedFloat(const std::span<float, 4>& _span) const
        {
            _span[0] = static_cast<float>(m_x);
            _span[1] = static_cast<float>(m_y);
            _span[2] = static_cast<float>(m_z);
            _span[3] = static_cast<float>(m_w);
        }

        MATH_LIB_FORCE_INLINE void streamToUnAlignedFloat(float* const _ptr) const
        {
            streamToUnAlignedFloat(std::span<float, 4>(_ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void streamToAlignedDouble(const std::span<double, 4>& _span) const
        {
            assert(isAligned<AVX_AVX2_ALIGNEMENT>(_span.data()));

            _span[0] = m_x;
            _span[1] = m_y;
            _span[2] = m_z;
            _span[3] = m_w;
        }

        MATH_LIB_FORCE_INLINE void streamToAlignedDouble(double* const _ptr) const
        {
            streamToAlignedDouble(std::span<double, 4>(_ptr, 4));
        }

        MATH_LIB_FORCE_INLINE void streamToAlignedFloat(const std::span<float, 4>& _span) const
        {
            assert(isAligned<SSE_ALIGNEMENT>(_span.data()));

            _span[0] = static_cast<float>(m_x);
            _span[1] = static_cast<float>(m_y);
            _span[2] = static_cast<float>(m_z);
            _span[3] = static_cast<float>(m_w);
        }

        MATH_LIB_FORCE_INLINE void streamToAlignedFloat(float* const _ptr) const
        {
            streamToUnAlignedFloat(std::span<float, 4>(_ptr, 4));
        }

        friend MATH_LIB_FORCE_INLINE std::ostream& operator<<(std::ostream& _ostream, const Vector4& _vec)
        {
            alignas(AVX_AVX2_ALIGNEMENT) std::array<double, 4> data;
            _vec.streamToUnalignedDouble(data);
            _ostream << "x: " << data[0] << ", y: " << data[1] << ", z: " << data[2] << ", w: " << data[3];

            return _ostream;
        }

    private:
        double m_x;
        double m_y;
        double m_z;
        double m_w;
    };

    using Vector4d = Vector4<double>;

} // MathLib

template<>
struct std::formatter<MathLib::Vector4d>
{
    constexpr static std::format_parse_context::const_iterator parse(std::format_parse_context& _ctx)
    {
        return _ctx.begin();
    }

    static std::format_context::iterator format(const MathLib::Vector4d& _v, std::format_context& _ctx)
    {
        std::array<double, 4> data;

        _v.streamToUnalignedDouble(data);

        return std::format_to(_ctx.out(), "x: {}, y: {}, z: {}, w: {}", data[0], data[1], data[2], data[3]);
    }
};

#endif // MATH_LIB_VECTOR4D_H
