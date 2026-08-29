#ifndef MATH_LIB_MATRIX3X3D_H
#define MATH_LIB_MATRIX3X3D_H

#include <array>
#include <cstring>
#include <Vector3d.hpp>

namespace MathLib
{
    template<typename T>
    class Matrix3x3;

    // Matrix elements are stored in row-major order
    // Mathematical operations use a column-vector convention
    template<>
    class Matrix3x3<double>
    {
    public:
        using _VectorType = Vector3d;

        explicit Matrix3x3() = default;

        ~Matrix3x3() = default;
        // clang-format off
        MATH_LIB_FORCE_INLINE explicit Matrix3x3(double getM11, double getM12, double getM13,
                                                 double getM21, double getM22, double getM23,
                                                 double getM31, double getM32, double getM33)
            : m_data{Vector3d(getM11, getM12, getM13), 
                     Vector3d(getM21, getM22, getM23),
                     Vector3d(getM31, getM32, getM33)}
        {

        }
        // clang-format on

        MATH_LIB_FORCE_INLINE explicit Matrix3x3(const Vector3d& row1, const Vector3d& row2, const Vector3d& row3)
            : m_data{row1, row2, row3}
        {
        }

        [[nodiscard]] static Matrix3x3 zero() noexcept
        {
            // clang-format off
            return Matrix3x3(0.0, 0.0, 0.0,
                             0.0, 0.0, 0.0,
                             0.0, 0.0, 0.0);
            // clang-format on
        }
        [[nodiscard]] static Matrix3x3 identity() noexcept
        {
            // clang-format off
            return Matrix3x3(1.0, 0.0, 0.0,
                             0.0, 1.0, 0.0,
                             0.0, 0.0, 1.0);
            // clang-format on
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM11() const noexcept
        {
            return m_data[0].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM12() const noexcept
        {
            return m_data[0].getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM13() const noexcept
        {
            return m_data[0].getZ();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM21() const noexcept
        {
            return m_data[1].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM22() const noexcept
        {
            return m_data[1].getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM23() const noexcept
        {
            return m_data[1].getZ();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM31() const noexcept
        {
            return m_data[2].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM32() const noexcept
        {
            return m_data[2].getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM33() const noexcept
        {
            return m_data[2].getZ();
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM11(double getM11) noexcept
        {
            m_data[0].setX(getM11);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM12(double getM12) noexcept
        {
            m_data[0].setY(getM12);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM13(double getM13) noexcept
        {
            m_data[0].setZ(getM13);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM21(double getM21) noexcept
        {
            m_data[1].setX(getM21);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM22(double getM22) noexcept
        {
            m_data[1].setY(getM22);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM23(double getM23) noexcept
        {
            m_data[1].setZ(getM23);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM31(double getM31) noexcept
        {
            m_data[2].setX(getM31);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM32(double getM32) noexcept
        {
            m_data[2].setY(getM32);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM33(double getM33) noexcept
        {
            m_data[2].setZ(getM33);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& transpose() noexcept
        {
            double* ptr = reinterpret_cast<double*>(&m_data[0]);
            static constexpr std::size_t m12offset = 1;
            static constexpr std::size_t m13offset = 2;

            static constexpr std::size_t m21offset = 3;
            static constexpr std::size_t m23offset = 5;

            static constexpr std::size_t m31offset = 6;
            static constexpr std::size_t m32offset = 7;

            std::swap(ptr[m12offset], ptr[m21offset]);
            std::swap(ptr[m13offset], ptr[m31offset]);
            std::swap(ptr[m23offset], ptr[m32offset]);

            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3 getTranspose() const noexcept
        {
            Matrix3x3 m = (*this);
            return m.transpose();
        }

        MATH_LIB_FORCE_INLINE double determinant() const noexcept
        {
            return Vector3d::dot(m_data[0], Vector3d::cross(m_data[1], m_data[2]));
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& inverse() noexcept
        {
            // clang-format off
             const double row1x = m_data[0].getX(); const double row1y = m_data[0].getY(); const double row1z = m_data[0].getZ();
             const double row2x = m_data[1].getX(); const double row2y = m_data[1].getY(); const double row2z = m_data[1].getZ();
             const double row3x = m_data[2].getX(); const double row3y = m_data[2].getY(); const double row3z = m_data[2].getZ();
             double inv[9];

             inv[0] = (row2y * row3z) - (row2z * row3y); inv[1] = (row3y * row1z) - (row3z * row1y); inv[2] = (row1y * row2z) - (row1z * row2y);
             inv[3] = (row2z * row3x) - (row2x * row3z); inv[4] = (row3z * row1x) - (row3x * row1z); inv[5] = (row1z * row2x) - (row1x * row2z);
             inv[6] = (row2x * row3y) - (row2y * row3x); inv[7] = (row3x * row1y) - (row3y * row1x); inv[8] = (row1x * row2y) - (row1y * row2x);
            // clang-format on
            const double determinant = row1x * inv[0] + row1y * inv[3] + row1z * inv[6];

            if (fuzzyZero(determinant) || !std::isfinite(determinant))
            {
                return *this;
            }

            const double invDeterminant = 1.0 / determinant;
            for (auto& d : inv)
                d = d * invDeterminant;

            static_assert(sizeof(m_data) == sizeof(inv));
            std::memcpy(m_data.data(), inv, sizeof(m_data));

            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3 getInverse() const noexcept
        {
            Matrix3x3 m = *this;
            return m.inverse();
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& operator+=(const double value) noexcept
        {
            m_data[0] += value;
            m_data[1] += value;
            m_data[2] += value;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix3x3 operator+(double scalar) const
        {
            Matrix3x3 result = *this;
            result += scalar;
            return result;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& operator-=(const double value) noexcept
        {
            m_data[0] -= value;
            m_data[1] -= value;
            m_data[2] -= value;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix3x3 operator-(double scalar) const
        {
            Matrix3x3 result = *this;
            result -= scalar;
            return result;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& operator*=(const double value) noexcept
        {
            m_data[0] *= value;
            m_data[1] *= value;
            m_data[2] *= value;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix3x3 operator*(double scalar) const
        {
            Matrix3x3 result = *this;
            result *= scalar;
            return result;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& operator/=(const double value) noexcept
        {
            m_data[0] /= value;
            m_data[1] /= value;
            m_data[2] /= value;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix3x3 operator/(double scalar) const
        {
            Matrix3x3 result = *this;
            result /= scalar;
            return result;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& operator+=(const Matrix3x3& rhs) noexcept
        {
            m_data[0] += rhs.m_data[0];
            m_data[1] += rhs.m_data[1];
            m_data[2] += rhs.m_data[2];
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix3x3 operator+(const Matrix3x3& rhs) const
        {
            Matrix3x3 result = *this;
            result += rhs;
            return result;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& operator-=(const Matrix3x3& rhs) noexcept
        {
            m_data[0] -= rhs.m_data[0];
            m_data[1] -= rhs.m_data[1];
            m_data[2] -= rhs.m_data[2];
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix3x3 operator-(const Matrix3x3& rhs) const
        {
            Matrix3x3 result = *this;
            result -= rhs;
            return result;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector3d operator*(const Vector3d& rhs) const noexcept
        {
            return Vector3d(Vector3d::dot(m_data[0], rhs), Vector3d::dot(m_data[1], rhs),
                            Vector3d::dot(m_data[2], rhs));
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& operator*=(Matrix3x3 rhs) noexcept
        {
            // because the matrix is row layout and we want to only do an dot product
            // we transopse the other matrix to make the base row * coloms multiplication
            // an row * row multiplication
            rhs.transpose();

            const double m11 = Vector3d::dot(m_data[0], rhs.m_data[0]);
            const double m12 = Vector3d::dot(m_data[0], rhs.m_data[1]);
            const double m13 = Vector3d::dot(m_data[0], rhs.m_data[2]);

            const double m21 = Vector3d::dot(m_data[1], rhs.m_data[0]);
            const double m22 = Vector3d::dot(m_data[1], rhs.m_data[1]);
            const double m23 = Vector3d::dot(m_data[1], rhs.m_data[2]);

            const double m31 = Vector3d::dot(m_data[2], rhs.m_data[0]);
            const double m32 = Vector3d::dot(m_data[2], rhs.m_data[1]);
            const double m33 = Vector3d::dot(m_data[2], rhs.m_data[2]);

            *this = Matrix3x3(Vector3d(m11, m12, m13), Vector3d(m21, m22, m23), Vector3d(m31, m32, m33));

            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix3x3 operator*(const Matrix3x3& rhs) const noexcept
        {
            Matrix3x3 m = *this;
            m *= rhs;
            return m;
        }

        MATH_LIB_FORCE_INLINE bool operator==(const Matrix3x3& rhs) const noexcept
        {
            return m_data[0] == rhs.m_data[0] && m_data[1] == rhs.m_data[1] && m_data[2] == rhs.m_data[2];
        }

        MATH_LIB_FORCE_INLINE bool operator!=(const Matrix3x3& rhs) const noexcept
        {
            return !this->operator==(rhs);
        }

    private:
        std::array<Vector3d, 3> m_data;
    };

    using Matrix3x3d = Matrix3x3<double>;
} // namespace MathLib

#endif // MATH_LIB_MATRIX3X3D_H
