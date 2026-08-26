#include <MathLibHeader.hpp>
#include <Matrix4x4d.hpp>
#include <Matrix3x3d.hpp>
#include <Vector3d.hpp>
#include <Vector4d.hpp>

namespace MathLib
{
    Matrix4x4<double>& Matrix4x4<double>::inverse() noexcept
    {
        const Vector4d cofactor0 = Vector4d::cross(m_data[1], m_data[2], m_data[3]);
        const double determinant = Vector4d::dot(m_data[0], cofactor0);
        if (fuzzyZero(determinant))
            return *this;

        const double invDeterminant = (1.0 / determinant);
        const Vector4d cofactor1 = Vector4d::cross(m_data[2], m_data[0], m_data[3]);
        const Vector4d cofactor2 = Vector4d::cross(m_data[3], m_data[0], m_data[1]);
        const Vector4d cofactor3 = Vector4d::cross(m_data[0], m_data[2], m_data[1]);

        *this = Matrix4x4d(cofactor0, cofactor1, cofactor2, cofactor3).transpose() * invDeterminant;

        // clang-format on
        return *this;
    }

} // namespace MathLib
