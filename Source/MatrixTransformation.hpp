#ifndef MATH_LIB_MATRIX_TRANSFORMATION_H
#define MATH_LIB_MATRIX_TRANSFORMATION_H

#include <Matrix2x2.hpp>
#include <Matrix3x3.hpp>
#include <Matrix4x4.hpp>
#include <Quaternion.hpp>

namespace MathLib
{
    template<typename T>
    concept MatrixSq = std::is_same_v<T, Matrix2x2<float>> || std::is_same_v<T, Matrix3x3<float>> ||
                       std::is_same_v<T, Matrix4x4<float>> || std::is_same_v<T, Matrix2x2<double>> ||
                       std::is_same_v<T, Matrix3x3<double>> || std::is_same_v<T, Matrix4x4<double>>;
    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix2x2<T> rotation(T cos, T sin)
    {
        return Matrix2x2<T>(cos, -sin, sin, cos);
    }

    template<typename T>
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix2x2<T> rotation(T angle)
    {
        const T c = std::cos(angle);
        const T s = std::sin(angle);

        return rotation<T>(c, s);
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

    template<MatrixSq M>
    [[nodiscard]] MATH_LIB_FORCE_INLINE M rotationX(typename M::_ValueType angle)
    {
        const typename M::_ValueType c = std::cos(angle);
        const typename M::_ValueType s = std::sin(angle);

        if constexpr (std::is_same_v<M, Matrix3x3<typename M::_ValueType>>)
        {
            // clang-format off
            return M(1, 0, 0, 
                     0, c, -s, 
                     0, s, c);
            // clang-format on
        }
        else if constexpr (std::is_same_v<M, Matrix4x4<typename M::_ValueType>>)
        {
            // clang-format off
            return  M(1, 0, 0, 0,
                      0, c, -s, 0,
                      0, s, c, 0, 
                      0, 0, 0, 1);
            // clang-format on
        }
        else
        {
            static_assert(false);
        }
    }

    template<MatrixSq M>
    [[nodiscard]] MATH_LIB_FORCE_INLINE M rotationY(typename M::_ValueType angle)
    {
        const typename M::_ValueType c = std::cos(angle);
        const typename M::_ValueType s = std::sin(angle);

        if constexpr (std::is_same_v<M, Matrix3x3<typename M::_ValueType>>)
        {
            // clang-format off
            return M(c, 0, s,
                     0, 1, 0,
                    -s, 0, c);
            // clang-format on
        }
        else if constexpr (std::is_same_v<M, Matrix4x4<typename M::_ValueType>>)
        {
            // clang-format off
            return M(c, 0, s, 0,
                     0, 1, 0, 0,
                    -s, 0, c, 0,
                     0, 0, 0, 1);
            // clang-format on
        }
        else
        {
            static_assert(false);
        }
    }

    template<MatrixSq M>
    [[nodiscard]] MATH_LIB_FORCE_INLINE M rotationZ(typename M::_ValueType angle)
    {
        const typename M::_ValueType c = std::cos(angle);
        const typename M::_ValueType s = std::sin(angle);

        if constexpr (std::is_same_v<M, Matrix3x3<typename M::_ValueType>>)
        {
            // clang-format off
            return M(c, -s, 0,
                     s,  c, 0,
                     0,  0, 1);
            // clang-format on
        }
        else if constexpr (std::is_same_v<M, Matrix4x4<typename M::_ValueType>>)
        {
            // clang-format off
            return M(c, -s, 0, 0,
                     s,  c, 0, 0,
                     0,  0, 1, 0,
                     0,  0, 0, 1);
            // clang-format on
        }
        else
        {
            static_assert(false);
        }
    }

    template<MatrixSq M>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static M rotationXYZ(typename M::_ValueType cX, typename M::_ValueType sX,
                                                             typename M::_ValueType cY, typename M::_ValueType sY,
                                                             typename M::_ValueType cZ, typename M::_ValueType sZ)
    {
        // Rz * Ry * Rx
        if constexpr (std::is_same_v<M, Matrix3x3<typename M::_ValueType>>)
        {
            // clang-format off
            return M(
                cZ * cY, cZ * sY * sX - sZ * cX, cZ * sY * cX + sZ * sX, 
                sZ * cY, sZ * sY * sX + cZ * cX, sZ * sY * cX - cZ * sX,
                -sY, cY * sX, cY * cX
            );
            // clang-format on
        }
        else if constexpr (std::is_same_v<M, Matrix4x4<typename M::_ValueType>>)
        {
            // clang-format off
            return M(
                cZ * cY, cZ * sY * sX - sZ * cX, cZ * sY * cX + sZ * sX, 0,
                sZ * cY, sZ * sY * sX + cZ * cX, sZ * sY * cX - cZ * sX, 0,
                -sY    , cY * sX               , cY * cX               , 0,
                0      ,0                      ,0                      , 1
            );
            // clang-format on
        }
        else
        {
            static_assert(false);
        }
    }

    template<MatrixSq M>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static M
    rotationXYZ(typename M::_ValueType angleX, typename M::_ValueType angleY, typename M::_ValueType angleZ)
    {
        using T = typename M::_ValueType;

        const T cX = std::cos(angleX);
        const T sX = std::sin(angleX);

        const T cY = std::cos(angleY);
        const T sY = std::sin(angleY);

        const T cZ = std::cos(angleZ);
        const T sZ = std::sin(angleZ);

        // clang-format off
        return rotationXYZ<M>(cX, sX, cY, sY, cZ, sZ);
        // clang-format on
    }

    template<MatrixSq M>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static M rotationXYZ(const Vector3<typename M::_ValueType>& angles)
    {
        // clang-format off
        return rotationXYZ<M>(angles.getX(), angles.getY(), angles.getZ());
        // clang-format on
    }

    template<MatrixSq M>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static M scale(typename M::_ValueType scaleX, typename M::_ValueType scaleY,
                                                       typename M::_ValueType scaleZ)
    {
        if constexpr (std::is_same_v<M, Matrix3x3<typename M::_ValueType>>)
        {
            // clang-format off
            return M(
                scaleX, 0, 0,
                0, scaleY, 0, 
                0, 0, scaleZ);
            // clang-format on
        }
        else if constexpr (std::is_same_v<M, Matrix4x4<typename M::_ValueType>>)
        {
            // clang-format off
            return M(
                scaleX, 0     , 0        , 0,
                0     , scaleY, 0        , 0,
                0     , 0     , scaleZ   , 0,
                0     , 0     , 0        , 1
            );
            // clang-format on
        }
        else
        {
            static_assert(false);
        }
    }

    template<MatrixSq M>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static M scale(const Vector3<typename M::_ValueType>& scaleVector)
    {
        return scale<M>(scaleVector.getX(), scaleVector.getY(), scaleVector.getZ());
    }

    template<MatrixSq M>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static M translation(typename M::_ValueType tX, typename M::_ValueType tY)
    {
        using T = typename M::_ValueType;

        if constexpr (std::is_same_v<M, Matrix3x3<typename M::_ValueType>>)
        {
            // clang-format off
            return M(
                T(1), T(0), tX,
                T(0), T(1), tY, 
                T(0), T(0), T(1));
            // clang-format on
        }
        else if constexpr (std::is_same_v<M, Matrix4x4<typename M::_ValueType>>)
        {
            // clang-format off
            return M(
                T(1) , T(0) , T(0) , tX,
                T(0) , T(1) , T(0) , tY,
                T(0) , T(0) , T(1) , T(0),
                T(0) , T(0) , T(0) , T(1)
            );
            // clang-format on
        }
        else
        {
            static_assert(false);
        }
    }

    template<MatrixSq M>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static M translation(const Vector2<typename M::_ValueType>& tXY)
    {
        return translation<M>(tXY.getX(), tXY.getY());
    }

    template<MatrixSq M>
    requires(std::is_same_v<M, Matrix4x4<typename M::_ValueType>>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static M translation(typename M::_ValueType tX, typename M::_ValueType tY,
                                                             typename M::_ValueType tZ)
    {
        using T = typename M::_ValueType;
        // clang-format off
            return M(
                T(1) , T(0) , T(0) , tX,
                T(0) , T(1) , T(0) , tY,
                T(0) , T(0) , T(1) , tZ,
                T(0) , T(0) , T(0) , T(1)
            );
        // clang-format on
    }

    template<MatrixSq M>
    requires(std::is_same_v<M, Matrix4x4<typename M::_ValueType>>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static M translation(const Vector3<typename M::_ValueType>& tXYZ)
    {
        return translation<M>(tXYZ.getX(), tXYZ.getY(), tXYZ.getZ());
    }

    template<typename T>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T> trsXYZ(T tX, T tY, T tZ, T cX, T sX, T cY, T sY, T cZ, T sZ,
                                                                   T scaleX, T scaleY, T scaleZ)
    {
        // Rz * Ry * Rx
        // M = T * R * S

        // clang-format off
            return Matrix4x4<T>(
                 cZ * cY                 * scaleX,
                (cZ * sY * sX - sZ * cX) * scaleY,
                (cZ * sY * cX + sZ * sX) * scaleZ,
                 tX,

                 sZ * cY                 * scaleX,
                (sZ * sY * sX + cZ * cX) * scaleY,
                (sZ * sY * cX - cZ * sX) * scaleZ,
                 tY,

                -sY                      * scaleX,
                 cY * sX                 * scaleY,
                 cY * cX                 * scaleZ,
                 tZ,

                 0, 0, 0, 1
            );
        // clang-format on
    }

    template<typename T>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T> trs(T tX, T tY, T tZ, T cX, T sX, T cY, T sY, T cZ, T sZ,
                                                                T scaleX, T scaleY, T scaleZ,
                                                                RotationOrder rotationOrder = RotationOrder::XYZ)
    {
        switch (rotationOrder)
        {
        case MathLib::RotationOrder::XYZ:
            return trsXYZ<T>(tX, tY, tZ, cX, sX, cY, sY, cZ, sZ, scaleX, scaleY, scaleZ);
        case MathLib::RotationOrder::XZY:
            break;
        case MathLib::RotationOrder::YXZ:
            break;
        case MathLib::RotationOrder::YZX:
            break;
        case MathLib::RotationOrder::ZXY:
            break;
        case MathLib::RotationOrder::ZYX:
            break;
        default:
            break;
        }

        return Matrix4x4<T>::identity();
    }

    template<typename T>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T> trs(T tX, T tY, T tZ, const Quaternion<T>& quaternion,
                                                                T scaleX, T scaleY, T scaleZ)
    {
        Matrix4x4<T> rotationMatrix = Quaternion<T>::toMatrix4x4(quaternion);

        rotationMatrix[0][3] = tX;
        rotationMatrix[1][3] = tY;
        rotationMatrix[2][3] = tZ;

        rotationMatrix[0] *= Vector4(scaleX, scaleY, scaleZ, T(1.0));
        rotationMatrix[1] *= Vector4(scaleX, scaleY, scaleZ, T(1.0));
        rotationMatrix[2] *= Vector4(scaleX, scaleY, scaleZ, T(1.0));

        return rotationMatrix;
    }

    template<typename T>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T>
    trs(const Vector3<T>& translation, const Quaternion<T>& quaternion, const Vector3<T>& scale)
    {
        return trs<T>(translation.getX(), translation.getY(), translation.getZ(), quaternion, scale.getX(),
                      scale.getY(), scale.getZ());
    }

    template<typename T>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T> trs(T tX, T tY, T tZ, T angleX, T angleY, T angleZ,
                                                                T scaleX, T scaleY, T scaleZ,
                                                                RotationOrder rotationOrder = RotationOrder::XYZ)
    {
        const T cX = std::cos(angleX);
        const T sX = std::sin(angleX);

        const T cY = std::cos(angleY);
        const T sY = std::sin(angleY);

        const T cZ = std::cos(angleZ);
        const T sZ = std::sin(angleZ);
        return trs<T>(tX, tY, tZ, cX, sX, cY, sY, cZ, sZ, scaleX, scaleY, scaleZ, rotationOrder);
    }

    template<typename T>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix4x4<T> trs(const Vector3<T>& translation,
                                                                const Vector3<T>& eulerAngles, const Vector3<T>& scale,
                                                                RotationOrder rotationOrder = RotationOrder::XYZ)
    {
        return trs<T>(translation.getX(), translation.getY(), translation.getZ(), eulerAngles.getX(),
                      eulerAngles.getY(), eulerAngles.getZ(), scale.getX(), scale.getY(), scale.getZ(), rotationOrder);
    }

    template<MatrixSq M>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector3<typename M::_ValueType> extractEulerXYZ(const M& m) noexcept
    {
        using T = typename M::_ValueType;
        static_assert(!std::is_same_v<M, Matrix2x2<T>>);

        // rotationXYZ = Rz * Ry * Rx
        //
        // m31 = -sin(y)
        // m32 = cos(y) * sin(x)
        // m33 = cos(y) * cos(x)
        //
        // m21 = sin(z) * cos(y)
        // m11 = cos(z) * cos(y)

        const T sinY = std::clamp(-m.getM31(), T(-1), T(1));
        const T y = std::asin(sinY);

        const T cosY = std::cos(y);

        T x;
        T z;

        if (std::abs(cosY) > std::numeric_limits<T>::epsilon())
        {
            x = std::atan2(m.getM32(), m.getM33());
            z = std::atan2(m.getM21(), m.getM11());
        }
        else
        {
            // Gimbal lock: y = +/- pi/2.
            // x and z are no longer independently recoverable.
            // Choose z = 0 and recover x.
            x = std::atan2(-m.getM23(), m.getM22());
            z = T(0);
        }

        return Vector3<T>(x, y, z);
    }

    template<MatrixSq M>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static Vector3<typename M::_ValueType>
    extractEulerXYZ(const M& m, RotationOrder rotationMatrixOrder) noexcept
    {
        switch (rotationMatrixOrder)
        {
        case MathLib::RotationOrder::XYZ:
            return extractEulerXYZ(m);
        case MathLib::RotationOrder::XZY:
            break;
        case MathLib::RotationOrder::YXZ:
            break;
        case MathLib::RotationOrder::YZX:
            break;
        case MathLib::RotationOrder::ZXY:
            break;
        case MathLib::RotationOrder::ZYX:
            break;
        default:
            break;
        }

        return M::identity();
    }

} // namespace MathLib

#endif // MATH_LIB_MATRIX_TRANSFORMATION_H
