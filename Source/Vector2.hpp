#ifndef MATH_LIB_VECTOR2_H
#define MATH_LIB_VECTOR2_H

#include <MathLibHeader.hpp>

namespace MathLib
{
    template<typename T>
    class Vector2
    {
    public:
        explicit Vector2() = default;

        ~Vector2() = default;

        MATH_LIB_FORCE_INLINE explicit Vector2(T x, T y)
            : m_x(x)
            , m_y(y)
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

        MATH_LIB_FORCE_INLINE void setX(double x) noexcept
        {
            m_x = x;
        }

        MATH_LIB_FORCE_INLINE void setY(double y) noexcept
        {
            m_y = y;
        }

    private:
        T m_x;
        T m_y;
    };

} // MathLib

#endif // MATH_LIB_VECTOR2_H
