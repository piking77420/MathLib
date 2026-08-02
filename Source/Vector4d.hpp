#ifndef MATH_LIB_VECTOR4D_H
#define MATH_LIB_VECTOR4D_H

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

    private:
        double m_x;
        double m_y;
        double m_z;
        double m_w;
    };

    using Vector4d = Vector4<double>;

} // MathLib

#endif // MATH_LIB_VECTOR4D_H