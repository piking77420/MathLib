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

        MATH_LIB_FORCE_INLINE explicit Vector4(T _x, T _y, T _z, T _w)
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

    private:
        T m_x;
        T m_y;
        T m_z;
        T m_w;
    };

} // MathLib

#endif // MATH_LIB_VECTOR4_H
