#ifndef MATH_LIB_MATRIX3X3_H
#define MATH_LIB_MATRIX3X3_H

#include <array>
#include <cstring>
#include <Vector3.hpp>

namespace MathLib
{
    // Matrix elements are stored in row-major order
    // Mathematical operations use a column-vector convention
    template<typename T>
    requires(std::is_floating_point_v<T>)
    class Matrix3x3
    {
    public:
        using _VectorType = Vector3<T>;
        using _ValueType = typename _VectorType::_ValueType;

        explicit Matrix3x3() = default;

        ~Matrix3x3() = default;
        // clang-format off
        MATH_LIB_FORCE_INLINE explicit Matrix3x3(T getM11, T getM12, T getM13,
                                                 T getM21, T getM22, T getM23,
                                                 T getM31, T getM32, T getM33)
            : m_data{Vector3<T>(getM11, getM12, getM13), 
                     Vector3<T>(getM21, getM22, getM23),
                     Vector3<T>(getM31, getM32, getM33)}
        {

        }
        // clang-format on

        MATH_LIB_FORCE_INLINE explicit Matrix3x3(const Vector3<T>& row1, const Vector3<T>& row2, const Vector3<T>& row3)
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

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM11() const noexcept
        {
            return m_data[0].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM12() const noexcept
        {
            return m_data[0].getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM13() const noexcept
        {
            return m_data[0].getZ();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM21() const noexcept
        {
            return m_data[1].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM22() const noexcept
        {
            return m_data[1].getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM23() const noexcept
        {
            return m_data[1].getZ();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM31() const noexcept
        {
            return m_data[2].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM32() const noexcept
        {
            return m_data[2].getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM33() const noexcept
        {
            return m_data[2].getZ();
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM11(T getM11) noexcept
        {
            m_data[0].setX(getM11);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM12(T getM12) noexcept
        {
            m_data[0].setY(getM12);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM13(T getM13) noexcept
        {
            m_data[0].setZ(getM13);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM21(T getM21) noexcept
        {
            m_data[1].setX(getM21);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM22(T getM22) noexcept
        {
            m_data[1].setY(getM22);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM23(T getM23) noexcept
        {
            m_data[1].setZ(getM23);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM31(T getM31) noexcept
        {
            m_data[2].setX(getM31);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM32(T getM32) noexcept
        {
            m_data[2].setY(getM32);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& setM33(T getM33) noexcept
        {
            m_data[2].setZ(getM33);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& transpose() noexcept
        {
            T* ptr = reinterpret_cast<T*>(&m_data[0]);
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

        MATH_LIB_FORCE_INLINE T determinant() const noexcept
        {
            return Vector3<T>::dot(m_data[0], Vector3<T>::cross(m_data[1], m_data[2]));
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& inverse() noexcept
        {
            // clang-format off
             const T row1x = m_data[0].getX(); const T row1y = m_data[0].getY(); const T row1z = m_data[0].getZ();
             const T row2x = m_data[1].getX(); const T row2y = m_data[1].getY(); const T row2z = m_data[1].getZ();
             const T row3x = m_data[2].getX(); const T row3y = m_data[2].getY(); const T row3z = m_data[2].getZ();
             T inv[9];

             inv[0] = (row2y * row3z) - (row2z * row3y); inv[1] = (row3y * row1z) - (row3z * row1y); inv[2] = (row1y * row2z) - (row1z * row2y);
             inv[3] = (row2z * row3x) - (row2x * row3z); inv[4] = (row3z * row1x) - (row3x * row1z); inv[5] = (row1z * row2x) - (row1x * row2z);
             inv[6] = (row2x * row3y) - (row2y * row3x); inv[7] = (row3x * row1y) - (row3y * row1x); inv[8] = (row1x * row2y) - (row1y * row2x);
            // clang-format on
            const T determinant = row1x * inv[0] + row1y * inv[3] + row1z * inv[6];

            if (fuzzyZero(determinant) || !std::isfinite(determinant))
            {
                return *this;
            }

            const T invDeterminant = 1.0 / determinant;
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

        MATH_LIB_FORCE_INLINE Matrix3x3& operator+=(const T value) noexcept
        {
            m_data[0] += value;
            m_data[1] += value;
            m_data[2] += value;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix3x3 operator+(T scalar) const
        {
            Matrix3x3 result = *this;
            result += scalar;
            return result;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& operator-=(const T value) noexcept
        {
            m_data[0] -= value;
            m_data[1] -= value;
            m_data[2] -= value;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix3x3 operator-(T scalar) const
        {
            Matrix3x3 result = *this;
            result -= scalar;
            return result;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& operator*=(const T value) noexcept
        {
            m_data[0] *= value;
            m_data[1] *= value;
            m_data[2] *= value;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix3x3 operator*(T scalar) const
        {
            Matrix3x3 result = *this;
            result *= scalar;
            return result;
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& operator/=(const T value) noexcept
        {
            m_data[0] /= value;
            m_data[1] /= value;
            m_data[2] /= value;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix3x3 operator/(T scalar) const
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

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector3<T> operator*(const Vector3<T>& rhs) const noexcept
        {
            return Vector3<T>(Vector3<T>::dot(m_data[0], rhs), Vector3<T>::dot(m_data[1], rhs),
                              Vector3<T>::dot(m_data[2], rhs));
        }

        MATH_LIB_FORCE_INLINE Matrix3x3& operator*=(Matrix3x3 rhs) noexcept
        {
            // because the matrix is row layout and we want to only do an dot product
            // we transopse the other matrix to make the base row * coloms multiplication
            // an row * row multiplication
            rhs.transpose();

            const T m11 = Vector3<T>::dot(m_data[0], rhs.m_data[0]);
            const T m12 = Vector3<T>::dot(m_data[0], rhs.m_data[1]);
            const T m13 = Vector3<T>::dot(m_data[0], rhs.m_data[2]);

            const T m21 = Vector3<T>::dot(m_data[1], rhs.m_data[0]);
            const T m22 = Vector3<T>::dot(m_data[1], rhs.m_data[1]);
            const T m23 = Vector3<T>::dot(m_data[1], rhs.m_data[2]);

            const T m31 = Vector3<T>::dot(m_data[2], rhs.m_data[0]);
            const T m32 = Vector3<T>::dot(m_data[2], rhs.m_data[1]);
            const T m33 = Vector3<T>::dot(m_data[2], rhs.m_data[2]);

            *this = Matrix3x3(Vector3<T>(m11, m12, m13), Vector3<T>(m21, m22, m23), Vector3<T>(m31, m32, m33));

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
        std::array<Vector3<T>, 3> m_data;
    };

    using Matrix3x3f = Matrix3x3<float>;
    using Matrix3x3d = Matrix3x3<double>;
} // namespace MathLib

#endif // MATH_LIB_MATRIX3X3_H
