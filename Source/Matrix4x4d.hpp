#ifndef MATH_LIB_MATRIX4X4D_H
#define MATH_LIB_MATRIX4X4D_H

#include <Vector4d.hpp>

namespace MathLib
{
    template<typename T>
    class Matrix4x4;

    // Matrix elements are stored in row-major order
    // Mathematical operations use a column-vector convention
    template<>
    class Matrix4x4<double>
    {
    public:
        using _VectorType = Vector4d;

        explicit Matrix4x4() = default;

        ~Matrix4x4() = default;
        // clang-format off
        MATH_LIB_FORCE_INLINE explicit Matrix4x4(double getM11, double getM12, double getM13, double getM14,
                                                 double getM21, double getM22, double getM23, double getM24,
                                                 double getM31, double getM32, double getM33, double getM34,
                                                 double getM41, double getM42, double getM43, double getM44)
            : m_data{Vector4d(getM11, getM12, getM13, getM14), 
                     Vector4d(getM21, getM22, getM23, getM24),
                     Vector4d(getM31, getM32, getM33, getM34),
                     Vector4d(getM41, getM42, getM43, getM44)}
        {

        }
        // clang-format on
        // clang-format off
        MATH_LIB_FORCE_INLINE explicit Matrix4x4(const Vector4d& row1, 
                                                 const Vector4d& row2, 
                                                 const Vector4d& row3,
                                                 const Vector4d& row4)
            : m_data{row1, row2, row3, row4}
        {
        }
        // clang-format on
        [[nodiscard]] static Matrix4x4 identity() noexcept
        {
            // clang-format off
            return Matrix4x4(1.0, 0.0, 0.0, 0.0,
                             0.0, 1.0, 0.0, 0.0,
                             0.0, 0.0, 1.0, 0.0,
                             0.0, 0.0, 0.0, 1.0);
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

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM14() const noexcept
        {
            return m_data[0].getW();
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

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM24() const noexcept
        {
            return m_data[1].getW();
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

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM34() const noexcept
        {
            return m_data[2].getW();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM41() const noexcept
        {
            return m_data[3].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM42() const noexcept
        {
            return m_data[3].getY();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM43() const noexcept
        {
            return m_data[3].getZ();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM44() const noexcept
        {
            return m_data[3].getW();
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM11(double getM11) noexcept
        {
            m_data[0].setX(getM11);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM12(double getM12) noexcept
        {
            m_data[0].setY(getM12);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM13(double getM13) noexcept
        {
            m_data[0].setZ(getM13);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM14(double getM14) noexcept
        {
            m_data[0].setW(getM14);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM21(double getM21) noexcept
        {
            m_data[1].setX(getM21);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM22(double getM22) noexcept
        {
            m_data[1].setY(getM22);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM23(double getM23) noexcept
        {
            m_data[1].setZ(getM23);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM24(double getM24) noexcept
        {
            m_data[1].setW(getM24);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM31(double getM31) noexcept
        {
            m_data[2].setX(getM31);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM32(double getM32) noexcept
        {
            m_data[2].setY(getM32);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM33(double getM33) noexcept
        {
            m_data[2].setZ(getM33);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM34(double getM34) noexcept
        {
            m_data[2].setW(getM34);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM41(double getM41) noexcept
        {
            m_data[3].setX(getM41);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM42(double getM42) noexcept
        {
            m_data[3].setY(getM42);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM43(double getM43) noexcept
        {
            m_data[3].setZ(getM43);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& setM44(double getM44) noexcept
        {
            m_data[3].setW(getM44);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4& transpose() noexcept
        {
            double* ptr = reinterpret_cast<double*>(&m_data[0]);

            static constexpr std::size_t m12offset = 1;
            static constexpr std::size_t m13offset = 2;
            static constexpr std::size_t m14offset = 3;

            static constexpr std::size_t m21offset = 4;
            static constexpr std::size_t m23offset = 6;
            static constexpr std::size_t m24offset = 7;

            static constexpr std::size_t m31offset = 8;
            static constexpr std::size_t m32offset = 9;
            static constexpr std::size_t m34offset = 11;

            static constexpr std::size_t m41offset = 12;
            static constexpr std::size_t m42offset = 13;
            static constexpr std::size_t m43offset = 14;

            std::swap(ptr[m12offset], ptr[m21offset]);

            std::swap(ptr[m13offset], ptr[m31offset]);
            std::swap(ptr[m14offset], ptr[m41offset]);

            std::swap(ptr[m23offset], ptr[m32offset]);
            std::swap(ptr[m24offset], ptr[m42offset]);

            std::swap(ptr[m34offset], ptr[m43offset]);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix4x4 getTranspose() const noexcept
        {
            Matrix4x4 m = (*this);
            return m.transpose();
        }

        MATH_LIB_FORCE_INLINE double determinant() const noexcept
        {
            return Vector4d::dot(m_data[0], Vector4d::cross(m_data[1], m_data[2], m_data[3]));
        }

        Matrix4x4& inverse() noexcept;

        Matrix4x4 getInverse() const noexcept
        {
            Matrix4x4 m = *this;
            return m.inverse();
        }

        Matrix4x4& operator+=(const double value) noexcept
        {
            m_data[0] += value;
            m_data[1] += value;
            m_data[2] += value;
            m_data[3] += value;
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator+(double scalar) const
        {
            Matrix4x4 result = *this;
            result += scalar;
            return result;
        }

        Matrix4x4& operator-=(const double value) noexcept
        {
            m_data[0] -= value;
            m_data[1] -= value;
            m_data[2] -= value;
            m_data[3] -= value;
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator-(double scalar) const
        {
            Matrix4x4 result = *this;
            result -= scalar;
            return result;
        }

        Matrix4x4& operator*=(const double value) noexcept
        {
            m_data[0] *= value;
            m_data[1] *= value;
            m_data[2] *= value;
            m_data[3] *= value;
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator*(double scalar) const
        {
            Matrix4x4 result = *this;
            result *= scalar;
            return result;
        }

        Matrix4x4& operator/=(const double value) noexcept
        {
            m_data[0] /= value;
            m_data[1] /= value;
            m_data[2] /= value;
            m_data[3] /= value;
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator/(double scalar) const
        {
            Matrix4x4 result = *this;
            result /= scalar;
            return result;
        }

        Matrix4x4& operator+=(const Matrix4x4& rhs) noexcept
        {
            m_data[0] += rhs.m_data[0];
            m_data[1] += rhs.m_data[1];
            m_data[2] += rhs.m_data[2];
            m_data[3] += rhs.m_data[3];
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator+(const Matrix4x4& rhs) const
        {
            Matrix4x4 result = *this;
            result += rhs;
            return result;
        }

        Matrix4x4& operator-=(const Matrix4x4& rhs) noexcept
        {
            m_data[0] -= rhs.m_data[0];
            m_data[1] -= rhs.m_data[1];
            m_data[2] -= rhs.m_data[2];
            m_data[3] -= rhs.m_data[3];
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator-(const Matrix4x4& rhs) const
        {
            Matrix4x4 result = *this;
            result -= rhs;
            return result;
        }

        [[nodiscard]] Vector4d operator*(const Vector4d& rhs) const noexcept
        {
            return Vector4d(Vector4d::dot(m_data[0], rhs), Vector4d::dot(m_data[1], rhs), Vector4d::dot(m_data[2], rhs),
                            Vector4d::dot(m_data[3], rhs));
        }

        Matrix4x4& operator*=(Matrix4x4 rhs) noexcept
        {
            // because the matrix is row layout and we want to only do an dot product
            // we transopse the other matrix to make the base row * coloms multiplication
            // an row * row multiplication
            rhs.transpose();

            const double m11 = Vector4d::dot(m_data[0], rhs.m_data[0]);
            const double m12 = Vector4d::dot(m_data[0], rhs.m_data[1]);
            const double m13 = Vector4d::dot(m_data[0], rhs.m_data[2]);
            const double m14 = Vector4d::dot(m_data[0], rhs.m_data[3]);
            const Vector4d row1 = Vector4d(m11, m12, m13, m14);

            const double m21 = Vector4d::dot(m_data[1], rhs.m_data[0]);
            const double m22 = Vector4d::dot(m_data[1], rhs.m_data[1]);
            const double m23 = Vector4d::dot(m_data[1], rhs.m_data[2]);
            const double m24 = Vector4d::dot(m_data[1], rhs.m_data[3]);
            const Vector4d row2 = Vector4d(m21, m22, m23, m24);

            const double m31 = Vector4d::dot(m_data[2], rhs.m_data[0]);
            const double m32 = Vector4d::dot(m_data[2], rhs.m_data[1]);
            const double m33 = Vector4d::dot(m_data[2], rhs.m_data[2]);
            const double m34 = Vector4d::dot(m_data[2], rhs.m_data[3]);
            const Vector4d row3 = Vector4d(m31, m32, m33, m34);

            const double m41 = Vector4d::dot(m_data[3], rhs.m_data[0]);
            const double m42 = Vector4d::dot(m_data[3], rhs.m_data[1]);
            const double m43 = Vector4d::dot(m_data[3], rhs.m_data[2]);
            const double m44 = Vector4d::dot(m_data[3], rhs.m_data[3]);
            const Vector4d row4 = Vector4d(m41, m42, m43, m44);

            // clang-format off
            *this = Matrix4x4(row1,
                              row2,
                              row3,
                              row4);
            // clang-format on
            return *this;
        }

        [[nodiscard]] Matrix4x4 operator*(const Matrix4x4& rhs) const noexcept
        {
            Matrix4x4 m = *this;
            m *= rhs;
            return m;
        }

        bool operator==(const Matrix4x4& rhs) const noexcept
        {
            return m_data[0] == rhs.m_data[0] && m_data[1] == rhs.m_data[1] && m_data[2] == rhs.m_data[2] &&
                   m_data[3] == rhs.m_data[3];
        }

        bool operator!=(const Matrix4x4& rhs) const noexcept
        {
            return !this->operator==(rhs);
        }

    private:
        std::array<Vector4d, 4> m_data;
    };

    using Matrix4x4d = Matrix4x4<double>;
} // namespace MathLib

#endif // MATH_LIB_MATRIX4X4D_H
