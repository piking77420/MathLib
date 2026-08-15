#ifndef MATH_LIB_VECTOR3_H
#define MATH_LIB_VECTOR3_H

#include <MathLibHeader.hpp>

namespace MathLib
{
    template<typename T>
    class Vector3
    {
    public:
        explicit Vector3() = default;

        ~Vector3() = default;

        MATH_LIB_FORCE_INLINE explicit Vector3(T _x, T _y, T _z)
            : m_x(_x)
            , m_y(_y)
            , m_z(_z)
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

    private:
        T m_x;
        T m_y;
        T m_z;
    };

} // MathLib

#endif // MATH_LIB_VECTOR3_H
