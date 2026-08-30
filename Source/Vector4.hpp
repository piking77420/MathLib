#ifndef MATH_LIB_VECTOR4_H
#define MATH_LIB_VECTOR4_H

#include <array>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <format>
#include <ostream>
#include <span>
#include <MathLibHeader.hpp>
#include <AVX.hpp>
#include <NEON.hpp>
#include <SSE.hpp>

namespace MathLib
{
    template<typename T>
        requires(std::is_floating_point_v<T>)
    class Vector2;

    template<typename T>
        requires(std::is_floating_point_v<T>)
    class Vector3;

    template<typename T>
        requires(std::is_floating_point_v<T>)
    class alignas(std::is_same_v<T, float> ? VECTOR4F_ALIGNEMENT : VECTOR4D_ALIGNEMENT) Vector4 // TODO is align or not
    {
    public:
#if defined(MATH_LIB_INTRINSIC)
        using _VectorInstrinsic =
            std::conditional_t<std::is_same_v<T, float>, Simd::VectorRegister4Float, Simd::VectorRegister4Double>;
#endif

        explicit Vector4() = default;

        ~Vector4() = default;

        MATH_LIB_FORCE_INLINE explicit Vector4(T x, T y, T z, T w)
            : m_data({x, y, z, w})
        {
            ASSERT_IS_FINITE(*this);
        }

        MATH_LIB_FORCE_INLINE explicit Vector4(T x)
            : m_data({x, x, x, x})
        {
            ASSERT_IS_FINITE(*this);
        }

#if defined(MATH_LIB_INTRINSIC)
        MATH_LIB_FORCE_INLINE Vector4(const _VectorInstrinsic& reg) noexcept
        {
            Simd::storeUnaligned(reg, m_data.data());
        }
#endif // defined(MATH_LIB_INTRINSIC)

        [[nodiscard]] MATH_LIB_FORCE_INLINE const T* data() const noexcept
        {
            return m_data.data();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T* data() noexcept
        {
            return m_data.data();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getX() const noexcept
        {
            return m_data[0];
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getY() const noexcept
        {
            return m_data[1];
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getZ() const noexcept
        {
            return m_data[2];
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getW() const noexcept
        {
            return m_data[3];
        }

        MATH_LIB_FORCE_INLINE void setX(T x) noexcept
        {
            m_data[0] = x;
        }

        MATH_LIB_FORCE_INLINE void setY(T y) noexcept
        {
            m_data[1] = y;
        }

        MATH_LIB_FORCE_INLINE void setZ(T z) noexcept
        {
            m_data[2] = z;
        }

        MATH_LIB_FORCE_INLINE void setW(T w) noexcept
        {
            m_data[3] = w;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator+=(const Vector4& other) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Vector4(Simd::add(*this, other));
#else
            m_data[0] += other.m_data[0];
            m_data[1] += other.m_data[1];
            m_data[2] += other.m_data[2];
            m_data[3] += other.m_data[3];
#endif // defined(MATH_LIB_INTRINSIC)

            ASSERT_IS_FINITE(*this) return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator-=(const Vector4& other) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Vector4(Simd::sub(*this, other));
#else
            m_data[0] -= other.m_data[0];
            m_data[1] -= other.m_data[1];
            m_data[2] -= other.m_data[2];
            m_data[3] -= other.m_data[3];
#endif // defined(MATH_LIB_INTRINSIC)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator*=(const Vector4& other) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Vector4(Simd::mul(*this, other));
#else
            m_data[0] *= other.m_data[0];
            m_data[1] *= other.m_data[1];
            m_data[2] *= other.m_data[2];
            m_data[3] *= other.m_data[3];
#endif // defined(MATH_LIB_INTRINSIC)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator/=(const Vector4& other) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Vector4(Simd::div(*this, other));
#else
            m_data[0] /= other.m_data[0];
            m_data[1] /= other.m_data[1];
            m_data[2] /= other.m_data[2];
            m_data[3] /= other.m_data[3];
#endif // defined(MATH_LIB_INTRINSIC)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator+(Vector4 lhs, const Vector4& _rhs) noexcept
        {
            lhs += _rhs;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator-(Vector4 lhs, const Vector4& _rhs) noexcept
        {
            lhs -= _rhs;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator*(Vector4 lhs, const Vector4& _rhs) noexcept
        {
            lhs *= _rhs;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator/(Vector4 lhs, const Vector4& _rhs) noexcept
        {
            lhs /= _rhs;
            return lhs;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator+=(const T scalar) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Vector4(Simd::add(*this, Simd::makeVector4(scalar)));
#else
            m_data[0] += scalar;
            m_data[1] += scalar;
            m_data[2] += scalar;
            m_data[3] += scalar;
#endif // defined(MATH_LIB_INTRINSIC)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator-=(const T scalar) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Vector4(Simd::sub(*this, Simd::makeVector4(scalar)));
#else
            m_data[0] -= scalar;
            m_data[1] -= scalar;
            m_data[2] -= scalar;
            m_data[3] -= scalar;
#endif // defined(MATH_LIB_INTRINSIC)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator*=(T scalar) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Vector4(Simd::mul(*this, Simd::makeVector4(scalar)));
#else
            m_data[0] *= scalar;
            m_data[1] *= scalar;
            m_data[2] *= scalar;
            m_data[3] *= scalar;
#endif // defined(MATH_LIB_INTRINSIC)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        MATH_LIB_FORCE_INLINE Vector4& operator/=(T scalar) noexcept
        {
#if defined(MATH_LIB_INTRINSIC)
            *this = Vector4(Simd::div(*this, Simd::makeVector4(scalar)));
#else
            m_data[0] /= scalar;
            m_data[1] /= scalar;
            m_data[2] /= scalar;
            m_data[3] /= scalar;
#endif // defined(MATH_LIB_INTRINSIC)
            ASSERT_IS_FINITE(*this)
            return *this;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator+(Vector4 lhs, const T scalar) noexcept
        {
            lhs += scalar;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator-(Vector4 lhs, const T scalar) noexcept
        {
            lhs -= scalar;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator*(Vector4 lhs, const T scalar) noexcept
        {
            lhs *= scalar;
            return lhs;
        }

        [[nodiscard]] friend MATH_LIB_FORCE_INLINE Vector4 operator/(Vector4 lhs, const T scalar) noexcept
        {
            lhs /= scalar;
            return lhs;
        }

        [[nodiscard]] bool operator==(const Vector4& other) const
        {
            return fuzzyZero(m_data[0] - other.m_data[0]) && fuzzyZero(m_data[1] - other.m_data[1]) &&
                   fuzzyZero(m_data[2] - other.m_data[2]) && fuzzyZero(m_data[3] - other.m_data[3]);
        }

        [[nodiscard]] bool operator!=(const Vector4& other) const
        {
            return !(*this == other);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 operator-() const noexcept
        {
            return Vector4(-m_data[0], -m_data[1], -m_data[2], -m_data[3]);
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE T dot(const Vector4& a, const Vector4& b)
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)

            const T x2 = a.getX() * b.getX();
            const T y2 = a.getY() * b.getY();
            const T z2 = a.getZ() * b.getZ();
            const T w2 = a.getW() * b.getW();
            return x2 + y2 + z2 + w2;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T lengthSquare() const
        {
            return dot(*this, *this);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T length() const
        {
            return std::sqrt(lengthSquare());
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE T distanceSquare(const Vector4& a, const Vector4& b)
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
            return (b - a).lengthSquare();
        }

        [[nodiscard]] static MATH_LIB_FORCE_INLINE T distance(const Vector4& a, const Vector4& b)
        {
            return std::sqrt(distanceSquare(a, b));
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 getNormalize() const
        {
            const T currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            return *this / currentLength;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 getNormalizeFast() const
        {
            const T currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            const T invLength = 1.0 / currentLength;
            return *this * invLength;
        }

        Vector4& normalize()
        {
            const T currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            *this /= currentLength;
            return *this;
        }

        Vector4& normalizeFast()
        {
            const T currentLength = length();

            if (fuzzyZero(currentLength))
            {
                return *this;
            }

            const T invLength = 1.0 / currentLength;
            *this *= invLength;
            return *this;
        }

        [[nodiscard]] bool isHomogeneous() const
        {
            return fuzzyEqual(getW(), static_cast<T>(1.0));
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector4 cross(const Vector4& a, const Vector4& b,
                                                                 const Vector4& c) noexcept
        {
            // Get all scalar
            const T ax = a.getX();
            const T ay = a.getY();
            const T az = a.getZ();
            const T aw = a.getW();

            const T bx = b.getX();
            const T by = b.getY();
            const T bz = b.getZ();
            const T bw = b.getW();

            const T cx = c.getX();
            const T cy = c.getY();
            const T cz = c.getZ();
            const T cw = c.getW();

            // manually do the cors product or determinant
            const T mYZ = by * cz - bz * cy;
            const T mYW = by * cw - bw * cy;
            const T mZW = bz * cw - bw * cz;

            const T mXZ = bx * cz - bz * cx;
            const T mXW = bx * cw - bw * cx;

            const T mXY = bx * cy - by * cx;

            // manuall dot
            return Vector4(ay * mZW - az * mYW + aw * mYZ, -(ax * mZW - az * mXW + aw * mXZ),
                           ax * mYW - ay * mXW + aw * mXY, -(ax * mYZ - ay * mXZ + az * mXY));
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector4 min(const Vector4& a, const Vector4& b) noexcept
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
#if defined(MATH_LIB_INTRINSIC)
            return Vector4(Simd::min(a, b));
#else
            return Vector4(std::min(a.getX(), b.getX()), std::min(a.getY(), b.getY()), std::min(a.getZ(), b.getZ()),
                           std::min(a.getW(), b.getW()));
#endif // defined(MATH_LIB_INTRINSIC)
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector4 max(const Vector4& a, const Vector4& b) noexcept
        {
            ASSERT_IS_FINITE(a)
            ASSERT_IS_FINITE(b)
#if defined(MATH_LIB_INTRINSIC)
            return Vector4(Simd::max(a, b));
#else
            return Vector4(std::max(a.getX(), b.getX()), std::max(a.getY(), b.getY()), std::max(a.getZ(), b.getZ()),
                           std::max(a.getW(), b.getW()));
#endif // defined(MATH_LIB_INTRINSIC)
        }

        static Vector4 unitX()
        {
            return Vector4(1.0, 0.0, 0.0, 0.0);
        }

        static Vector4 unitY()
        {
            return Vector4(0.0, 1.0, 0.0, 0.0);
        }

        static Vector4 unitZ()
        {
            return Vector4(0.0, 0.0, 1.0, 0.0);
        }

        static Vector4 unitW()
        {
            return Vector4(0.0, 0.0, 0.0, 1.0);
        }

        static Vector4 zero()
        {
            return Vector4(0.0, 0.0, 0.0, 0.0);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 abs() const noexcept
        {
            ASSERT_IS_FINITE(*this);
            return Vector4(std::abs(getX()), std::abs(m_data[1]), std::abs(m_data[2]), std::abs(m_data[3]));
        }

        friend MATH_LIB_FORCE_INLINE std::ostream& operator<<(std::ostream& ostream, const Vector4& vec)
        {
            ostream << "x: " << vec.m_data[0] << ", y: " << vec.m_data[1] << ", z: " << vec.m_data[2]
                    << ", w: " << vec.m_data[3];

            return ostream;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE bool isFinite() const
        {
            return std::isfinite(getX()) && std::isfinite(m_data[1]) && std::isfinite(m_data[2]) &&
                   std::isfinite(m_data[3]);
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 xywz() const noexcept
        {
            return Vector4(getX(), getY(), getW(), getZ());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 xzyw() const noexcept
        {
            return Vector4(getX(), getZ(), getY(), getW());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 xzwy() const noexcept
        {
            return Vector4(getX(), getZ(), getW(), getY());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 xwyz() const noexcept
        {
            return Vector4(getX(), getW(), getY(), getZ());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 xwzy() const noexcept
        {
            return Vector4(getX(), getW(), getZ(), getY());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 yxzw() const noexcept
        {
            return Vector4(getY(), getX(), getZ(), getW());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 yxwz() const noexcept
        {
            return Vector4(getY(), getX(), getW(), getZ());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 yzxw() const noexcept
        {
            return Vector4(getY(), getZ(), getX(), getW());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 yzwx() const noexcept
        {
            return Vector4(getY(), getZ(), getW(), getX());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 ywxz() const noexcept
        {
            return Vector4(getY(), getW(), getX(), getZ());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 ywzx() const noexcept
        {
            return Vector4(getY(), getW(), getZ(), getX());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zxyw() const noexcept
        {
            return Vector4(getZ(), getX(), getY(), getW());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zxwy() const noexcept
        {
            return Vector4(getZ(), getX(), getW(), getY());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zyxw() const noexcept
        {
            return Vector4(getZ(), getY(), getX(), getW());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zywx() const noexcept
        {
            return Vector4(getZ(), getY(), getW(), getX());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zwxy() const noexcept
        {
            return Vector4(getZ(), getW(), getX(), getY());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 zwyx() const noexcept
        {
            return Vector4(getZ(), getW(), getY(), getX());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wxyz() const noexcept
        {
            return Vector4(getW(), getX(), getY(), getZ());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wxzy() const noexcept
        {

            return Vector4(getW(), getX(), getZ(), getY());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wyxz() const noexcept
        {
            return Vector4(getW(), getY(), getX(), getZ());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wyzx() const noexcept
        {
            return Vector4(getW(), getY(), getZ(), getX());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wzxy() const noexcept
        {
            return Vector4(getW(), getZ(), getX(), getY());
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector4 wzyx() const noexcept
        {
            return Vector4(getW(), getZ(), getY(), getX());
        }

        Vector3<T> xyz() const noexcept
        {
            return static_cast<Vector3<T>>(*this);
        };

        Vector3<T> xzy() const noexcept
        {
            return static_cast<Vector3<T>>(xzyw());
        }

        Vector3<T> yxz() const noexcept
        {
            return static_cast<Vector3<T>>(yxzw());
        }
        Vector3<T> yzx() const noexcept
        {
            return static_cast<Vector3<T>>(yzxw());
        }

        Vector3<T> zxy() const noexcept
        {
            return static_cast<Vector3<T>>(zxyw());
        }
        Vector3<T> zyx() const noexcept
        {
            return static_cast<Vector3<T>>(zyxw());
        }

        Vector2<T> xy() const noexcept
        {
            return static_cast<Vector2<T>>(*this);
        }

        Vector2<T> xz() const noexcept
        {
            return static_cast<Vector2<T>>(xzwy());
        }

        Vector2<T> xw() const noexcept
        {
            return static_cast<Vector2<T>>(xwyz());
        }

        Vector2<T> yx() const noexcept
        {
            return static_cast<Vector2<T>>(yxzw());
        }

        Vector2<T> yz() const noexcept
        {
            return static_cast<Vector2<T>>(yzxw());
        }

        Vector2<T> yw() const noexcept
        {
            return static_cast<Vector2<T>>(ywxz());
        }

        Vector2<T> zx() const noexcept
        {
            return static_cast<Vector2<T>>(zxyw());
        }

        Vector2<T> zy() const noexcept
        {
            return static_cast<Vector2<T>>(zywx());
        }

        Vector2<T> zw() const noexcept
        {
            return static_cast<Vector2<T>>(zwxy());
        }

        Vector2<T> wx() const noexcept
        {
            return static_cast<Vector2<T>>(wxyz());
        }

        Vector2<T> wy() const noexcept
        {
            return static_cast<Vector2<T>>(wyxz());
        }

        Vector2<T> wz() const noexcept
        {
            return static_cast<Vector2<T>>(wzxy());
        }

        operator Vector3<T>() const noexcept
        {
            return Vector3<T>(getX(), getY(), getZ());
        }

        operator Vector2<T>() const noexcept
        {
            return Vector2<T>(getX(), getY());
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

    using Vector4f = Vector4<float>;
    using Vector4d = Vector4<double>;

} // MathLib

template<typename T>
struct std::formatter<MathLib::Vector4<T>, char>
{
    constexpr static std::format_parse_context::const_iterator parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    static std::format_context::iterator format(const MathLib::Vector4<T>& v, std::format_context& ctx)
    {
        return std::format_to(ctx.out(), "x: {}, y: {}, z: {}, w: {}", v.getX(), v.getY(), v.getZ(), v.getW());
    }
};

#endif // MATH_LIB_VECTOR4_H
