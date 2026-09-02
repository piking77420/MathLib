#ifndef MATH_LIB_MATRIX_TRANSFORMATION_H
#define MATH_LIB_MATRIX_TRANSFORMATION_H

#include <Matrix2x2.hpp>
#include <Matrix3x3.hpp>
#include <Matrix4x4.hpp>

namespace MathLib
{
    template<typename T>
    concept MatrixSq = std::is_same_v<T, Matrix2x2<float>> || std::is_same_v<T, Matrix3x3<float>> ||
                       std::is_same_v<T, Matrix4x4<float>> || std::is_same_v<T, Matrix2x2<double>> ||
                       std::is_same_v<T, Matrix3x3<double>> || std::is_same_v<T, Matrix4x4<double>>;

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
        const typename M::_ValueType cX = std::cos(angleX);
        const typename M::_ValueType sX = std::sin(angleX);

        const typename M::_ValueType cY = std::cos(angleY);
        const typename M::_ValueType sY = std::sin(angleY);

        const typename M::_ValueType cZ = std::cos(angleZ);
        const typename M::_ValueType sZ = std::sin(angleZ);

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
        if constexpr (std::is_same_v<M, Matrix3x3<typename M::_ValueType>>)
        {
            // clang-format off
            return M(
                1, 0, tX,
                0, 1, tY, 
                0, 0, 1);
            // clang-format on
        }
        else if constexpr (std::is_same_v<M, Matrix4x4<typename M::_ValueType>>)
        {
            // clang-format off
            return M(
                1 , 0 , 0 , tX,
                0 , 1 , 0 , tY,
                0 , 0 , 1 , 0,
                0 , 0 , 0 , 1
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
        // clang-format off
            return M(
                1 , 0 , 0 , tX,
                0 , 1 , 0 , tY,
                0 , 0 , 1 , tZ,
                0 , 0 , 0 , 1
            );
        // clang-format on
    }

    template<MatrixSq M>
    requires(std::is_same_v<M, Matrix4x4<typename M::_ValueType>>)
    [[nodiscard]] MATH_LIB_FORCE_INLINE static M translation(const Vector3<typename M::_ValueType>& tXYZ)
    {
        return translation<M>(tXYZ.getX(), tXYZ.getY(), tXYZ.getZ());
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

    template<MatrixSq M>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static M
    trsXYZ(typename M::_ValueType tX, typename M::_ValueType tY, typename M::_ValueType tZ, typename M::_ValueType cX,
           typename M::_ValueType sX, typename M::_ValueType cY, typename M::_ValueType sY, typename M::_ValueType cZ,
           typename M::_ValueType sZ, typename M::_ValueType scaleX, typename M::_ValueType scaleY,
           typename M::_ValueType scaleZ)
    {
        if constexpr (std::is_same_v<M, Matrix4x4<typename M::_ValueType>>)
        {
            // Rz * Ry * Rx
            // M = T * R * S

            // clang-format off
            return M(
                 cZ * cY               * scaleX,
                (cZ * sY * sX - sZ * cX) * scaleY,
                (cZ * sY * cX + sZ * sX) * scaleZ,
                 tX,

                 sZ * cY               * scaleX,
                (sZ * sY * sX + cZ * cX) * scaleY,
                (sZ * sY * cX - cZ * sX) * scaleZ,
                 tY,

                -sY                    * scaleX,
                 cY * sX               * scaleY,
                 cY * cX               * scaleZ,
                 tZ,

                 0, 0, 0, 1
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
    trs(typename M::_ValueType tX, typename M::_ValueType tY, typename M::_ValueType tZ, typename M::_ValueType cX,
        typename M::_ValueType sX, typename M::_ValueType cY, typename M::_ValueType sY, typename M::_ValueType cZ,
        typename M::_ValueType sZ, typename M::_ValueType scaleX, typename M::_ValueType scaleY,
        typename M::_ValueType scaleZ, RotationMatrixOrder rotationOrder = RotationMatrixOrder::XYZ)
    {
        switch (rotationOrder)
        {
        case MathLib::RotationMatrixOrder::XYZ:
            return trsXYZ<M>(tX, tY, tZ, cX, sX, cY, sY, cZ, sZ, scaleX, scaleY, scaleZ);
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

        return M::identity();
    }

    template<MatrixSq M>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static M
    trs(typename M::_ValueType tX, typename M::_ValueType tY, typename M::_ValueType tZ, typename M::_ValueType angleX,
        typename M::_ValueType angleY, typename M::_ValueType angleZ, typename M::_ValueType scaleX,
        typename M::_ValueType scaleY, typename M::_ValueType scaleZ,
        RotationMatrixOrder rotationOrder = RotationMatrixOrder::XYZ)
    {
        const typename M::_ValueType cX = std::cos(angleX);
        const typename M::_ValueType sX = std::sin(angleX);

        const typename M::_ValueType cY = std::cos(angleY);
        const typename M::_ValueType sY = std::sin(angleY);

        const typename M::_ValueType cZ = std::cos(angleZ);
        const typename M::_ValueType sZ = std::sin(angleZ);
        return trs<M>(tX, tY, tZ, cX, sX, cY, sY, cZ, sZ, scaleX, scaleY, scaleZ, rotationOrder);
    }

    template<MatrixSq M>
    [[nodiscard]] MATH_LIB_FORCE_INLINE static M
    trs(const Vector3<typename M::_ValueType>& translation, const Vector3<typename M::_ValueType>& eulerAngles,
        const Vector3<typename M::_ValueType>& scale, RotationMatrixOrder rotationOrder = RotationMatrixOrder::XYZ)
    {
        return trs<M>(translation.getX(), translation.getY(), translation.getZ(), eulerAngles.getX(),
                      eulerAngles.getY(), eulerAngles.getZ(), scale.getX(), scale.getY(), scale.getZ(), rotationOrder);
    }

} // namespace MathLib

#endif // MATH_LIB_MATRIX_TRANSFORMATION_H
