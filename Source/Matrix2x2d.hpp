#ifndef MATH_LIB_MATRIX2X2D_H
#define MATH_LIB_MATRIX2X2D_H

#include <Vector2d.hpp>

namespace MathLib
{
    template<typename T>
    class Matrix2x2;

    // Matrix elements are stored in row-major order
    // Mathematical operations use a column-vector convention
    template<>
    class Matrix2x2<double>
    {
    public:
        explicit Matrix2x2() = default;

        ~Matrix2x2() = default;
        // clang-format off
        MATH_LIB_FORCE_INLINE explicit Matrix2x2(double getM11, double getM12,
                                                 double getM21, double getM22)
            : m_data{Vector2d(getM11, getM12), 
                     Vector2d(getM21, getM22)}
        {

        }
        // clang-format on

        MATH_LIB_FORCE_INLINE explicit Matrix2x2(Vector2d row1, Vector2d row2)
            : m_data{row1, row2}
        {
        }

        static Matrix2x2 identity()
        {
            // clang-format off
            return Matrix2x2(1.0, 0.0,
                             0.0, 1.0);
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

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM21() const noexcept
        {
            return m_data[1].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE double getM22() const noexcept
        {
            return m_data[1].getY();
        }

        Matrix2x2& setM11(double getM11) noexcept
        {
            m_data[0].setX(getM11);
            return *this;
        }

        Matrix2x2& setM12(double getM12) noexcept
        {
            m_data[0].setY(getM12);
            return *this;
        }

        Matrix2x2& setM21(double getM21) noexcept
        {
            m_data[1].setX(getM21);
            return *this;
        }

        Matrix2x2& setM22(double getM22) noexcept
        {
            m_data[1].setY(getM22);
            return *this;
        }

        Matrix2x2& transpose() noexcept
        {
#if defined(SIMD_AVX)
#else
            const double trmp = m_data[0].getY();
            m_data[0].setY(m_data[1].getX());
            m_data[1].setX(trmp);
#endif // SIMD_AVX

            return *this;
        }

        Matrix2x2 getTranspose() const noexcept
        {
            Matrix2x2 m = (*this);
            return m.transpose();
        }

        double determinant() const noexcept
        {
#if defined(SIMD_AVX)
#else
            const double a = m_data[0].getX();
            const double b = m_data[0].getY();
            const double c = m_data[1].getX();
            const double d = m_data[1].getY();

            return a * d - b * c;
#endif // SIMD_AVX
        }

        Matrix2x2& inverse() noexcept
        {
            const double d = determinant();
            if (fuzzyZero(d))
                return *this;
#if defined(SIMD_AVX)
#else

            const double invDetermiant = 1.0 / d;
            // clang-format off
            const Matrix2x2 adj = Matrix2x2(m_data[1].getY(), -m_data[0].getY(),
                                            -m_data[1].getX(), m_data[0].getX()) * invDetermiant;
            // clang-format on
            *this = adj;
#endif // SIMD_AVX

            return *this;
        }

        Matrix2x2 getInverse() const noexcept
        {
            Matrix2x2 m = *this;
            return m.inverse();
        }

        Matrix2x2& operator+=(const double value) noexcept
        {
            m_data[0] += value;
            m_data[1] += value;
            return *this;
        }

        [[nodiscard]] Matrix2x2 operator+(double scalar) const
        {
            Matrix2x2 result = *this;
            result += scalar;
            return result;
        }

        Matrix2x2& operator-=(const double value) noexcept
        {
            m_data[0] -= value;
            m_data[1] -= value;
            return *this;
        }

        [[nodiscard]] Matrix2x2 operator-(double scalar) const
        {
            Matrix2x2 result = *this;
            result -= scalar;
            return result;
        }

        Matrix2x2& operator*=(const double value) noexcept
        {
            m_data[0] *= value;
            m_data[1] *= value;
            return *this;
        }

        [[nodiscard]] Matrix2x2 operator*(double scalar) const
        {
            Matrix2x2 result = *this;
            result *= scalar;
            return result;
        }

        Matrix2x2& operator/=(const double value) noexcept
        {
            m_data[0] /= value;
            m_data[1] /= value;
            return *this;
        }

        [[nodiscard]] Matrix2x2 operator/(double scalar) const
        {
            Matrix2x2 result = *this;
            result /= scalar;
            return result;
        }

        Matrix2x2& operator+=(const Matrix2x2& rhs) noexcept
        {
            m_data[0] += rhs.m_data[0];
            m_data[1] += rhs.m_data[1];
            return *this;
        }

        [[nodiscard]] Matrix2x2 operator+(const Matrix2x2& rhs) const
        {
            Matrix2x2 result = *this;
            result += rhs;
            return result;
        }

        Matrix2x2& operator-=(const Matrix2x2& rhs) noexcept
        {
            m_data[0] -= rhs.m_data[0];
            m_data[1] -= rhs.m_data[1];
            return *this;
        }

        [[nodiscard]] Matrix2x2 operator-(const Matrix2x2& rhs) const
        {
            Matrix2x2 result = *this;
            result -= rhs;
            return result;
        }

        [[nodiscard]] Vector2d operator*(const Vector2d& rhs) const noexcept
        {
            return Vector2d(Vector2d::dot(m_data[0], rhs), Vector2d::dot(m_data[1], rhs));
        }

        Matrix2x2& operator*=(Matrix2x2 rhs) noexcept
        {
            // because the matrix is row layout and we want to only do an dot product
            // we transopse the other matrix to make the base row * coloms multiplication
            // an row * row multiplication
            rhs.transpose();

            const double getM11 = Vector2d::dot(m_data[0], rhs.m_data[0]);
            const double getM12 = Vector2d::dot(m_data[0], rhs.m_data[1]);

            const double getM21 = Vector2d::dot(m_data[1], rhs.m_data[0]);
            const double getM22 = Vector2d::dot(m_data[1], rhs.m_data[1]);

            m_data[0] = Vector2d(getM11, getM12);
            m_data[1] = Vector2d(getM21, getM22);

            return *this;
        }

        [[nodiscard]] Matrix2x2 operator*(const Matrix2x2& rhs) const noexcept
        {
            Matrix2x2 m = *this;
            m *= rhs;
            return m;
        }

        bool operator==(const Matrix2x2& rhs) const noexcept
        {
            return m_data[0] == rhs.m_data[0] && m_data[1] == rhs.m_data[1];
        }

        bool operator!=(const Matrix2x2& rhs) const noexcept
        {
            return !this->operator==(rhs);
        }

    private:
        std::array<Vector2d, 2> m_data;
    };

    using Matrix2x2d = Matrix2x2<double>;
}

#endif // MATH_LIB_MATRIX2X2D_H
