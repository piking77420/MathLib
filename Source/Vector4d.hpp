#ifndef MATH_LIB_VECTOR4D_H
#define MATH_LIB_VECTOR4D_H

#include <Vector4.hpp>

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

        Vector4(double _x, double _y, double _z, double _w);

        [[nodiscard]] double getX() const noexcept;

        [[nodiscard]] double getY() const noexcept;

        [[nodiscard]] double getZ() const noexcept;

        [[nodiscard]] double getW() const noexcept;

        void setX(double _x) noexcept;

        void setY(double _y) noexcept;

        void setZ(double _z) noexcept;

        void setW(double _w) noexcept;

    private:
        double m_x;
        double m_y;
        double m_z;
        double m_w;
    };

    using Vector4d = Vector4<double>;

} // MathLib

#endif // MATH_LIB_VECTOR4D_H