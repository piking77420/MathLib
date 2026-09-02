#ifndef MATH_LIB_MATRIX2X2_H
#define MATH_LIB_MATRIX2X2_H

#include <array>
#include <Vector2.hpp>

namespace MathLib
{
    // Matrix elements are stored in row-major order
    // Mathematical operations use a column-vector convention
    template<typename T>
    requires(std::is_floating_point_v<T>)
    class Matrix2x2
    {
    public:
        using _VectorType = Vector2<T>;
        using _ValueType = typename _VectorType::_ValueType;

        explicit Matrix2x2() = default;

        ~Matrix2x2() = default;
        // clang-format off
        MATH_LIB_FORCE_INLINE explicit Matrix2x2(T getM11, T getM12,
                                                 T getM21, T getM22)
            : m_data{Vector2<T>(getM11, getM12), 
                     Vector2<T>(getM21, getM22)}
        {

        }
        // clang-format on

        MATH_LIB_FORCE_INLINE explicit Matrix2x2(Vector2<T> row1, Vector2<T> row2)
            : m_data{row1, row2}
        {
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix2x2 zero() noexcept
        {
            // clang-format off
            return Matrix2x2(0.0, 0.0,
                             0.0, 0.0);
            // clang-format on
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE static Matrix2x2 identity() noexcept
        {
            // clang-format off
            return Matrix2x2(1.0, 0.0,
                             0.0, 1.0);
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

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM21() const noexcept
        {
            return m_data[1].getX();
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE T getM22() const noexcept
        {
            return m_data[1].getY();
        }

        MATH_LIB_FORCE_INLINE Matrix2x2& setM11(T getM11) noexcept
        {
            m_data[0].setX(getM11);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix2x2& setM12(T getM12) noexcept
        {
            m_data[0].setY(getM12);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix2x2& setM21(T getM21) noexcept
        {
            m_data[1].setX(getM21);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix2x2& setM22(T getM22) noexcept
        {
            m_data[1].setY(getM22);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix2x2& transpose() noexcept
        {
            const T trmp = m_data[0].getY();
            m_data[0].setY(m_data[1].getX());
            m_data[1].setX(trmp);
            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix2x2 getTranspose() const noexcept
        {
            Matrix2x2 m = (*this);
            return m.transpose();
        }

        MATH_LIB_FORCE_INLINE T determinant() const noexcept
        {
            const T a = m_data[0].getX();
            const T b = m_data[0].getY();
            const T c = m_data[1].getX();
            const T d = m_data[1].getY();

            return a * d - b * c;
        }

        MATH_LIB_FORCE_INLINE Matrix2x2& inverse() noexcept
        {
            const T a = m_data[0].getX();
            const T b = m_data[0].getY();
            const T c = m_data[1].getX();
            const T d = m_data[1].getY();

            const T determinant = a * d - b * c;

            if (fuzzyZero(determinant) || !std::isfinite(determinant))
                return *this;

            const T invDeterminant = 1.0 / determinant;

            // clang-format off
            *this = Matrix2x2(
                 d * invDeterminant, -b * invDeterminant,
                -c * invDeterminant,  a * invDeterminant
            );
            // clang-format on

            return *this;
        }

        MATH_LIB_FORCE_INLINE Matrix2x2 getInverse() const noexcept
        {
            Matrix2x2 m = *this;
            return m.inverse();
        }

        MATH_LIB_FORCE_INLINE Matrix2x2& operator+=(const T value) noexcept
        {
            m_data[0] += value;
            m_data[1] += value;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix2x2 operator+(T scalar) const
        {
            Matrix2x2 result = *this;
            result += scalar;
            return result;
        }

        MATH_LIB_FORCE_INLINE Matrix2x2& operator-=(const T value) noexcept
        {
            m_data[0] -= value;
            m_data[1] -= value;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix2x2 operator-(T scalar) const
        {
            Matrix2x2 result = *this;
            result -= scalar;
            return result;
        }

        MATH_LIB_FORCE_INLINE Matrix2x2& operator*=(const T value) noexcept
        {
            m_data[0] *= value;
            m_data[1] *= value;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix2x2 operator*(T scalar) const
        {
            Matrix2x2 result = *this;
            result *= scalar;
            return result;
        }

        MATH_LIB_FORCE_INLINE Matrix2x2& operator/=(const T value) noexcept
        {
            m_data[0] /= value;
            m_data[1] /= value;
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix2x2 operator/(T scalar) const
        {
            Matrix2x2 result = *this;
            result /= scalar;
            return result;
        }

        MATH_LIB_FORCE_INLINE Matrix2x2& operator+=(const Matrix2x2& rhs) noexcept
        {
            m_data[0] += rhs.m_data[0];
            m_data[1] += rhs.m_data[1];
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix2x2 operator+(const Matrix2x2& rhs) const
        {
            Matrix2x2 result = *this;
            result += rhs;
            return result;
        }

        MATH_LIB_FORCE_INLINE Matrix2x2& operator-=(const Matrix2x2& rhs) noexcept
        {
            m_data[0] -= rhs.m_data[0];
            m_data[1] -= rhs.m_data[1];
            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix2x2 operator-(const Matrix2x2& rhs) const
        {
            Matrix2x2 result = *this;
            result -= rhs;
            return result;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Vector2<T> operator*(const Vector2<T>& rhs) const noexcept
        {
            return Vector2<T>(Vector2<T>::dot(m_data[0], rhs), Vector2<T>::dot(m_data[1], rhs));
        }

        MATH_LIB_FORCE_INLINE Matrix2x2& operator*=(Matrix2x2 rhs) noexcept
        {
            // because the matrix is row layout and we want to only do an dot product
            // we transopse the other matrix to make the base row * coloms multiplication
            // an row * row multiplication
            rhs.transpose();

            const T getM11 = Vector2<T>::dot(m_data[0], rhs.m_data[0]);
            const T getM12 = Vector2<T>::dot(m_data[0], rhs.m_data[1]);

            const T getM21 = Vector2<T>::dot(m_data[1], rhs.m_data[0]);
            const T getM22 = Vector2<T>::dot(m_data[1], rhs.m_data[1]);

            m_data[0] = Vector2<T>(getM11, getM12);
            m_data[1] = Vector2<T>(getM21, getM22);

            return *this;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE Matrix2x2 operator*(const Matrix2x2& rhs) const noexcept
        {
            Matrix2x2 m = *this;
            m *= rhs;
            return m;
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE bool operator==(const Matrix2x2& rhs) const noexcept
        {
            return m_data[0] == rhs.m_data[0] && m_data[1] == rhs.m_data[1];
        }

        [[nodiscard]] MATH_LIB_FORCE_INLINE bool operator!=(const Matrix2x2& rhs) const noexcept
        {
            return !this->operator==(rhs);
        }

    private:
        std::array<Vector2<T>, 2> m_data;
    };

    using Matrix2x2f = Matrix2x2<float>;
    using Matrix2x2d = Matrix2x2<double>;
} // namespace MathLib

#endif // MATH_LIB_MATRIX2X2_H
