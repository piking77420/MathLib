#ifndef MATH_LIB_VECTOR3D_H
#define MATH_LIB_VECTOR3D_H

#include <array>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <format>
#include <ostream>
#include <span>
#include <MathLibHeader.hpp>

// NOLINTBEGIN(clang-analyzer-optin.cplusplus.UninitializedObject)

namespace MathLib
{
    template<typename T>
    class Vector3;

    template<>
    class Vector3<double>
    {
    public:
        explicit Vector3() = default;

        ~Vector3() = default;

        MATH_LIB_FORCE_INLINE explicit Vector3(double _x, double _y, double _z)
            : m_x(_x)
            , m_y(_y)
            , m_z(_z)
        {
            ASSERT_IS_FINITE(*this)
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

        MATH_LIB_FORCE_INLINE void setX(double _x) noexcept
        {
            m_x = _x;
            ASSERT_IS_FINITE(*this)
        }

        MATH_LIB_FORCE_INLINE void setY(double _y) noexcept
        {
            m_y = _y;
            ASSERT_IS_FINITE(*this)
        }

        MATH_LIB_FORCE_INLINE void setZ(double _z) noexcept
        {
            m_z = _z;
            ASSERT_IS_FINITE(*this)
        }

        MATH_LIB_FORCE_INLINE Vector3& operator+=(const Vector3& _other) noexcept
        {
            m_x += _other.m_x;
            m_y += _other.m_y;
            m_z += _other.m_z;
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator-=(const Vector3& _other) noexcept
        {
            m_x -= _other.m_x;
            m_y -= _other.m_y;
            m_z -= _other.m_z;
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator+(Vector3 _lhs, const Vector3& _rhs) noexcept
        {
            _lhs += _rhs;
            return _lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator-(Vector3 _lhs, const Vector3& _rhs) noexcept
        {
            _lhs -= _rhs;
            return _lhs;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator+=(const double _scalar) noexcept
        {
            m_x += _scalar;
            m_y += _scalar;
            m_z += _scalar;
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator-=(const double _scalar) noexcept
        {
            m_x -= _scalar;
            m_y -= _scalar;
            m_z -= _scalar;
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator*=(double _scalar) noexcept
        {
            m_x *= _scalar;
            m_y *= _scalar;
            m_z *= _scalar;
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector3& operator/=(double _scalar) noexcept
        {
            m_x /= _scalar;
            m_y /= _scalar;
            m_z /= _scalar;
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator+(Vector3 _lhs, const double _scalar) noexcept
        {
            _lhs += _scalar;
            return _lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator-(Vector3 _lhs, const double _scalar) noexcept
        {
            _lhs -= _scalar;
            return _lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator*(Vector3 _lhs, const double _scalar) noexcept
        {
            _lhs *= _scalar;
            return _lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector3 operator/(Vector3 _lhs, const double _scalar) noexcept
        {
            _lhs /= _scalar;
            return _lhs;
        }

        [[nodiscard]] bool operator==(const Vector3& _other) const
        {
            return fuzzyZero(m_x - _other.m_x) && fuzzyZero(m_y - _other.m_y) && fuzzyZero(m_z - _other.m_z);
        }

        [[nodiscard]] bool operator!=(const Vector3& _other) const
        {
            return !(*this == _other);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector3 operator-() const noexcept
        {
            ASSERT_IS_FINITE(*this)
            return Vector3(-m_x, -m_y, -m_z);
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double dot(const Vector3& _a, const Vector3& _b)
        {
            ASSERT_IS_FINITE(_a)
            ASSERT_IS_FINITE(_b)
            return (_a.m_x * _b.m_x) + (_a.m_y * _b.m_y) + (_a.m_z * _b.m_z);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double lengthSquare() const
        {
            ASSERT_IS_FINITE(*this)
            return dot(*this, *this);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double length() const
        {
            ASSERT_IS_FINITE(*this)
            return std::sqrt(lengthSquare());
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double distanceSquare(const Vector3& _a, const Vector3& _b)
        {
            ASSERT_IS_FINITE(_a)
            ASSERT_IS_FINITE(_b)
            return (_b - _a).lengthSquare();
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE double distance(const Vector3& _a, const Vector3& _b)
        {
            return std::sqrt(distanceSquare(_a, _b));
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector3 getNormalize() const
        {
            const double currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            return *this / currentLength;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector3 getNormalizeFast() const
        {
            const double currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            const double invLength = 1.0 / currentLength;
            return *this * invLength;
        }

        Vector3& normalize()
        {
            const double currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            *this /= currentLength;
            return *this;
        }

        Vector3& normalizeFast()
        {
            const double currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            const double invLength = 1.0 / currentLength;
            *this *= invLength;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector3 min(const Vector3& _a, const Vector3& _b) noexcept
        {
            ASSERT_IS_FINITE(_a)
            ASSERT_IS_FINITE(_b)
            return Vector3(std::min(_a.getX(), _b.getX()), std::min(_a.getY(), _b.getY()),
                           std::min(_a.getZ(), _b.getZ()));
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector3 max(const Vector3& _a, const Vector3& _b) noexcept
        {
            ASSERT_IS_FINITE(_a)
            ASSERT_IS_FINITE(_b)
            return Vector3(std::max(_a.getX(), _b.getX()), std::max(_a.getY(), _b.getY()),
                           std::max(_a.getZ(), _b.getZ()));
        }

        static Vector3 unitX()
        {
            return Vector3(1.0, 0.0, 0.0);
        }

        static Vector3 unitY()
        {
            return Vector3(0.0, 1.0, 0.0);
        }

        static Vector3 unitZ()
        {
            return Vector3(0.0, 0.0, 1.0);
        }

        static Vector3 zero()
        {
            return Vector3(0.0, 0.0, 0.0);
        }

        MATH_LIB_FORCE_INLINE void storeToUnalignedDouble(const std::span<double, 3>& _span) const
        {
            ASSERT_IS_FINITE(*this)
            _span[0] = m_x;
            _span[1] = m_y;
            _span[2] = m_z;
        }

        MATH_LIB_FORCE_INLINE void storeToUnalignedDouble(double* const _ptr) const
        {
            storeToUnalignedDouble(std::span<double, 3>(_ptr, 3));
        }

        MATH_LIB_FORCE_INLINE void storeToUnAlignedFloat(const std::span<float, 3>& _span) const
        {
            ASSERT_IS_FINITE(*this)
            _span[0] = static_cast<float>(m_x);
            _span[1] = static_cast<float>(m_y);
            _span[2] = static_cast<float>(m_z);
        }

        MATH_LIB_FORCE_INLINE void storeToUnAlignedFloat(float* const _ptr) const
        {
            storeToUnAlignedFloat(std::span<float, 3>(_ptr, 3));
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedDouble(const std::span<double, 3>& _span) const
        {
            ASSERT_IS_FINITE(*this)
            MATHLIB_ASSERT(isAligned<AVX_AVX2_ALIGNEMENT>(_span.data()));

            _span[0] = m_x;
            _span[1] = m_y;
            _span[2] = m_z;
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedDouble(double* const _ptr) const
        {
            storeToAlignedDouble(std::span<double, 3>(_ptr, 3));
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedFloat(const std::span<float, 3>& _span) const
        {
            ASSERT_IS_FINITE(*this)
            MATHLIB_ASSERT(isAligned<SSE_ALIGNEMENT>(_span.data()));

            _span[0] = static_cast<float>(m_x);
            _span[1] = static_cast<float>(m_y);
            _span[2] = static_cast<float>(m_z);
        }

        MATH_LIB_FORCE_INLINE void storeToAlignedFloat(float* const _ptr) const
        {
            storeToUnAlignedFloat(std::span<float, 3>(_ptr, 3));
        }

        MATH_LIB_FORCE_INLINE void fromUnalignedDouble(const std::span<const double, 3>& _span)
        {
            m_x = _span[0];
            m_y = _span[1];
            m_z = _span[2];
            ASSERT_IS_FINITE(*this)
        }

        MATH_LIB_FORCE_INLINE void fromUnalignedDouble(double* const _ptr)
        {
            fromUnalignedDouble(std::span<double, 3>(_ptr, 3));
        }

        MATH_LIB_FORCE_INLINE void fromUnAlignedFloat(const std::span<const float, 3>& _span)
        {
            m_x = static_cast<double>(_span[0]);
            m_y = static_cast<double>(_span[1]);
            m_z = static_cast<double>(_span[2]);
            ASSERT_IS_FINITE(*this)
        }

        MATH_LIB_FORCE_INLINE void fromUnAlignedFloat(float* const _ptr)
        {
            fromUnAlignedFloat(std::span<float, 3>(_ptr, 3));
        }

        MATH_LIB_FORCE_INLINE void fromAlignedDouble(const std::span<const double, 3>& _span)
        {
            MATHLIB_ASSERT(isAligned<AVX_AVX2_ALIGNEMENT>(_span.data()));

            m_x = _span[0];
            m_y = _span[1];
            m_z = _span[2];

            ASSERT_IS_FINITE(*this)
        }

        MATH_LIB_FORCE_INLINE void fromAlignedDouble(const double* const _ptr)
        {
            fromAlignedDouble(std::span<const double, 3>(_ptr, 3));
        }

        MATH_LIB_FORCE_INLINE void fromAlignedFloat(const std::span<const float, 3>& _span)
        {
            MATHLIB_ASSERT(isAligned<SSE_ALIGNEMENT>(_span.data()));

            m_x = static_cast<double>(_span[0]);
            m_y = static_cast<double>(_span[1]);
            m_z = static_cast<double>(_span[2]);

            ASSERT_IS_FINITE(*this)
        }

        MATH_LIB_FORCE_INLINE void fromAlignedFloat(const float* const _ptr)
        {
            fromAlignedFloat(std::span<const float, 3>(_ptr, 3));
        }

        friend MATH_LIB_FORCE_INLINE std::ostream& operator<<(std::ostream& _ostream, const Vector3& _vec)
        {
            std::array<double, 3> data;
            _vec.storeToUnalignedDouble(data);
            _ostream << "x: " << data[0] << ", y: " << data[1] << ", z: " << data[2];

            return _ostream;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE bool isFinite() const
        {
            return std::isfinite(m_x) && std::isfinite(m_y) && std::isfinite(m_z);
        }

    private:
        double m_x;
        double m_y;
        double m_z;
        [[maybe_unused]] double m_w; // not used deliberately
    };

    using Vector3d = Vector3<double>;

} // MathLib

// NOLINTEND(clang-analyzer-optin.cplusplus.UninitializedObject)

template<>
struct std::formatter<MathLib::Vector3d>
{
    constexpr static std::format_parse_context::const_iterator parse(std::format_parse_context& _ctx)
    {
        return _ctx.begin();
    }

    static std::format_context::iterator format(const MathLib::Vector3d& _v, std::format_context& _ctx)
    {
        std::array<double, 3> data;

        _v.storeToUnalignedDouble(data);

        return std::format_to(_ctx.out(), "x: {}, y: {}, z: {}", data[0], data[1], data[2]);
    }
};

#endif // MATH_LIB_VECTOR3D_H
