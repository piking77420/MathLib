#ifndef MATH_LIB_VECTOR4_H
#define MATH_LIB_VECTOR4_H

#include <MathLibHeader.hpp>

namespace MathLib
{
    template<typename T>
    class Vector4
    {
    public:
        explicit Vector4() = default;

        ~Vector4() = default;

        MATH_LIB_FORCE_INLINE explicit Vector4(T x, T y, T z, T w)
            : m_x(x)
            , m_y(y)
            , m_z(z)
            , m_w(w)
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

        MATH_LIB_FORCE_INLINE void setX(double x) noexcept
        {
            m_x = x;
        }

        MATH_LIB_FORCE_INLINE void setY(double y) noexcept
        {
            m_y = y;
        }

        MATH_LIB_FORCE_INLINE void setZ(double z) noexcept
        {
            m_z = z;
        }

        MATH_LIB_FORCE_INLINE void setW(double w) noexcept
        {
            m_w = w;
        }

    private:
        T m_x;
        T m_y;
        T m_z;
        T m_w;
    };

} // MathLib

#endif // MATH_LIB_VECTOR4_H
