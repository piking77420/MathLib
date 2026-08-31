#ifndef MATH_LIB_MATRIX_TRANSFORMATION_H
#define MATH_LIB_MATRIX_TRANSFORMATION_H

#include <Matrix2x2.hpp>
#include <Matrix3x3.hpp>
#include <Matrix4x4.hpp>

namespace MathLib
{
    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix2x2<T> rotation(T angle)
    {
        const T c = std::cos(angle);
        const T s = std::sin(angle);

        return Matrix2x2<T>(c, -s, s, c);
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix2x2<T> scale(T scaleX, T scaleY)
    {
        return Matrix2x2<T>(scaleX, 0.0, 0.0, scaleY);
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix2x2<T> scale(const Vector2<T>& scale)
    {
        return Matrix2x2<T>(scale.getX(), 0.0, 0.0, scale.getY());
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix3x3<T> rotationX(T angle)
    {
        const T c = std::cos(angle);
        const T s = std::sin(angle);
        // clang-format off
        return Matrix3x3<T>(1, 0, 0, 0, c, -s, 0, s, c);
        // clang-format on
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix3x3<T> rotationY(T angle)
    {
        const T c = std::cos(angle);
        const T s = std::sin(angle);

        // clang-format off
            return Matrix3x3<T>(
                c, 0, s, 
                0, 1, 0, 
                -s, 0, c);
        // clang-format on
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix3x3<T> rotationZ(T angle)
    {
        const T c = std::cos(angle);
        const T s = std::sin(angle);

        // clang-format off
            return Matrix3x3<T>(
                c, -s, 0, 
                s, c, 0, 
                0, 0, 1);
        // clang-format on
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix3x3<T> rotationXYZ(T angleX, T angleY, T angleZ)
    {
        const T cX = std::cos(angleX);
        const T sX = std::sin(angleX);

        const T cY = std::cos(angleY);
        const T sY = std::sin(angleY);

        const T cZ = std::cos(angleZ);
        const T sZ = std::sin(angleZ);

        // Rz * Ry * Rx

        // clang-format off
        return rotationXYZ(cX, sX, cY, sY, cZ, sZ);
        // clang-format on
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix3x3<T> rotationXYZ(T cX, T sX, T cY, T sY, T cZ, T sZ)
    {
        // Rz * Ry * Rx
        // clang-format off
        return Matrix3x3<T>(
            cZ * cY,  cZ * sY * sX - sZ * cX,  cZ * sY * cX + sZ * sX,
            sZ * cY,  sZ * sY * sX + cZ * cX,  sZ * sY * cX - cZ * sX,
                -sY,  cY * sX               ,  cY * cX
        );
        // clang-format on
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix3x3<T> scale(T scaleX, T scaleY, T scaleZ)
    {
        // clang-format off
            return Matrix3x3<T>(
                scaleX, 0, 0,
                0, scaleY, 0, 
                0, 0, scaleZ);
        // clang-format on
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix3x3<T> translation(T tX, T tY)
    {
        // clang-format off
            return Matrix3x3<T>(
                0, 0, tX,
                0, 0, tY, 
                0, 0, 1);
        // clang-format on
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix3x3<T> translation(const Vector2<T>& tXY)
    {
        return translation(tXY.getX(), tXY.getY());
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T> rotationX(T angle)
    {
        const T c = std::cos(angle);
        const T s = std::sin(angle);

        // clang-format off
        return Matrix4x4<T>(
            1, 0,  0, 0,
            0, c, -s, 0,
            0, s,  c, 0,
            0, 0,  0, 1
        );
        // clang-format on
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T> rotationY(T angle)
    {
        const T c = std::cos(angle);
        const T s = std::sin(angle);

        // clang-format off
        return Matrix4x4<T>(
             c, 0, s, 0,
             0, 1, 0, 0,
            -s, 0, c, 0,
             0, 0, 0, 1
        );
        // clang-format on
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T> rotationZ(T angle)
    {
        const T c = std::cos(angle);
        const T s = std::sin(angle);

        // clang-format off
        return Matrix4x4<T>(
            c, -s, 0, 0,
            s,  c, 0, 0,
            0,  0, 1, 0,
            0,  0, 0, 1
        );
        // clang-format on
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T> rotationXYZ(T angleX, T angleY, T angleZ)
    {
        const T cX = std::cos(angleX);
        const T sX = std::sin(angleX);

        const T cY = std::cos(angleY);
        const T sY = std::sin(angleY);

        const T cZ = std::cos(angleZ);
        const T sZ = std::sin(angleZ);

        return rotationXYZ(cX, sX, cY, sY, cZ, sZ);
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T> rotationXYZ(T cX, T sX, T cY, T sY, T cZ, T sZ)
    {
        // Rz * Ry * Rx
        // clang-format off
        return Matrix4x4<T>(
            cZ * cY, cZ * sY * sX - sZ * cX, cZ * sY * cX + sZ * sX, 0,
            sZ * cY, sZ * sY * sX + cZ * cX, sZ * sY * cX - cZ * sX, 0,
            -sY    , cY * sX               , cY * cX               , 0,
            0      ,0                      ,0                      , 1
        );
        // clang-format on
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T> scale(T scaleX, T scaleY, T scaleZ)
    {
        // clang-format off
        return Matrix4x4<T>(
            scaleX,      0,      0, 0,
                 0, scaleY,      0, 0,
                 0,      0, scaleZ, 0,
                 0,      0,      0, 1
        );
        // clang-format on
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T> scale(const Vector3<T>& scale)
    {
        // clang-format off
        return Matrix4x4<T>(
            scale.getX(),      0      ,      0      , 0,
                 0      , scale.getY(),      0      , 0,
                 0      ,      0      , scale.getZ(), 0,
                 0      ,      0      ,      0      , 1
        );
        // clang-format on
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T> translation(T tX, T tY, T tZ)
    {
        // clang-format off
        return Matrix4x4<T>(
                 0,      0,      0,     tX,
                 0,      0,      0,     tY,
                 0,      0,      0,     tZ,
                 0,      0,      0,     1
        );
        // clang-format on
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T> translation(const Vector3<T>& translation)
    {
        // clang-format off
        return Matrix4x4<T>(
                 0,      0,      0,     translation.getX(),
                 0,      0,      0,     translation.getY(),
                 0,      0,      0,     translation.getZ(),
                 0,      0,      0,     1
        );
        // clang-format on
    }

    enum class RotationMatrixOrder
    {
        // Tait-Bryan
        XYZ,
        XZY,
        YXZ,
        YZX,
        ZXY,
        ZYX,
    };

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T> trsXYZ(T tX, T tY, T tZ, T cX, T sX, T cY, T sY, T cZ, T sZ,
                                                                   T scaleX, T scaleY, T scaleZ)
    {
        // Rz * Ry * Rx
        // clang-format off
        return Matrix4x4<T>(
            (cZ * cY) * scaleX, cZ * sY * sX - sZ * cX, cZ * sY * cX + sZ * sX, tX,
            sZ * cY, (sZ * sY * sX + cZ * cX) * scaleY, sZ * sY * cX - cZ * sX, tY,
            -sY    , cY * sX               , (cY * cX) * scaleZ               , tZ,
            0      ,0                      ,0                                 , 1
        );
        // clang-format on;
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T>
    trs(T tX, T tY, T tZ, T cX, T sX, T cY, T sY, T cZ, T sZ, T scaleX, T scaleY, T scaleZ,
        RotationMatrixOrder rotationOrder = RotationMatrixOrder::XYZ)
    {
        switch (rotationOrder)
        {
        case MathLib::RotationMatrixOrder::XYZ:
            return trsXYZ(tX, tY, tZ, cX, sX, cY, sY, cZ, sZ, scaleX, scaleY, scaleZ);
        case MathLib::RotationMatrixOrder::XZY:
            break;
        case MathLib::RotationMatrixOrder::YXZ:
            break;
        case MathLib::RotationMatrixOrder::YZX:
            break;
        case MathLib::RotationMatrixOrder::ZXY:
            break;
        case MathLib::RotationMatrixOrder::ZYX:
            break;
        default:
            break;
        }

        return Matrix4x4<T>::identity();
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T>
    trs(T tX, T tY, T tZ, T angleX, T angleY, T angleZ, T scaleX, T scaleY, T scaleZ,
        RotationMatrixOrder rotationOrder = RotationMatrixOrder::XYZ)
    {
        const T cX = std::cos(angleX);
        const T sX = std::sin(angleX);

        const T cY = std::cos(angleY);
        const T sY = std::sin(angleY);

        const T cZ = std::cos(angleZ);
        const T sZ = std::sin(angleZ);
        return trs(tX, tY, tZ, cX, sX, cY, sY, cZ, sZ, scaleX, scaleY, scaleZ, rotationOrder);
    }

} // namespace MathLib

#endif // MATH_LIB_MATRIX_TRANSFORMATION_H
